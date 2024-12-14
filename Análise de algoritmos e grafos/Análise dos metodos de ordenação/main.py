import pandas, time;
from InserctionSort import InserctionSort;
from BubbleSort     import BubbleSort;
from SelectionSort  import SelectionSort;
from ShellSort      import ShellSort;
from QuickSort      import QuickSort;
from HeapSort       import HeapSort;
from MergeSort      import MergeSort;
from RadixSort      import RadixSort;

base_de_dados_ordem_aleatoria    = pandas.read_excel("cursos-prouni-aleatorio.xls"); 
base_de_dados_ordem_crescente    = pandas.read_excel("cursos-prouni-crescente.xls"); 
base_de_dados_ordem_descrescente = pandas.read_excel("cursos-prouni-decrescente.xls");  
atributo_para_ordenacao          = base_de_dados_ordem_aleatoria["nome"];  
metodos_de_ordenacao             = ['InserctionSort', 'BubbleSort','SelectionSort', 'ShellSort','QuickSort','HeapSort','MergeSort','RadixSort'];
funcoes_ordenacao                = [InserctionSort, BubbleSort, SelectionSort, ShellSort, QuickSort, HeapSort, MergeSort, RadixSort];
qtde_metodos                     = len(metodos_de_ordenacao);
tempos_de_execucao_aleatorio     = [];
tempos_de_execucao_crescente     = [];
tempos_de_execucao_decrescente   = [];

def calcular_tempo_de_execucao(funcao, *args, **args2):
    inicio = time.time()
    funcao(*args, **args2)
    fim = time.time()
    return fim - inicio;

for i in range(qtde_metodos):
    funcao  = funcoes_ordenacao[i]
    tempo1  = calcular_tempo_de_execucao(funcao, base_de_dados_ordem_aleatoria,    atributo_para_ordenacao)
    tempo2  = calcular_tempo_de_execucao(funcao, base_de_dados_ordem_crescente,    atributo_para_ordenacao)
    tempo3  = calcular_tempo_de_execucao(funcao, base_de_dados_ordem_descrescente, atributo_para_ordenacao)
    tempos_de_execucao_aleatorio.append(tempo1)
    tempos_de_execucao_crescente.append(tempo2)
    tempos_de_execucao_decrescente.append(tempo3)

print(f"--------------BASE DE DADOS ALEATÓRIA--------------")
for i in range(qtde_metodos):
    print(f"{metodos_de_ordenacao[i]} levou {tempos_de_execucao_aleatorio[i]:.2f} segundos")
print(f"---------------------------------------------------")

print(f"--------------BASE DE DADOS CRESCENTE--------------")
for i in range(qtde_metodos):
    print(f"{metodos_de_ordenacao[i]} levou {tempos_de_execucao_crescente[i]:.2f} segundos")
print(f"---------------------------------------------------")

print(f"--------------BASE DE DADOS DECRESCENTE--------------")
for i in range(qtde_metodos):
    print(f"{metodos_de_ordenacao[i]} levou {tempos_de_execucao_decrescente[i]:.2f} segundos")
print(f"---------------------------------------------------")