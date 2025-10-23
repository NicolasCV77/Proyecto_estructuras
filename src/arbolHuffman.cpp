#include "arbolHuffman.h"
#include "queue"
#include "iostream"

using namespace std;

// Constructor y destructor.
arbolHuffman::arbolHuffman() {
    this->raiz = NULL;
}

// Verificar si el árbol está vacío.
bool arbolHuffman::esVacio() {
    return this->raiz == NULL;
}

// Construir el árbol de Huffman a partir de las frecuencias dadas.
void arbolHuffman::construir(map<char, int> &frecuencias) {
    // Declarar la cola de prioridad usando el comparador.
    priority_queue<nodoHuffman*, vector<nodoHuffman*>, ComparadorNodos> cola;

    // Crear un nodo hoja para cada símbolo y agregarlo a la cola.
    map<char, int>::iterator it;
    for (it = frecuencias.begin(); it != frecuencias.end(); it++) {
        nodoHuffman* nuevoNodo = new nodoHuffman(it->second, it->first);
        cola.push(nuevoNodo);
    }

    // Construir el árbol de Huffman.
    while (cola.size() > 1) {
        nodoHuffman *izquierdo = cola.top();
        cola.pop();

        nodoHuffman *derecho = cola.top();
        cola.pop();

        nodoHuffman *nuevoNodo = new nodoHuffman(izquierdo->obtenerFrecuencia() + derecho->obtenerFrecuencia(), '\0');
        nuevoNodo->fijarHijoIzq(izquierdo);
        nuevoNodo->fijarHijoDer(derecho);

        cola.push(nuevoNodo);
    }

    // La raíz del árbol es el único nodo restante en la cola.
    this->raiz = cola.top();

    // Generar los códigos de Huffman.
    string codigoActual;
    generarCodigos(this->raiz, codigoActual);
}

// Obtener los códigos de Huffman generados.
map<char, string> arbolHuffman::obtenerCodigos() {
    return codigos;
}

// Codificar un texto utilizando los códigos de Huffman.
string arbolHuffman::codificar(string &texto) {
    string textoCodificado;
    for (char simbolo : texto) {
        textoCodificado += codigos[simbolo];
    }

    return textoCodificado;
}

// Decodificar un texto codificado utilizando el árbol de Huffman.
string arbolHuffman::decodificar(string &textoCodificado) {
    string textoDecodificado;
    nodoHuffman *nodoActual = this->raiz;

    for (char bit : textoCodificado) {
        if (bit == '0') {
            nodoActual = nodoActual->obtenerHijoIzq();
        } else if (bit == '1') {
            nodoActual = nodoActual->obtenerHijoDer();
        }

        // Si llegamos a un nodo hoja, agregar el símbolo al texto decodificado.
        if (nodoActual->esHoja()) {
            textoDecodificado += nodoActual->obtenerSimbolo();

            // Volver a la raíz para el siguiente símbolo.
            nodoActual = this->raiz;
        }
    }

    return textoDecodificado;
}

// Función auxiliar para generar los códigos de Huffman.
void arbolHuffman::generarCodigos(nodoHuffman *nodo, string &codigoActual) {
    if (nodo == nullptr) {
        return;
    }

    // Si es un nodo hoja, guardar el código.
    if (nodo->esHoja()) {
        codigos[nodo->obtenerSimbolo()] = codigoActual;
    }

    // Recorrer hijo izquierdo con '0' añadido al código.
    codigoActual.push_back('0');
    generarCodigos(nodo->obtenerHijoIzq(), codigoActual);
    codigoActual.pop_back();

    // Recorrer hijo derecho con '1' añadido al código.
    codigoActual.push_back('1');
    generarCodigos(nodo->obtenerHijoDer(), codigoActual);
    codigoActual.pop_back();
}
