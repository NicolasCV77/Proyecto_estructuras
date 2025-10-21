#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H

#include "nodoHuffman.h"
#include <map>
#include <string>

using namespace std;

// Comparador de nodos, el menor valor de frecuencia tiene mayor prioridad.
struct ComparadorNodos {
    bool operator()(nodoHuffman* a, nodoHuffman* b) {
        if (a->obtenerFrecuencia() == b->obtenerFrecuencia()) {
            return a->obtenerSimbolo() > b->obtenerSimbolo();
        }
        return a->obtenerFrecuencia() > b->obtenerFrecuencia();
    }
};

// Clase Árbol de Huffman.
class arbolHuffman {
    private:
        // Raíz del árbol.
        nodoHuffman *raiz;
        // Mapa de códigos de Huffman.
        map<char, string> codigos;

        // Funciones auxiliares.
        void generarCodigos(nodoHuffman *nodo, string &codigoActual);
        void destruirArbol(nodoHuffman *nodo);

    public:
        arbolHuffman();
        ~arbolHuffman();
        bool esVacio();
        void construir(map<char, int> &frecuencias);
        map<char, string> obtenerCodigos();
        string codificar(string &texto);
        string decodificar(string &textoCodificado);
        void mostrarPreOrden();

};

#endif