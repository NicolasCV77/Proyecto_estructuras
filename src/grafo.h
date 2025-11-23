#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Clase Grafo, representa un grafo dirigido y ponderado.
class Grafo {
    private:
        int filas;
        int columnas;
        vector<vector<double>> matrizAdyacencia;
        vector<double> distancias;
        vector<int> predecesores;
        int numVertices;

    public:
        Grafo();
        void construirGrafo(vector<vector<char>> secuencias);
        int indexar(int fila, int columna);
        void dijkstra(int filaInicio, int columnaInicio, int filaFin, int columnaFin);
        double obtenerDistancia(int filaFin, int columnaFin);
        double calcularPeso (char a, char b);
        vector<pair<int, int>> obtenerRuta(int filaInicio, int columnaInicio, int filaFin, int columnaFin);

};

#endif
