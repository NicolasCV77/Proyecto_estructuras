#ifndef FASTA_H
#define FASTA_H

#include <iostream>
#include <vector>
#include <string>
#include "secuencia.h"

using namespace std;

// Clase FASTA, representa un conjunto de secuencias.
class FASTA {
    private:
        // Conjunto de secuencias, lista de equivalencias y límite de bases exactas.
        vector<Secuencia> secuencias;
        vector<vector<char>> componentes;
        int limiteExactas;
        
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

        // Funciones de apoyo.
        int contarPosiblesBases(Secuencia secuencia);
        bool subEncontrada (vector <char> bases, vector <char> secuencia, int inicio);

        // Métodos de acceso.
        vector<char> getEquivalencias(char base);
        vector<Secuencia>& getSecuencias();
        vector<vector<char>>& getComponentes();
        
};

#endif
