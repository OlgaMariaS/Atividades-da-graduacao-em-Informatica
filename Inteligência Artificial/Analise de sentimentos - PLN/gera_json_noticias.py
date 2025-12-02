import json
import requests
from bs4 import BeautifulSoup
from datetime import datetime
import re

def extrair_data(texto):
    padrao = r"(\d{1,2}[/-]\d{1,2}[/-]\d{4})"
    match = re.search(padrao, texto)
    if match:
        try:
            d = match.group(1).replace("-", "/")
            data = datetime.strptime(d, "%d/%m/%Y")
            return data.strftime("%d/%m/%Y")
        except:
            return ""
    return ""
# ==========================================================
# 1. Carrega a notícias a partir da URL para JSON
# ==========================================================
def processar_noticia(item_json):
    url = item_json.get("noticia")
    resposta = requests.get(url, timeout=10)
    soup = BeautifulSoup(resposta.text, "html.parser")

    # ---- Título ----
    titulo = ""
    if soup.find("h1"):
        titulo = soup.find("h1").get_text(strip=True) # type: ignore
    elif soup.title:
        titulo = soup.title.get_text(strip=True)

    # ---- Texto ----
    paragrafos = soup.find_all("p")
    texto = " ".join([p.get_text(strip=True) for p in paragrafos])

    # ---- Data ----
    data = ""
    metatags = [
        ("meta", {"property": "article:published_time"}),
        ("meta", {"name": "article:published_time"}),
        ("meta", {"property": "og:updated_time"}),
        ("meta", {"name": "date"}),
        ("meta", {"itemprop": "datePublished"})
    ]

    for tag in metatags:
        m = soup.find(*tag) # type: ignore
        if m and m.get("content"):
            try:
                d = m.get("content")
                data = datetime.fromisoformat(d[:10]).strftime("%d/%m/%Y")
                break
            except:
                pass

    if not data:
        data = extrair_data(soup.get_text(" "))

    return {
        "titulo": titulo,
        "data": data,
        "texto": texto,
        "url": url
    }

# Noticias
entradas = [
  { "id": "01", "noticia": "https://www.infomoney.com.br/mercados/axia3-axia-ex-eletrobras-estreia-novo-ticker-na-b3-nesta-segunda/" },
  { "id": "02", "noticia": "https://www.infomoney.com.br/brasil/moraes-suspende-julgamento-de-acordo-entre-eletrobras-e-uniao-caso-vai-ao-plenario/" },
  { "id": "03", "noticia": "https://www.seudinheiro.com/2024/empresas/eletrobras-elet3-levanta-r-47-bilhoes-com-venda-de-termeletricas-e-ainda-diminui-o-risco-do-portfolio-miql/" },
  { "id": "04", "noticia": "https://www.infomoney.com.br/mercados/axia-tem-combinacao-de-resultado-robusto-e-dividendo-de-r-43-bilhoes-acoes-sobem/" },
  { "id": "05", "noticia": "https://www.infomoney.com.br/mercados/axia-antiga-eletrobras-passa-a-deter-usina-tres-irmaos-e-reforca-disciplina/" },
  { "id": "06", "noticia": "https://www.infomoney.com.br/mercados/axia-ex-eletrobras-compra-juno-por-r-247-mi-e-passa-a-deter-usina-tres-irmaos/" },
  { "id": "07", "noticia": "https://www.infomoney.com.br/business/axia-energia-ex-eletrobras-participara-de-leiloes-se-retorno-for-adequado-diz-ceo/" },
  { "id": "08", "noticia": "https://www.infomoney.com.br/business/justica-livra-uniao-de-pagar-r-16-bilhoes-em-acao-sobre-debentures-da-eletrobras/" },
  { "id": "09", "noticia": "https://valorinveste.globo.com/mercados/renda-variavel/empresas/noticia/2025/11/05/axia-energia-ex-eletrobras-elet3-registra-prejuizo-bilionario-no-3o-tri.ghtml" },
  { "id": "10", "noticia": "https://www.cnnbrasil.com.br/economia/mercado/eletrobras-tem-prejuizo-liquido-de-r-354-mi-no-1o-trimestre/" },
  { "id": "11", "noticia": "https://economia.uol.com.br/noticias/estadao-conteudo/2025/08/07/eletrobras-reverte-lucro-e-tem-prejuizo-de-r-1325-bilhao-no-2-trimestre.htm" },
  { "id": "12", "noticia": "https://valorinveste.globo.com/mercados/renda-variavel/empresas/noticia/2025/05/15/acoes-da-eletrobras-elet3-balanco-trimestre-resultados.ghtml" },
  { "id": "13", "noticia": "https://veja.abril.com.br/coluna/radar-economico/a-privatizada-eletrobras-entra-no-vermelho-e-frustra-analistas/" },
  { "id": "14", "noticia": "https://www.cartacapital.com.br/economia/eletrobras-tem-prejuizo-de-r-479-milhoes-em-trimestre-posterior-a-privatizacao/" },
  { "id": "15", "noticia": "https://forbes.com.br/forbes-money/2024/03/eletrobras-reverte-prejuizo-e-lucra-de-r-893-milhoes-no-4o-trimestre/" }
]

nome_arq_saida = "noticias NOME_DA_NOTICIA_AQUI.json"
resultados = [processar_noticia(item) for item in entradas]

# Salva no arquivo .json
with open(nome_arq_saida, "w", encoding="utf-8") as f:
    json.dump(resultados, f, ensure_ascii=False, indent=2)

print(f"Arquivo salvo com sucesso: {nome_arq_saida}")