#define _POSIX_C_SOURCE 200809L 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "funciones_dc.h"
#include "pila.h"
#define SUMA '+'
#define RESTA '-'
#define MULT '*'
#define DIV '/'
#define POT '^'
#define TERN '?'
#define MAX_STR 128

void liberar_elementos_pila(pila_t* pila){
    while (!pila_esta_vacia(pila)){
        char* desapilado = pila_desapilar(pila);
        if (desapilado) free(desapilado);
    }
}

bool aritmetica(pila_t* pila, int operacion(int a, int b)){
    char* a = (char*)pila_desapilar(pila);
    char* b = (char*)pila_desapilar(pila);

    if (!a || !b){
        fprintf(stdout,"ERROR\n");
        if (a) free(a);
        if (b) free(b);
        liberar_elementos_pila(pila);
        return false;
    }
    if (es_operador(a) || es_operador(b)){
        fprintf(stdout,"ERROR\n");
        free(a);
        free(b);
        liberar_elementos_pila(pila);
        return false;
    }
    if (operacion == dividir && atoi(b) == 0){
        fprintf(stdout,"ERROR\n");
        free(a);
        free(b);
        liberar_elementos_pila(pila);
        return false;
    }
    int resultado = operacion(atoi(a),atoi(b));
    char str[MAX_STR];
    sprintf(str,"%d",resultado);
    char* res_str = strdup((const char*)&str);
    bool apilado = pila_apilar(pila,res_str);
    free(a);
    free(b);
    return apilado;
}

int sumar(int a, int b){
    return a + b;
}

int restar(int a, int b){
    return a - b;
}

int multiplicar(int a, int b){
    return a * b;
}

int dividir(int a, int b){
    return a / b;
}

bool ternaria(pila_t* pila){
    char* a = pila_desapilar(pila);
    char* b = pila_desapilar(pila);
    char* c = pila_desapilar(pila);

    if (!a || !b || !c){
        fprintf(stdout,"ERROR\n");
        if (a)  free(a);
        if (b)  free(b);
        if (c)  free(c);
        liberar_elementos_pila(pila);
        return false;
    }
    if (es_operador(a), es_operador(b), es_operador(c)){
        fprintf(stdout,"ERROR\n");
        free(a);
        free(b);
        free(c);
        liberar_elementos_pila(pila);
        return false;
    }
    int resultado = atoi(a) == 0 ? atoi(c) : atoi(b);
    char str[MAX_STR];
    sprintf(str,"%d",resultado);
    char* res_str = strdup((const char*)&str);
    bool apilado = pila_apilar(pila,res_str);
    free(a);
    free(b);
    free(c);
    return apilado;
}

bool raiz(pila_t* pila){
    char* elem = pila_desapilar(pila);
    if (!elem){
        fprintf(stdout,"ERROR\n");
        if (elem)   free(elem);
        liberar_elementos_pila(pila);
        return false;
    }
    if (es_operador(elem)){
        fprintf(stdout,"ERROR\n");
        free(elem);
        liberar_elementos_pila(pila);
        return false;
    }
    if (atoi(elem) < 0){
        fprintf(stdout,"ERROR\n");
        free(elem);
        liberar_elementos_pila(pila);
        return false;
    }
    int resultado = _raiz(atoi(elem),1);
    char str[MAX_STR];
    sprintf(str,"%d",resultado);
    char* res_str = strdup((const char*)&str);
    bool apilado = pila_apilar(pila,res_str);
    free(elem);
    return apilado;
}

int _raiz(int elem, int i){
    if ((elem == 0) || (elem == 1) )    return elem;
    if (i * i > elem){
        return i - 1;
    }
    return _raiz(elem,i + 1);
}

bool potencia(pila_t* pila){
    char* base = pila_desapilar(pila);
    char* expo = pila_desapilar(pila);
    if (!base || !expo){
        fprintf(stdout,"ERROR\n");
        if (base)   free(base);
        if(expo)    free(expo);
        liberar_elementos_pila(pila);
        return false;
    }
    if (es_operador(base) || es_operador(expo)){
        fprintf(stdout,"ERROR\n");
        free(base);
        free(expo);
        liberar_elementos_pila(pila);
        return false;
    }
    if (atoi(expo) < 0){
        fprintf(stdout,"ERROR\n");
        free(base);
        free(expo);
        liberar_elementos_pila(pila);
        return false;
    }
    int resultado = _pot(atoi(base),atoi(expo));
    char str[MAX_STR];
    sprintf(str,"%d",resultado);
    char* res_str = strdup((const char*)&str);
    bool apilado = pila_apilar(pila,res_str);
    free(base);
    free(expo);
    return apilado;
}

int _pot(int base, int expo){
    if (expo == 0)  return 1;
    if (base == 0)  return base;
    int pot_parcial = _pot(base, expo / 2);
    
    int resultado = pot_parcial * pot_parcial;
    if (expo % 2 != 0) resultado *= base;
    
    return resultado;
}

bool loga(pila_t* pila){
    char* a = pila_desapilar(pila);
    char* b = pila_desapilar(pila);
    if (!a || !b){
        fprintf(stdout,"ERROR\n");
        if (a)  free(a);
        if (b)  free(b);
        liberar_elementos_pila(pila);
        return false;
    }
    if (es_operador(a) || es_operador(b)){
        fprintf(stdout,"ERROR\n");
        free(a);
        free(b);
        liberar_elementos_pila(pila);
        return false;
    }
    if (atoi(b) <= 1){
        fprintf(stdout,"ERROR\n");
        free(a);
        free(b);
        liberar_elementos_pila(pila);
        return false;
    }
    if (atoi(a) <= 0){
        fprintf(stdout,"ERROR\n");
        free(a);
        free(b);
        liberar_elementos_pila(pila);
        return false;
    }
    int resultado = _log(atoi(a),atoi(b),1,1);
    char str[MAX_STR];
    sprintf(str,"%d",resultado);
    char* res_str = strdup((const char*)&str);
    bool apilado = pila_apilar(pila,res_str);
    free(a);
    free(b);
    return apilado;
}

int _log(int arg, int base, int acum, int expo){
    acum *= base;
    if (acum == arg) return expo;
    if (acum > arg) return expo-1;
    return _log(arg, base, acum, ++expo);
    
}

bool es_operador(char* str){
    if (strlen(str) == 1){
        bool suma = str[0] == SUMA;
        bool resta = str[0] == RESTA;
        bool multip = str[0] == MULT;
        bool division = str[0] == DIV;
        bool pot = str[0] == POT;
        bool tern = str[0] == TERN;

        return (suma || resta || multip || division || pot || tern);
    }

    char raiz[5] = "sqrt\0";
    char* p_raiz = raiz;
    char logaritmo[4] = "log\0";
    char* p_logaritmo = logaritmo;
    
    bool es_raiz = strcmp(str,(const char*)p_raiz) == 0;
    bool es_log = strcmp(str,(const char*)p_logaritmo) == 0;
    return (es_raiz || es_log);
}
