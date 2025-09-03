#ifndef FASTA_H
#define FASTA_H

#include <iostream>
#include <vector>
#include <string>
#include "secuencia.h"

using namespace std;

class FASTA {
    private:
        // Conjunto de secuencias cargadas.
        vector<Secuencia> secuencias;
        vector <char> componentes;
        
    public:
        // Constructor.
        FASTA();

        // Gestión de secuencias.
        void agregarSecuencia(const Secuencia& secuencia);
        int totalSecuencias();

        // Operaciones principales.
        void listarSecuencias();
        void histograma(string descripcion);  
        void contarSubsecuencia(string sub);
        void enmascararSubsecuencia(string sub);

        // Acceso directo.
        vector<Secuencia> getSecuencias();
        
};

#endif