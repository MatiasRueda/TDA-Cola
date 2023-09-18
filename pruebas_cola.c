#include "cola.h"
#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

// Se pueda crear y destruir correctamente la estructura.
static void prueba_cola_crear(void) {
    cola_t *cola = cola_crear();
    print_test("Chequeando que la cola haya sido creada",cola != NULL);
    print_test("Chequeando que la cola esta vacia", cola_esta_vacia(cola));
    cola_destruir(cola,NULL);
}

// Se puedan apilar elementos, que al desapilarlos se mantenga el invariante de pila.
static void prueba_encolar_desencolar(void) {
    cola_t *cola = cola_crear();
    int prueba1 = 1;
    int prueba2 = 2;
    int prueba3 = 3;
    int prueba4 = 4;
    int* direccion1 = &prueba1;
    int* direccion2 = &prueba2;
    int* direccion3 = &prueba3;
    int* direccion4 = &prueba4;
    print_test("Se pudo colar una direccion1", cola_encolar(cola,direccion1));
    print_test("Chequeo lo primero que hay en la cola es la direccion1",cola_ver_primero(cola) == direccion1);
    print_test("Se pudo colar una direccion2", cola_encolar(cola,direccion2));
    print_test("Chequeo lo primero que hay en la cola es la direccion1",cola_ver_primero(cola) == direccion1);
    print_test("Se pudo colar una direccion3", cola_encolar(cola,direccion3));
    print_test("Chequeo lo primero que hay en la cola es la direccion1",cola_ver_primero(cola) == direccion1);
    print_test("Se pudo colar una direccion4", cola_encolar(cola,direccion4));
    print_test("Chequeo lo primero que hay en la cola es la direccion1",cola_ver_primero(cola) == direccion1);
    print_test("Desencolo direccion1",cola_desencolar(cola) == direccion1);
    print_test("Chequeo que lo primero que hay en la cola es la direccion2", cola_ver_primero(cola) == direccion2);
    print_test("Desencolo direccion2",cola_desencolar(cola) == direccion2);
    print_test("Chequeo que lo primero que hay en la cola es la direccion3", cola_ver_primero(cola) == direccion3);
    print_test("Desencolo direccion3",cola_desencolar(cola) == direccion3);
    print_test("Chequeo que lo primero que hay en la cola es la direccion3", cola_ver_primero(cola) == direccion4);
    print_test("Desencolo direccion4",cola_desencolar(cola) == direccion4);
    print_test("Chequeo que la cola esta vacia", cola_esta_vacia(cola));
    cola_destruir(cola,NULL);
}

// Prueba de Volumen
static void prueba_volumen(void) {
    cola_t* cola = cola_crear();
    int* primero = malloc(sizeof(int));
    cola_encolar(cola,primero);
    int volum = 100000;
    size_t i = 0;
    bool ok = true; 
    int** orden_cola = malloc(sizeof(int*)*volum);
    orden_cola[0] = primero;
    for (i = 1 ;i < volum; i++) {
        int* direc = malloc(sizeof(int));
        orden_cola[i] = direc;
        ok &= cola_encolar(cola,direc);
        ok &= cola_ver_primero(cola) == primero;
    }
    print_test("Se pudo encolar 100000 correctamente",ok);
    i = 0;
    ok = true;
    while (!cola_esta_vacia(cola)) {
        int* guardado = cola_ver_primero(cola);
        ok &= (guardado == orden_cola[i]); 
        ok &= (cola_ver_primero(cola) == cola_desencolar(cola));
        free(guardado);
        i++;
    }
    free(orden_cola);
    print_test("Se pudo desencolar 100000 correctamente",ok);
    print_test("Comprobando que la cola este vacia", cola_esta_vacia(cola));
    print_test("Verificando que NO se pueda desapilar en una cola vacia en la cual se encolo y se desencolo", cola_desencolar(cola) == NULL);
    print_test("Verificando que NO se pueda desapilar en una cola vacia en la cual se encolo y se desencolo", cola_ver_primero(cola) == NULL);
    cola_destruir(cola,NULL);
}

// Prueba con NULL
static void prueba_cola_NULL(void) {
    cola_t* cola = cola_crear();
    print_test("Encolo NULL", cola_encolar(cola,NULL));
    print_test("Verifico que la pila deja de estar vacia", !cola_esta_vacia(cola));
    print_test("Desencolo NULL", cola_desencolar(cola) == NULL);
    cola_destruir(cola,NULL);
}

// Condición de borde: comprobar que al desencolar hasta que está vacía hace que la cola se comporte como recién creada.
static void prueba_cola_vacia_encolar_y_desencolar(void) {
    cola_t* cola = cola_crear();
    int prueba1;
    int prueba2;
    int* direccion1 = &prueba1;
    int* direccion2 = &prueba2;
    print_test("Encolando direccion1", cola_encolar(cola,direccion1));
    print_test("Encolando direccion2", cola_encolar(cola,direccion2));
    print_test("Desencolo la direccion1", cola_desencolar(cola) == direccion1);
    print_test("Desencolo la direccion2", cola_desencolar(cola) == direccion2);
    print_test("Comprobando que la cola este vacia", cola_esta_vacia(cola));
    print_test("Verifico que NO se pueda desencolar en una cola recien creada", cola_desencolar(cola) == NULL);
    print_test("Verifico que NO se pueda ver el primer elemento en una cola recien creada", cola_ver_primero(cola) == NULL);
    print_test("Encolo un elemento",cola_encolar(cola,direccion1));
    print_test("Verifico que el elemento recien encolado es el primero",cola_ver_primero(cola));
    print_test("Desencolo el elemento",cola_desencolar(cola) == direccion1);
    print_test("Y verifico que la cola este vacia nuevamente",cola_esta_vacia(cola));
    cola_destruir(cola,NULL);
}
//Condición de borde: las acciones de desencolar y ver primero en una pila recién creada son inválidas.
static void prueba_cola_vacia_desencolar_y_ver_primero(void) {
    cola_t* cola = cola_crear();
    print_test("Verifico que la cola esta vacia",cola_esta_vacia(cola));
    print_test("Verifico que NO se pueda desencolar en una cola recien creada", cola_desencolar(cola) == NULL);
    print_test("Verifico que NO se pueda ver el primer elemento en una cola recien creada", cola_ver_primero(cola) == NULL);
    cola_destruir(cola,NULL);
}

//Condición de borde: la acción de esta vacía en una cola recién creada es verdadero.
static void prueba_cola_vacia(void) {
    cola_t* cola = cola_crear();
    print_test("Verificando si la acción de esta vacía en una cola recién creada es verdadero.", cola_esta_vacia(cola));
    cola_destruir(cola,NULL);
}
// Condición de borde: las acciones de desencolar y ver primero en una cola a la que se le encolo y desencolo hasta estar vacía son inválidas.
static void prueba_comportamiento_cola_desencolada(void) {
    cola_t* cola = cola_crear();
    int prueba1 = 4;
    int* direccion1 = &prueba1;
    print_test("Encolo un elemento",cola_encolar(cola,direccion1));
    print_test("Desencolo el elemento",cola_desencolar(cola) == direccion1);
    print_test("Verifico que NO se pueda desencolar en una cola recien creada", cola_desencolar(cola) == NULL);
    print_test("Verifico que NO se pueda ver el primer elemento en una cola recien creada", cola_ver_primero(cola) == NULL);
    cola_destruir(cola,NULL);
}

// Pruebo una forma distinta de destruir la cola, pasandole como parametro una funcion
static void prueba_destruir_pila(void) {
    cola_t* cola = cola_crear();
    pila_t* pila = pila_crear();
    int numero;
    int* direc = &numero;
    print_test("Agrego un elemento a la pila",pila_apilar(pila,direc));
    print_test("Verifico que se pueda encolar una pila",cola_encolar(cola,pila));
    print_test("Destruyo la cola",true);
    cola_destruir(cola,pila_destruir);
}

static void prueba_destruir_cola_con_NULL(void){
    cola_t* cola = cola_crear();
    int numero;
    int* direc = &numero;
    print_test("Encolo una direccion",cola_encolar(cola,direc));
    print_test("Destruyo la cola",true);
    cola_destruir(cola,NULL);
}


void pruebas_cola_estudiante() {
    prueba_cola_crear();
    prueba_encolar_desencolar();
    prueba_volumen();
    prueba_cola_NULL();
    prueba_cola_vacia_encolar_y_desencolar();
    prueba_cola_vacia_desencolar_y_ver_primero();
    prueba_cola_vacia();
    prueba_comportamiento_cola_desencolada();
    prueba_destruir_pila();
    prueba_destruir_cola_con_NULL();
}


#ifndef CORRECTOR

int main(void) {
    pruebas_cola_estudiante();
    return 0;
}

#endif