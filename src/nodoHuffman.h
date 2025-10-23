#ifndef NODOHUFFMAN_H
#define NODOHUFFMAN_H

// Clase nodoHuffman, representa un nodo en el árbol de Huffman.
class nodoHuffman {
    private:
        int frecuencia;
        char simbolo;
        nodoHuffman *hijoIzq;
        nodoHuffman *hijoDer;

    public:
        nodoHuffman();
        nodoHuffman(int frecuencia, char simbolo);
        int obtenerFrecuencia();
        void fijarFrecuencia(int frecuencia);
        char obtenerSimbolo();
        void fijarSimbolo(char simbolo);
        nodoHuffman *obtenerHijoIzq();
        nodoHuffman *obtenerHijoDer();
        void fijarHijoIzq(nodoHuffman *izq);
        void fijarHijoDer(nodoHuffman *der);
        bool esHoja();

};

#endif
