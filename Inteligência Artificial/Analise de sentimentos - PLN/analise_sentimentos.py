#  pip install yfinance nltk scikit-learn pandas matplotlib seaborn --quiet

import json
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import yfinance as yf
import nltk
import re
from datetime import timedelta
from sklearn.feature_extraction.text import CountVectorizer
from nltk.stem import RSLPStemmer
from nltk.corpus import stopwords

nltk.download('stopwords', quiet=True)
nltk.download('rslp', quiet=True)

# ==========================================================
# 2. Carregamento do arquivo JSON (notícias)
# ==========================================================
# ALTERE OS DADOS SE NECESSÁRIO
nome_arquivo = 'noticias AXIA3.json'
ticker = "ELET3.SA" 
nome_acao = "(ELET3)" # Opções: ELET3, ELET6, AXIA3, AXIA6, PETR4, ENGIE3
# ==========================================================

with open(nome_arquivo, 'r', encoding='utf-8') as f:
    dados_noticias = json.load(f)
    print(f"Conteúdo de {nome_arquivo} lido!")

df_noticias = pd.DataFrame(dados_noticias)
df_noticias['data'] = pd.to_datetime(df_noticias['data'], format='%d/%m/%Y')

# ==========================================================
# 3. Download dos preços da empresa
# ==========================================================
print(f"Coletando dados da B3 {nome_acao}...")

inicio = df_noticias['data'].min() - timedelta(days=10)
fim = df_noticias['data'].max() + timedelta(days=10)

dados_acoes = yf.download(
    ticker,
    start=inicio,
    end=fim,
    progress=False,
    auto_adjust=False
)

dados_acoes.reset_index(inplace=True) # type: ignore

if isinstance(dados_acoes.columns, pd.MultiIndex): # type: ignore
    dados_acoes.columns = [col[0] if isinstance(col, tuple) else col for col in dados_acoes.columns] # type: ignore

# Correção da coluna Date
df_acoes = dados_acoes[['Date','Open','Close']].copy() # type: ignore

df_acoes['Date'] = pd.to_datetime(df_acoes['Date'], errors='coerce')
df_acoes = df_acoes.dropna(subset=['Date'])
df_acoes['Date'] = df_acoes['Date'].dt.floor('D') # type: ignore

# Calcula variação
df_acoes['Variacao'] = ((df_acoes['Close'] - df_acoes['Open']) / df_acoes['Open']) * 100

# ==========================================================
# 4. Pré-processamento
# ==========================================================
stops = set(stopwords.words('portuguese'))
stemmer = RSLPStemmer()

def pre_processar(texto):
    if not isinstance(texto, str):
        return ""
    texto = texto.lower()
    texto = re.sub(r'[^À-ſ\w\s]', ' ', texto)
    tokens = texto.split()
    tokens = [stemmer.stem(t) for t in tokens if t not in stops]
    return " ".join(tokens)

df_noticias['texto_processado'] = df_noticias['texto'].apply(pre_processar)
# Para executar sem pre-processamento, descomente a linha abaixo e comente a de cima
# df_noticias['texto_processado'] = df_noticias['texto'] 

# ==========================================================
# 5. Vetorização com CountVectorizer
# ==========================================================
positivas = [
    'lucro','cres','ganh','expans','alt','posit','fort','aument',
    'dividend','otim','record','melhor','eficien','sucess','avan'
]

negativas = [
    'queda','desp','cust','baix','negat','alert','proble','risc',
    'recua','desafi','pression','volatil','dimin','reduz','prej'
]

vectorizer = CountVectorizer()
X = vectorizer.fit_transform(df_noticias['texto_processado'])
vocab = vectorizer.vocabulary_

# ==========================================================
# 6. Função de sentimento aprimorada (CountVectorizer)
# ==========================================================
def sentimento_count(idx):
    vetor = X[idx].toarray()[0] # type: ignore
    total = vetor.sum() if vetor.sum() > 0 else 1
    score = 0

    for palavra, pos in vocab.items():
        qtd = vetor[pos]

        if qtd > 0:
            # POSITIVAS
            if any(p in palavra for p in positivas):
                score += 2 * qtd

            # NEGATIVAS
            if any(n in palavra for n in negativas):
                score -= 2.5 * qtd

    polaridade = score / (total ** 0.7)
    return max(-1, min(1, polaridade))

df_noticias['sentimento'] = df_noticias.index.map(sentimento_count)

# ==========================================================
# 7. Função de captura de variação com lag temporal
# ==========================================================
def obter_variacao(data_noticia, dias_offset):

    target = pd.to_datetime(data_noticia + timedelta(days=dias_offset)).to_pydatetime()

    match = df_acoes[df_acoes['Date'] >= target].sort_values('Date')

    if not match.empty:
        data_encontrada = match.iloc[0]['Date']

        if not isinstance(data_encontrada, pd.Timestamp):
            data_encontrada = pd.to_datetime(data_encontrada, errors='coerce')

        data_encontrada = data_encontrada.to_pydatetime()

        diff = data_encontrada - target

        if abs(diff.days) <= 3:
            return match.iloc[0]['Variacao']

    return np.nan

# Aplicando os lags
lags = [-2, -1, 0, 1, 2]
colunas_lags = []

for lag in lags:
    nome = f"var_d_{'menos_'+str(abs(lag)) if lag<0 else 'mais_'+str(lag) if lag>0 else '0'}"
    df_noticias[nome] = df_noticias['data'].apply(lambda d: obter_variacao(d, lag))
    colunas_lags.append(nome)


# ==========================================================
# 8. Matriz de correlação
# ==========================================================
matriz_corr = df_noticias[['sentimento'] + colunas_lags].corr()
print("\n=== Correlação com sentimento ===")
print(matriz_corr['sentimento'])


# ==========================================================
# 9. Geração dos gráficos
# ==========================================================
plt.figure(figsize=(15, 8))
plt.suptitle(f"Correlação: Sentimento x Variação das Ações {nome_acao}", fontsize=16)

titulos = {
    -2: "2 Dias Antes",
    -1: "1 Dia Antes",
     0: "Dia da Notícia",
     1: "1 Dia Depois",
     2: "2 Dias Depois"
}

for i, lag in enumerate(lags):
    nome = colunas_lags[i]
    plt.subplot(2, 3, i+1)

    dados_plot = df_noticias.dropna(subset=[nome])
    print(f"Número de pontos para {titulos[lag]}.")
    sns.regplot(
        x=dados_plot['sentimento'],
        y=dados_plot[nome],
        scatter_kws={'s': 80, 'alpha': 0.6},
        line_kws={'color': 'red'}
    )

    corr_val = matriz_corr['sentimento'][nome]
    plt.title(f"{titulos[lag]}\nCorrelação: {corr_val:.2f}")
    plt.xlabel("Sentimento")
    plt.ylabel("Variação (%)")
    plt.grid(True, linestyle='--', alpha=0.5)

plt.tight_layout(rect=[0, 0.03, 1, 0.95]) # type: ignore
plt.show()


# ==========================================================
# 10. Tabela final
# ==========================================================
print("\n ===== Tabela Final ===== ")
print(df_noticias[['data', 'sentimento', 'var_d_0']])