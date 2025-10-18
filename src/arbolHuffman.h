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
        bool insertar(int val);
        bool eliminar(int val);
        bool buscar(int val);
};


#endif
