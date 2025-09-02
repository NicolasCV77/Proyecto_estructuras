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
    bool cargarArchivo(string nombreArchivo);
    bool guardarArchivo(string nombreArchivo);

    // Acceso al objeto FASTA.
    FASTA& getFASTA();
};

#endif