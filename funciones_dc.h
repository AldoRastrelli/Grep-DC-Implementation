#ifndef FUNC_H
#define FUNC_

#include <stdbool.h>
#include "pila.h"

/* Recibe una pila con elementos y una función operación (que puede ser
suma, resta, multiplicación y división).
Aplica operación a los elementos correspondientes de la pila.
Si la operación no pudo realizarse (no hay cantidad suficiente de elementos,
la pila está vacía, el elemento desapilado no es un entero, se quiere dividir
por 0), devuelve false e imprime ERROR.
De lo contrario, devuelve true. */
bool aritmetica(pila_t* pila, int operacion(int a, int b));

/* Suma dos elementos y devuelve el resultado */
int sumar(int a, int b);

/* Resta dos elementos y devuelve el resultado */
int restar(int a, int b);

/* Multiplica dos elementos y devuelve el resultado */
int multiplicar(int a, int b);

/* Divide dos elementos y devuelve el resultado */
int dividir(int a, int b);

/* Recibe una pila con elementos y desapila los últimos 3 elementos (en tope).
En caso que el último operando sea distinto de 0, devuelve el penúltimo,
en caso de ser 0 debe devolver el antepenúltimo.
Si la operación no pudo realizarse, devuelve false e imprime ERROR.
De lo contrario, devuelve true. */
bool ternaria(pila_t* pila);

/* Recibe una pila con elementos y desapila el último (el tope).
Busca la raíz del elemento y devuelve si parte entera.
Si el elemento es menor a 0, la pila está vacía o el elemento
no es un entero, devuelve false e imprime ERROR.
De lo contrario, devuelve true. */
bool raiz(pila_t* pila);

/* Busca la parte entera de la raíz de un número */
int _raiz(int elem, int i);

/* Recibe una pila con elementos y desapila los últimos 2 elementos (en tope).
Luego eleva el último por el anterior.
Si la operación no pudo realizarse (cantidad insuficiente de operandos,
el elemento desapilado no es un número, el anterior es menor a cero),
devuelve false e imprime ERROR.
De lo contrario, devuelve true. */
bool potencia(pila_t* pila);

/* Calcula la potencia dada una base y un exponente */
int _pot(int base, int expo);

/* Recibe una pila con elementos y desapila los últimos 2 elementos (en tope).
LUego calcular la parte entera del logaritmo del último operando,
en base del penúltimo.
Si la operación no pudo realizarse (cantidad insuficiente de operandos,
el elemento desapilado no es un número, el penúltimo es menor a cero),
devuelve false e imprime ERROR.
De lo contrario, devuelve true. */
bool loga(pila_t* pila);

/* Calcula un logaritmo dado un argumento y una base */
int _log(int arg, int base, int acum, int expo);

/* Devuelve true si el elemento pasado por parámetro
es un operador y false si no lo es */
bool es_operador(char* str);

/* Libera todos los elementos apilados en una pila,
sabiendo que dichos elementos son de memoria dinámica.
Pre: la pila debe haber sido creada y contener únicamente elementos
de memoria dinámica. */
void liberar_elementos_pila(pila_t* pila);

#endif