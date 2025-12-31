#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <threads.h>
#include <stdatomic.h>

#define MAX_QTD 5
#define TEMPO_LIM 30

atomic_int status = 0;

typedef struct Pedido{
    char sabor[55];
    char bebida[55];
    char borda[55];
    char acompanhamento[55];
} Pedido;

typedef struct Cliente{
    char nome[40];
    Pedido pedido;
} Cliente;

int cronometro(void *arg){
    for(int i = TEMPO_LIM; i>0; i--){
        if(atomic_load(&status)==1) return 0;
        if(i == 20){
            printf("Faltam %d segundos... \n", i);
        }
        if(i == 10){
            printf("Faltam %d segundos... \n", i);
        }
        if(i <=5 ){
            printf("Faltam %d segundos... \n", i);
        }
        struct timespec t = {.tv_sec = 1};
        thrd_sleep(&t, NULL);
    }
    if(atomic_load(&status)==0){
        atomic_store(&status, 2);
        printf("\n\nO cliente desistiu do pedido!\n");
        printf("Aperte ENTER para continuar\n");
    }
    return 0;
}
typedef struct{
    Cliente *primeiro;
    Cliente *ultimo;
} Fila;

void criarPedido(Pedido *p){
    char sabores[MAX_QTD][55] = {
        {"Mussarela"},
        {"Portuguesa"},
        {"Quatro Queijos"},
        {"Frango Catupiry"},
        {"Sorvete"}
    };
    char bordas[MAX_QTD][55] = {
        {"Chocolate"},
        {"Catupiry"},
        {"Doce de Leite"},
        {"Cream Cheese"},
        {"Cheddar"}
    };
    char acompanhamentos[MAX_QTD][55] = {
        {"Ketchup"},
        {"Maionese"},
        {"Ketchup + Maionese"},
        {"Maionese temperada"},
        {"Sem acompalhamentos"}
    };
    char bebidas[MAX_QTD][55] ={
        {"Suco de laranja"},
        {"Suco de manga"},
        {"Coca-Cola"},
        {"Guaraná"},
        {"Sem bebidas"}
    };
    
    strcpy(p->sabor, sabores[rand() % (MAX_QTD-1)]);
    strcpy(p->borda, bordas[rand() % (MAX_QTD-1)]);
    strcpy(p->acompanhamento, acompanhamentos[rand() % (MAX_QTD-1)]);
    strcpy(p->bebida, bebidas[rand() % (MAX_QTD-1)]);
}
int main()
{
    
    thrd_t thread;
    Pedido p1;
    Pedido p2;
    criarPedido(&p1);
    criarPedido(&p2);
    
    thrd_create(&thread, cronometro, NULL);
    srand(time(NULL));
    
    printf("--------------PEDIDO --------------\n");
    printf("Sabor: %s \n", p1.sabor);
    printf("Bebida: %s \n", p1.bebida);
    printf("Bordas: %s \n", p1.borda);
    printf("Acompanhamentos: %s \n", p1.acompanhamento);
    
    printf("--------------PEDIDO --------------\n");
    printf("Sabor: %s \n", p2.sabor);
    printf("Bebida: %s \n", p2.bebida);
    printf("Bordas: %s \n", p2.borda);
    printf("Acompanhamentos: %s \n", p2.acompanhamento);
    thrd_join(thread, NULL);
    return 0;
}