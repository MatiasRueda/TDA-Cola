#include "cola.h"
#include <stdlib.h>

typedef struct nodo nodo_t;
typedef void (*destruir_dato_t)(void*);

struct nodo {
    void* dato;
    nodo_t* prox;
};


struct cola {
    nodo_t* primero;
    nodo_t* ultimo;
};


nodo_t *nodo_crear(void* valor) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL) {
        return NULL;
    }
    nodo->prox = NULL;
    nodo->dato = valor;
    return nodo;
}

cola_t *cola_crear(void) {
    cola_t *cola = malloc(sizeof(cola_t));
    if (cola == NULL) {
        return NULL;
    }
    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

void cola_destruir(cola_t *cola,destruir_dato_t destruir_dato){
    while (!cola_esta_vacia(cola)) {
        void* dato = cola_desencolar(cola);
        if (destruir_dato) {
            destruir_dato(dato);
        }
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola) {
    return cola->primero == NULL;
}

bool cola_encolar(cola_t *cola, void *valor) {
    nodo_t* nodo = nodo_crear(valor);
    if (nodo == NULL) {
        return false;
    }
    if (cola_esta_vacia(cola)) {
        cola->ultimo = nodo;
        cola->primero = nodo;
    }

    else if (!cola_esta_vacia(cola)) {
        cola->ultimo->prox = nodo;
        cola->ultimo = nodo;
    }
    return true;
}

void *cola_ver_primero(const cola_t *cola) {
    return cola_esta_vacia(cola) ? NULL : cola->primero->dato;   
}

void *cola_desencolar(cola_t *cola) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }
    void* valor = cola->primero->dato;
    void* prox = cola->primero->prox;
    free(cola->primero);
    if (cola->primero == cola->ultimo) {
        cola->ultimo = NULL;
    }
    cola->primero = prox;
    return valor;
}

