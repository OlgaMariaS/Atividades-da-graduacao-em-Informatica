#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da lista
typedef struct node {
    int value;
    struct node* prev;
    struct node* next;
} Node;

// Definição da estrutura do deque
typedef struct deque {
    Node* front;
    Node* rear;
} Deque;

// Função para criar um nó
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Função para criar um deque vazio
Deque* createDeque() {
    Deque* newDeque = (Deque*)malloc(sizeof(Deque));
    newDeque->front = NULL;
    newDeque->rear = NULL;
    return newDeque;
}

// Função para verificar se o deque está vazio
int isEmpty(Deque* deque) {
    return deque->front == NULL;
}

// Função para inserir um item na frente do deque
void insertFront(Deque* deque, int value) {
    Node* newNode = createNode(value);
    if (isEmpty(deque)) {
        deque->front = newNode;
        deque->rear = newNode;
    } else {
        newNode->next = deque->front;
        deque->front->prev = newNode;
        deque->front = newNode;
    }
}

// Função para inserir um item no final do deque
void insertRear(Deque* deque, int value) {
    Node* newNode = createNode(value);
    if (isEmpty(deque)) {
        deque->front = newNode;
        deque->rear = newNode;
    } else {
        newNode->prev = deque->rear;
        deque->rear->next = newNode;
        deque->rear = newNode;
    }
}

// Função para remover um item da frente do deque
int deleteFront(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    int value = deque->front->value;
    Node* temp = deque->front;
    deque->front = deque->front->next;
    if (deque->front == NULL) {
        deque->rear = NULL;
    } else {
        deque->front->prev = NULL;
    }
    free(temp);
    return value;
}

// Função para remover um item do final do deque
int deleteRear(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    int value = deque->rear->value;
    Node* temp = deque->rear;
    deque->rear = deque->rear->prev;
    if (deque->rear == NULL) {
        deque->front = NULL;
    } else {
        deque->rear->next = NULL;
    }
    free(temp);
    return value;
}

// Função para imprimir o deque
void printDeque(Deque* deque) {
    Node* current = deque->front;
    printf("Deque");
