#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <iostream>
#include <string>
#include <vector>

#include "grafo.h"

using namespace std;

// Clase Secuencia, representa una secuencia de bases.
class Secuencia {
    private:
        // Atributos.
        Grafo grafo;
        vector <char> bases;    
        string descripcion; 
        int ancho;

    public:
        // Constructor.
        Secuencia(const string& descripcion, const vector<char>& linea, int anchoLinea);

        // Construir el grafo asociado a la secuencia.
        void construirGrafo();
        Grafo& getGrafo();

        // Métodos de acceso.
        string getDescripcion();
        vector <char> getBases();
        int getAncho();

        // Operaciones principales.
        int contarBase(char base);
        int enmascarar(int inicio, int fin);

};

#endif
