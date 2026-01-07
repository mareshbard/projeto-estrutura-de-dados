#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


void correctString(char *str)
{
    str[strlen(str) - 1] = '\0';
}

void clean()
{
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void bufferCleanner()
{
    char x = 'x';
    while(x != '\n') x = getchar();

}

void await()
{
    printf("\n\t\tAperte Enter para continuar:");
    bufferCleanner();
    
}
