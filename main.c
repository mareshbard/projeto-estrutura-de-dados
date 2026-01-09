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
typedef struct Pedido
{
 char sabor[55];
 char bebida[55];
 char borda[55];
 char acompanhamento[55];
} Pedido;

typedef struct Cliente
{
 char nome[40];
 Pedido pedido;
 struct Cliente *proximo; // conect na proximo
} Cliente;

typedef struct
{
 Cliente *primeiro;
 Cliente *ultimo;
 int size;
} Fila;

int cronometro(void *arg)
{
 for (int i = TEMPO_LIM; i > 0; i--)
 {
  if (atomic_load(&status) == 1)
  {

   return 0;
  }
  if (i == 20)
  {
   printf("Faltam %d segundos... \n", i);
   printf(">> ");
  }
  if (i == 10)
  {
   printf("Faltam %d segundos... \n", i);
   printf(">> ");
  }
  if (i <= 5)
  {
   printf("Faltam %d segundos... \n", i);
   printf(">> ");
  }
  struct timespec t = {.tv_sec = 1};
  thrd_sleep(&t, NULL);
 }
 if (atomic_load(&status) == 0)
 {
  atomic_store(&status, 2);
  system("cls || clear");
  printf("\n\nO cliente desistiu do pedido!\n");
  printf("Aperte ENTER para continuar\n");
 }
 return 0;
}

void AdicionarPessoa(Fila *f, char *nome, Pedido p)
{
 Cliente *novo = (Cliente *)malloc(sizeof(Cliente));
 if (novo == NULL)
 {
  printf("lascou leticia\n");
  return;
 }
 strcpy(novo->nome, nome);
 novo->pedido = p;
 novo->proximo = NULL;

 if (f->primeiro == NULL)
 {
  f->primeiro = novo;
  f->ultimo = novo;
 }
 else
 {
  f->ultimo->proximo = novo;
  f->ultimo = novo;
 }
}

Cliente *RemoverPessoa(Fila *p)
{
 if (p->primeiro == NULL)
  return NULL; // tem ninguem não fi

 Cliente *temp = p->primeiro;
 p->primeiro = p->primeiro->proximo;

 if (p->primeiro == NULL)
 {
  p->ultimo = NULL;
 }
    p->size--;
 return temp;
}

void criarPedido(Pedido *p)
{
 strcpy(p->sabor, sabores[rand() % (MAX_QTD)]);
 strcpy(p->borda, bordas[rand() % (MAX_QTD)]);
 strcpy(p->acompanhamento, acompanhamentos[rand() % (MAX_QTD)]);
 strcpy(p->bebida, bebidas[rand() % (MAX_QTD)]);
}

int estaVazia(Fila* fila){
    if(fila->size == 0) printf("🎉   Expediente finalizado! :)  🎉\n");
    return (fila->size == 0);
}

int estaCheia(Fila* fila, int qtd_clientes){
    if(fila->size == qtd_clientes){ 
        printf("\tIniciando expediente... Prepare os pedidos!\n");
        printf("\tVocê terá 10s para memorizar e 30s para atender ao cliente!\n");
    }

    return (fila->size == qtd_clientes);
}

int main()
{

 Fila pedidos; 
 pedidos.primeiro = NULL;
 pedidos.ultimo = NULL;

 thrd_t thread;
 srand(time(NULL));
 int item;
 pedidos.size = 0;
 int qtd_clientes = 4 + rand() % 3; // gera um numero aleatorio entre 4 e 7
 struct timespec t = {.tv_sec = 1};
 char ArrayNomesClientes[7][50]; // aq tem os nomes dos clientes 

 strcpy(ArrayNomesClientes[0], "Erivelton");
 strcpy(ArrayNomesClientes[1], "Mercy");
 strcpy(ArrayNomesClientes[2], "Remédio");
 strcpy(ArrayNomesClientes[3], "Jaciara");
 strcpy(ArrayNomesClientes[4], "Audriey");
 strcpy(ArrayNomesClientes[5], "Xerox");
 strcpy(ArrayNomesClientes[6], "Ping-pong");


 for (int i = 0; i < qtd_clientes ; i++)
 { 
  Pedido p;
  criarPedido(&p);
  AdicionarPessoa(&pedidos, ArrayNomesClientes[i], p);
  pedidos.size++;
 }
estaCheia(&pedidos, qtd_clientes);
 Cliente *atual;
 while ((atual = RemoverPessoa(&pedidos)) != NULL)
 {
  atomic_store(&status, 0);

  
  printf("-------------- PEDIDO --------------\n");
  printf("Cliente: %s\n", atual->nome);
  printf("Sabor: %s \n", atual->pedido.sabor);
  printf("Bebida: %s \n", atual->pedido.bebida);
  printf("Bordas: %s \n", atual->pedido.borda);
  printf("Acompanhamentos: %s \n", atual->pedido.acompanhamento);
  
  thrd_create(&thread, cronometro, NULL);
  PAUSA(10);
  system("cls || clear");
  estaCheia(&pedidos, qtd_clientes);
  do
  {
   // MOSTRAR MENU DE SABORES
   printf("Sabores: \n");
   printf("1 - Mussarela 🧀\n");
   printf("2 - Portuguesa 🥓\n");
   printf("3 - Quatro Queijos 🧀🧀🧀🧀\n");
   printf("4 - Frango Catupiry 🐔\n");
   printf("5 - Sorvete 🍦 \n\n");

   printf("Digite o numero referente ao sabor: \n");
   printf(">> ");
   char str[255];
   fgets(str,255,stdin);
   item = atoi(str);
   if(atomic_load(&status) == 2) break;
   system("cls || clear");
  } while (strcmp(sabores[item - 1], atual->pedido.sabor) != 0);
  
  if(atomic_load(&status) != 2)
  do
  {
   // MOSTRAR MENU DE BEBIDAS
   printf("1 - Suco de laranja 🍊\n");
   printf("2 - Suco de manga 🥭\n");
   printf("3 - Coca-Cola 🥤\n");
   printf("4 - Guaraná 🥤\n");
   printf("5 - Sem bebidas ❌\n\n");
   
  printf("Digite o numero referente à bebida: \n");
   printf(">> ");
   char str[255];
   fgets(str,255,stdin);
   item = atoi(str);
   
if(atomic_load(&status) == 2) break;
   system("cls || clear");
  } while (strcmp(bebidas[item - 1], atual->pedido.bebida) != 0);
  
  if(atomic_load(&status) != 2)
 
  do
  {
   // MOSTRAR MENU DE BORDAS
   printf("1 - Chocolate 🍫\n");
   printf("2 - Catupiry 🧀\n");
   printf("3 - Doce de leite 🍯\n");
   printf("4 - Cream cheese ⚪\n");
   printf("5 - Cheddar 🧀\n\n");
   printf("Digite o numero referente ao sabor da borda: \n");
   printf(">> ");
   char str[255];
   fgets(str,255,stdin);
   item = atoi(str);
if(atomic_load(&status) == 2) break;
   system("cls || clear");
  } while (strcmp(bordas[item - 1], atual->pedido.borda) != 0);
  
  if(atomic_load(&status) != 2)
  do
  {
   // MOSTRAR MENU DE acompanhamentos
   printf("1 - Ketchup 🍅\n");
   printf("2 - Maionese ⚪\n");
   printf("3 - Ketchup + Maionese 🍅⚪\n");
   printf("4 - Maionese temperada 🌶️🧴\n");
   printf("5 - Sem acompanhamentos ❌\n\n");
   
   printf("Digite o numero referente ao acompanhamento: \n");
   printf(">> ");
   char str[255];
   fgets(str,255,stdin);
   item = atoi(str);
   if(atomic_load(&status) == 2) break;
   if (strcmp(acompanhamentos[item - 1], atual->pedido.acompanhamento) == 0)
   {
    atomic_store(&status, 1);
    printf("Pedido finalizado!\n");
   }
  } while (strcmp(acompanhamentos[item - 1], atual->pedido.acompanhamento) != 0 && atomic_load(&status) != 2);

  thrd_join(thread, NULL);
  free(atual);
if(!estaVazia(&pedidos)){
 printf("\nPressione ENTER para o proximo cliente...\n");   
}
  system("cls || clear");
 }
 estaVazia(&pedidos);

 return 0;
}
