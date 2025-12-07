import os
import subprocess

TASCAL_DIR = "Tascal"     # pasta dos arquivos .tascal
FLAG = "-g"               # coloque a flag que deseja (ex: -l, -p, -pp, -s, -g)

for fname in os.listdir(TASCAL_DIR):
    if fname.endswith(".tascal"):
        path = os.path.join(TASCAL_DIR, fname)
        print(f"\n==============================================")
        print(f"Arquivo: {fname}")

        result = subprocess.run(
            ["python", "main.py", FLAG, path],
            capture_output=False,   # coloque True se quiser capturar a saída
            text=True
        )

print(f"\n==============================================")