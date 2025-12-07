import os

PASTA_ALUNO = "codigos_mepa"
PASTA_GABARITO = "Tascal"

def ler_arquivo(caminho):
    with open(caminho, "r") as f:
        return f.read().splitlines()

def comparar_arquivos(arq_aluno, arq_prof):
    linhas_aluno = ler_arquivo(arq_aluno)
    linhas_prof  = ler_arquivo(arq_prof)

    tamanho = max(len(linhas_aluno), len(linhas_prof))
    diffs = []

    for i in range(tamanho):
        # lê linha ou usa "<EOF>"
        linha_a = linhas_aluno[i] if i < len(linhas_aluno) else "<EOF>"
        linha_p = linhas_prof[i]  if i < len(linhas_prof)  else "<EOF>"

        # remove espaços em branco das pontas
        a_norm = linha_a.strip()
        p_norm = linha_p.strip()

        # compara apenas conteúdo relevante
        if a_norm != p_norm:
            diffs.append((i+1, linha_a, linha_p))

    return diffs

def main():
    arquivos_aluno = sorted(os.listdir(PASTA_ALUNO))

    print("\n=== Comparando arquivos MEPA ===\n")

    for nome in arquivos_aluno:
        arq_aluno = os.path.join(PASTA_ALUNO, nome)
        arq_prof  = os.path.join(PASTA_GABARITO, nome)

        if not os.path.exists(arq_prof):
            print(f"[AVISO] Gabarito não encontrado para: {nome}")
            continue

        diffs = comparar_arquivos(arq_aluno, arq_prof)

        if not diffs:
            print(f"[OK] {nome} — Arquivos iguais ✓")
        else:
            print(f"\n[ERRO] Diferenças encontradas em: {nome}")
            for (linha, aluno, prof) in diffs:
                print(f"  Linha {linha}:")
                print(f"    aluno:    {aluno}")
                print(f"    gabarito: {prof}")
            print("-" * 50)


if __name__ == "__main__":
    main()