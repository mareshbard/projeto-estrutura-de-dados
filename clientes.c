#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QTD 5

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

// void criarPedido(Pedido *p){
//     char sabores[MAX_QTD][55] = {
//         {"Mussarela"},
//         {"Portuguesa"},
//         {"Quatro Queijos"},
//         {"Frango Catupiry"},
//         {"Sorvete"}
//     };
//     char bordas[MAX_QTD][55] = {
//         {"Chocolate"},
//         {"Catupiry"},
//         {"Doce de Leite"},
//         {"Cream Cheese"},
//         {"Cheddar"}
//     };
//     char acompanhamentos[MAX_QTD][55] = {
//         {"Ketchup"},
//         {"Maionese"},
//         {"Ketchup + Maionese"},
//         {"Maionese temperada"},
//         {"Sem acompalhamentos"}
//     };
//     char bebidas[MAX_QTD][55] ={
//         {"Suco de laranja"},
//         {"Suco de manga"},
//         {"Coca-Cola"},
//         {"Guaraná"},
//         {"Sem bebidas"}
//     };
    
//     strcpy(p->sabor, sabores[rand() % (MAX_QTD-1)]);
//     strcpy(p->borda, bordas[rand() % (MAX_QTD-1)]);
//     strcpy(p->acompanhamento, acompanhamentos[rand() % (MAX_QTD-1)]);
//     strcpy(p->bebida, bebidas[rand() % (MAX_QTD-1)]);
//     printf("--------------PEDIDO --------------\n");
//     printf("Sabor: %s \n", p->sabor);
//     printf("Bebida: %s \n", p->bebida);
//     printf("Bordas: %s \n", p->borda);
//     printf("Acompanhamentos: %s \n", p->acompanhamento);
// }