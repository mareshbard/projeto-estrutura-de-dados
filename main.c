#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <threads.h>
#include <stdatomic.h>
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
    

int cronometro(void *arg) {
	for(int i = TEMPO_LIM; i>0; i--) {
		if(atomic_load(&status)==1) {

			return 0;
		}
		if(i == 20) {
			printf("Faltam %d segundos... \n", i);
		}
		if(i == 10) {
			printf("Faltam %d segundos... \n", i);
		}
		if(i <=5 ) {
			printf("Faltam %d segundos... \n", i);
		}
		struct timespec t = {.tv_sec = 1};
		thrd_sleep(&t, NULL);
	}
	if(atomic_load(&status)==0) {
		atomic_store(&status, 2);
		printf("\n\nO cliente desistiu do pedido!\n");
		printf("Aperte ENTER para continuar\n");
	}
	return 0;
}
typedef struct {
	Cliente *primeiro;
	Cliente *ultimo;
} Fila;

void criarPedido(Pedido *p) {

	strcpy(p->sabor, sabores[rand() % (MAX_QTD)]);
	strcpy(p->borda, bordas[rand() % (MAX_QTD)]);
	strcpy(p->acompanhamento, acompanhamentos[rand() % (MAX_QTD)]);
	strcpy(p->bebida, bebidas[rand() % (MAX_QTD)]);
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
	int qtd_clientes = rand() % 4 + 3;
	printf("%d", qtd_clientes);

	do {
		atomic_store(&status, 0);
		criarPedido(&p1);

		PAUSA(10);
		system("cls || clear");
		printf("Faça o pedido! ");
		thrd_create(&thread, cronometro, NULL);

		do {
		    // MOSTRAR MENU DE SABORES
			printf("Sabores: \n");
			printf("1 - Mussarela\n");
			printf("2 - Portuguesa\n");
			printf("3 - Quatro Queijos\n");
			printf("4 - Drango Catupiry\n");
			printf("5 - sorvete\n\n");

		    printf("Digite o numero referente ao sabor: \n");
			printf(">> ");
			scanf("%d", &item);
		} while(strcmp(sabores[item], p1.sabor)!=0);
		do {
		    // MOSTRAR MENU DE BEBIDAS
		    printf("1 - Suco de laranja\n");
			printf("2 - Suco de manga\n");
			printf("3 - Coca-Cola\n");
			printf("4 - Guaraná\n");
			printf("5 - Sem bebidas\n\n");

			printf("Digite o numero referente a bebida: \n");
			printf(">> ");
			scanf("%d", &item);
		} while(strcmp(bebidas[item], p1.bebida)!=0);
		do {
		    // MOSTRAR MENU DE BORDAS
		    printf("1 - Chocolate\n");
			printf("2 - Catupiry\n");
			printf("3 - Doce de leite\n");
			printf("4 - Cream cheese\n");
			printf("5 - Cheddar\n\n");

			printf("Digite o numero referente ao sabor da borda:\n");
			printf(">> ");
			scanf("%d", &item);
		} while(strcmp(bordas[item], p1.borda)!=0);
		do {
		    // MOSTRAR MENU DE acompanhamentos
		    printf("1 - Ketchup\n");
			printf("2 - Maionese\n");
			printf("3 - Letchup + Maionese\n");
			printf("4 - Maionese temperada\n");
			printf("5 - Sem acompalhamentos\n\n");

			printf("Digite o numero referente ao acompanhamento: \n");
			printf(">> ");
			scanf("%d", &item);
			if(strcmp(acompanhamentos[item], p1.acompanhamento)==0){
			    atomic_store(&status, 1);
			    printf("Pedido finalizado!\n");
			}
		} while(strcmp(acompanhamentos[item], p1.acompanhamento)!=0 && atomic_load(&status)!=2);
		
		if(atomic_load(&status) == 2) {
			printf("Tarde demais! Cliente foi embora\n");
		}
		qtd_clientes--;
		thrd_join(thread, NULL);
	} while(qtd_clientes>0);
	printf("Expediente finalizado! :)");

	return 0;
}