#define _POSIX_C_SOURCE 200809L 
#include "strutil.h"
#include "pila.h"
#include "funciones_dc.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#define TAM_MAX_LINEA 90
#define SUMA '+'
#define RESTA '-'
#define MULT '*'
#define DIV '/'
#define POT '^'
#define TERN '?'

/*
gcc -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion7 dc.c strutil.c pila.c funciones_dc.c  -o pruebas
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas < ejemplodc.txt

*/


/*****************
 *  Auxiliares
 * ***************/

bool _dc(pila_t* pila){
    if (pila_esta_vacia(pila))  return true;
    
    char* desapilado = pila_desapilar(pila);

    if (!_dc(pila)){
        free(desapilado);
        return false;
    }
    if (!es_operador(desapilado))   return pila_apilar(pila,(desapilado));

    bool operacion = true;

    if (strlen(desapilado) == 1){
        if (desapilado[0] == SUMA)     operacion = aritmetica(pila,sumar);
        if (desapilado[0] == RESTA)    operacion = aritmetica(pila,restar);
        if (desapilado[0] == MULT)     operacion = aritmetica(pila,multiplicar);
        if (desapilado[0] == DIV)      operacion = aritmetica(pila,dividir);
        if (desapilado[0] == POT)      operacion = potencia(pila);
        if (desapilado[0] == TERN)     operacion = ternaria(pila);
    }

    if (strlen(desapilado)>1){
        char str_raiz[5] = "sqrt";
        char str_log[4] = "log";
        if (strcmp(desapilado, (char*)&str_raiz)== 0)     operacion = raiz(pila);
        if (strcmp(desapilado, (char*)&str_log) == 0)     operacion = loga(pila);
    }
    free(desapilado);
    return operacion;
}

/*****************
 *  principales
 * ***************/

void dc(pila_t* pila){
    if (pila_esta_vacia(pila))  return;
    if (!_dc(pila)){
        liberar_elementos_pila(pila);
        return;
    }
    
    char* desap = (char*)pila_desapilar(pila);
    if (!pila_esta_vacia(pila)){
        fprintf(stdout,"ERROR\n");
        liberar_elementos_pila(pila);
    } else {
        fprintf(stdout,"%s\n",desap);
    }
    free(desap);
    return;
}

char* rstrip(char* s){
    size_t tam;
    char *fin;

    tam = strlen(s);

    if (!tam)  return s;

    fin = s + tam - 1;
    if (*(fin) == '\n'){
        *(fin) = '\0';
    }
    return s;
}

int main(int argc, char* argv[]){

    FILE* archivo;
    if (!(archivo = stdin))   return -1;
    char linea_archivo[TAM_MAX_LINEA];
    while(fgets(linea_archivo,TAM_MAX_LINEA,archivo) != NULL){
        char* linea = rstrip(linea_archivo);
        pila_t* pila = pila_crear();
        if(!pila)   return -1;

        char sep = ' ';
        char** elems = split(linea,sep);
        if (!elems) return -1;
        int i = 0;

        while (elems[i] != NULL){
            if (strcmp(elems[i],"") != 0)   pila_apilar(pila,strdup(elems[i]));
            i++;
        }
        dc(pila);
        free_strv(elems);
        pila_destruir(pila);
    }
    return 0;
}