#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Clase Grafo, representa un grafo dirigido y ponderado.
class Grafo {
    private:
        vector<vector<double>> matrizAdyacencia;
        vector<double> distancias;
        vector<int> predecesores;
        int numVertices;
        
    public:
        ~Grafo();
};

#endif
