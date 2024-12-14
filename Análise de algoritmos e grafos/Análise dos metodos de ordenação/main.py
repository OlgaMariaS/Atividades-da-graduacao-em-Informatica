import time;
from BubbleSort     import BubbleSort;
from InserctionSort import InserctionSort;
from SelectionSort  import SelectionSort;
from ShellSort      import ShellSort;
from QuickSort      import QuickSort;
from HeapSort       import HeapSort;
from MergeSort      import MergeSort;
from RadixSort      import RadixSort;

base_de_dados_ordem_aleatoria    = "cursos-prouni-aleatorio.xlsx"; 
base_de_dados_ordem_crescente    = "cursos-prouni-crescente.xlsx"; 
base_de_dados_ordem_descrescente = "cursos-prouni-decrescente.xlsx";  
atributo_para_ordenacao          = "nome";  
metodos_de_ordenacao             = ['BubbleSort','InserctionSort','SelectionSort','ShellSort','QuickSort','HeapSort','MergeSort','RadixSort'];
funcoes_ordenacao                = [ BubbleSort,  InserctionSort,  SelectionSort,  ShellSort,  QuickSort,  HeapSort,  MergeSort,  RadixSort];
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

def exibir_tempos_de_execucao(titulo, tempos):
    print(f"--------------{titulo}--------------")
    for i in range(qtde_metodos):
        print(f"{metodos_de_ordenacao[i]} levou {tempos[i]:.2f} segundos")
    print(f"---------------------------------------------------")

exibir_tempos_de_execucao("BASE DE DADOS ALEATÓRIA", tempos_de_execucao_aleatorio)
exibir_tempos_de_execucao("BASE DE DADOS CRESCENTE", tempos_de_execucao_crescente)
exibir_tempos_de_execucao("BASE DE DADOS DECRESCENTE", tempos_de_execucao_decrescente)
