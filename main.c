#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <threads.h>
#include <stdatomic.h>
#include "clientes.c"
#include "estoque.h"


    #ifdef _WIN32
        #include <windows.h>
        #define PAUSA(s) Sleep(s * 1000)
    #else
        #include <unistd.h>
        #define PAUSA(s) sleep(s)
    #endif    


#define TEMPO_LIM 30

atomic_int status = 0;


int cronometro(void *arg){
    for(int i = TEMPO_LIM; i>0; i--){
        if(atomic_load(&status)==1){
            
            return 0;
        }
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
    
    strcpy(p->sabor, sabores[rand() % (MAX_QTD-1)]);
    strcpy(p->borda, bordas[rand() % (MAX_QTD-1)]);
    strcpy(p->acompanhamento, acompanhamentos[rand() % (MAX_QTD-1)]);
    strcpy(p->bebida, bebidas[rand() % (MAX_QTD-1)]);
    printf("--------------PEDIDO --------------\n");
    printf("Sabor: %s \n", p->sabor);
    printf("Bebida: %s \n", p->bebida);
    printf("Bordas: %s \n", p->borda);
    printf("Acompanhamentos: %s \n", p->acompanhamento);
}
int main()
{
    thrd_t thread;
    Pedido p1;
    Pedido p2;
    srand(time(NULL));
    int item;
    int qtd_clientes = rand() % 3 + 2;
    printf("%d", qtd_clientes);
 
    do{
        atomic_store(&status, 0);
    criarPedido(&p1);
    PAUSA(3);
    system("cls || clear");
    printf("Faça o pedido! ");
    thrd_create(&thread, cronometro, NULL);
    do{
    scanf("%d", &item);
    }while(strcmp(sabores[item], p1.sabor)==1);
    if(atomic_load(&status) == 2){
       printf("Tarde demais!\n");
    } else if (strcmp(sabores[item], p1.sabor)==0){
        printf("\nPedido anterior entregue!\n");
        atomic_store(&status, 1);
    }
    qtd_clientes--;
    thrd_join(thread, NULL);
    } while(qtd_clientes>0);
    printf("Expediente finalizado! :)");
    
    return 0;
}