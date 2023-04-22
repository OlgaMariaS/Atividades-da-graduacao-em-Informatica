//Heap Sort - Bubble Sort 
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 50000
#define MOD_RAND 10000
#define EXECS 3

//Funções auxiliares do Heap-sort
void trocar(int *a,int *b){
    int aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

void maxheapfy(int v[],int i, int n){
    int fe,fd,maior;
    fe=2*i+1;
    fd=2*i+2;
    maior=i;
    if(fd < n && v[fd]>v[maior]){
        maior=fd;
    }
    if(fe < n && v[fe]>v[maior]){
        maior=fe;
    }
    if(maior!=i){
        trocar(&v[i],&v[maior]);
        maxheapfy(v,maior,n);
    }
}
void buildmaxheap(int v[],int n){
    int i;
    for(i=(n-1)/2;i>=0;i--){
        maxheapfy(v,i,n);
    }   
}
void heapsort(int v[], int n){
    int i;
    buildmaxheap(v,n);
    for(i=n-1;i>0;i--){
        trocar(&v[i],&v[0]);
                maxheapfy(v,0,i);
    }
}

// Função Bubble-sort
 void bubble(int v[], int n){
    int lim,i,j,aux,trocou;
    trocou=1;
    i=0;
    while((i<n-1) && (trocou)){
        trocou=0;
        for(j=0;j<(n-1)-i;j++){
            if(v[j]>v[j+1]){
                aux=v[j];
                v[j]=v[j+1];
                v[j+1]=aux;
                trocou=1;
            }
        }
        i++;
    }
}
double calcula_tempo(struct timeval ini, struct timeval fim){
    return (fim.tv_usec - ini.tv_usec)/1e6 + (fim.tv_sec - ini.tv_sec);
}

void gera_vetor(int v[], int n){ 
    srand(time(NULL));
    int i;
    for(i=0;i<n;i++){
        v[i] = rand()%MOD_RAND;
    }
}

int main(){
    struct timeval ini_alg1, ini_alg2, fim_alg1, fim_alg2;
    double tempo1,tempo2;
    int *v, *v1, *v2;
    int i;
    
    //alocando os vetores v1 e v2 dinamicamente
    v=(int*)malloc(TAM*sizeof(int));
    v1=(int*)malloc(TAM*sizeof(int));
    v2=(int*)malloc(TAM*sizeof(int));
    
    //gerando o vetor v1
    gera_vetor(v,TAM);
    
    for(i=0;i<EXECS;i++){
        
        //copiar vetor v para v1 e v2
        for (int i = 0; i < TAM; i++) {
            v1[i] = v[i];
            v2[i] = v[i];
        }
        
        gettimeofday(&ini_alg1, NULL);
        heapsort(v1, TAM);
        gettimeofday(&fim_alg1, NULL);

        tempo1 = calcula_tempo(ini_alg1,fim_alg1);

        gettimeofday(&ini_alg2, NULL);
        bubble(v2, TAM);
        gettimeofday(&fim_alg2, NULL);
        
        tempo2 = calcula_tempo(ini_alg2,fim_alg2);
        
        //mostrar tempos ou salvar em arquivo
        printf("Tempo de execucao do Heap Sort: %.6f segundos\n", tempo1);
        printf("Tempo de execucao do Bubble Sort: %.6f segundos\n", tempo2);
    }
    return 0;
}