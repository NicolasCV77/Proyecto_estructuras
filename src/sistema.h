#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <string>
#include "FASTA.h"

using namespace std;

class Sistema {
    private:
        FASTA fasta;

    public:
        // Constructor.
        Sistema();

        // Manejo de archivos.
        void cargarArchivo(string nombreArchivo);
        void guardarArchivo(string nombreArchivo);

        // Acceso al objeto FASTA.
        FASTA& getFASTA();
        
};

#endif