#include "nodoHuffman.h"
#include <iostream>

using namespace std;

// Constructores.
nodoHuffman::nodoHuffman() {
    this->hijoIzq = nullptr;
    this->hijoDer = nullptr;
}

nodoHuffman::nodoHuffman(int frecuencia, char simbolo) {
    this->frecuencia = frecuencia;
    this->simbolo = simbolo;
    this->hijoIzq = nullptr;
    this->hijoDer = nullptr;
}

// Métodos de acceso.
int nodoHuffman::obtenerFrecuencia() {
    return this->frecuencia;
}

void nodoHuffman::fijarFrecuencia(int frecuencia) {
    this->frecuencia = frecuencia;
}

char nodoHuffman:: obtenerSimbolo() {
    return this->simbolo;
}

void nodoHuffman::fijarSimbolo(char simbolo) {
    this->simbolo = simbolo;
}

nodoHuffman *nodoHuffman::obtenerHijoIzq() {
    return this->hijoIzq;
}

nodoHuffman *nodoHuffman::obtenerHijoDer() {
    return this->hijoDer;
}

void nodoHuffman::fijarHijoIzq(nodoHuffman *izq) {
    this->hijoIzq = izq;
}

void nodoHuffman::fijarHijoDer(nodoHuffman *der) {
    this->hijoDer = der;
}

bool nodoHuffman::esHoja() {
    return (this->hijoIzq == nullptr && this->hijoDer == nullptr);
}
