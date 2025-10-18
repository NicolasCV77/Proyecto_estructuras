#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H

#include "nodoHuffman.h"

class arbolHuffman {
    protected:
        nodoHuffman *raiz;
    public:
        arbolHuffman();
        ~arbolHuffman();
        bool esVacio();
        nodoHuffman datoRaiz();
        int altura();
        int tamano();
        bool insertar(int val);
        bool eliminar(int val);
        bool buscar(int val);
        void preOrden();
        void postOrden();
        void inOrden();
        void nivelOrden();
};


#endif
