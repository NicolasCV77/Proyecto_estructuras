#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <string>

#include "FASTA.h"

using namespace std;

// Clase Sistema, representa el núcleo del programa.
class Sistema {
    private:
    // Objeto que administra las secuencias FASTA.
        FASTA fasta;

    public:
        // Manejo de archivos. 
        void cargarArchivo(string nombreArchivo);
        void guardarArchivo(string nombreArchivo);

        // Referencia del objeto FASTA.
        FASTA& getFASTA();
        
};

#endif