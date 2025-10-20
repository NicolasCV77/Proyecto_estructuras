#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H

#include "nodoHuffman.h"
#include <map>
#include <string>

using namespace std;

// Alias para el tipo de función comparadora.
typedef bool (*Comparador)(nodoHuffman*, nodoHuffman*);

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
        bool compararNodos(nodoHuffman* a, nodoHuffman* b);

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