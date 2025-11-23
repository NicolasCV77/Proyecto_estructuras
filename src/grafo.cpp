#include "grafo.h"

#include <queue>
#include <cmath>

using namespace std;

// Constructor.
Grafo::Grafo() {
    filas = 0;
    columnas = 0;
    numVertices = 0;
}

// Construye el grafo desde una matriz irregular de caracteres.
void Grafo::construirGrafo(vector<vector<char>> secuencias) {
    filas = secuencias.size();
    columnas = 0;

    // Determinar cuántas columnas máximas tiene la matriz.
    for (int i = 0; i < filas; i++) {
        int tamano = secuencias[i].size();
        if (tamano > columnas) {
            columnas = tamano;
        }
    }
    numVertices = filas * columnas;

    // Crear la matriz de adyacencia (numVertices x numVertices).
    matrizAdyacencia.clear();
    matrizAdyacencia.resize(numVertices);

    for (int i = 0; i < numVertices; i++) {
        matrizAdyacencia[i].resize(numVertices);
        for (int j = 0; j < numVertices; j++) {
            matrizAdyacencia[i][j] = 0.0;
        }
    }

    // Movimientos posibles.
    int df[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    // Llenar la matriz de adyacencia.
    for (int f = 0; f < filas; f++) {
        int totalColsFila = secuencias[f].size();

        for (int c = 0; c < totalColsFila; c++) {
            int u = indexar(f, c);
            char baseU = secuencias[f][c];

            // Vecinos.
            for (int k = 0; k < 4; k++) {
                int numFilas = f + df[k];
                int numColumnas = c + dc[k];

                // Validar límites.
                if (numFilas < 0 || numFilas >= filas) { continue; }
                if (numColumnas < 0) { continue; }
                if (numColumnas >= (int)secuencias[numFilas].size()) { continue; }

                int v = indexar(numFilas, numColumnas);
                char baseV = secuencias[numFilas][numColumnas];
                matrizAdyacencia[u][v] = calcularPeso(baseU, baseV);
            }
        }
    }
}

// Convertir fila/columna a índice único.
int Grafo::indexar(int fila, int columna) {
    return fila * columnas + columna;
}

// Algoritmo de Dijkstra para ruta más corta.
void Grafo::dijkstra(int filaInicio, int columnaInicio, int filaFin, int columnaFin) {
    distancias.clear();
    distancias.resize(numVertices);

    predecesores.clear();
    predecesores.resize(numVertices);

    // Inicializar distancias y predecesores.
    for (int i = 0; i < numVertices; i++) {
        distancias[i] = INFINITY;
        predecesores[i] = -1;
    }

    int inicio = indexar(filaInicio, columnaInicio);
    int destino = indexar(filaFin, columnaFin);
    distancias[inicio] = 0.0;

    // Cola de prioridad, distancia - nodo.
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> cola;
    cola.push(make_pair(0.0, inicio));

    // Procesar nodos.
    while (!cola.empty()) {
        pair<double, int> actual = cola.top();
        cola.pop();

        double distanciaActual = actual.first;
        int nodoActual = actual.second;

        if (distanciaActual > distancias[nodoActual]) { continue; }

        // Explorar vecinos.
        for (int vecino = 0; vecino < numVertices; vecino++) {
            double pesoArista = matrizAdyacencia[nodoActual][vecino];

            if (pesoArista > 0.0) {
                double nuevaDistancia = distancias[nodoActual] + pesoArista;
                if (nuevaDistancia < distancias[vecino]) {
                    distancias[vecino] = nuevaDistancia;
                    predecesores[vecino] = nodoActual;
                    cola.push(pair<double, int>(distancias[vecino], vecino));
                }
            }
        }
    }
}

// Obtener distancia a la celda final.
double Grafo::obtenerDistancia(int filaFin, int columnaFin) {
    int idx = indexar(filaFin, columnaFin);
    return distancias[idx];
}

// Calcular el peso entre dos nodos basándose en sus caracteres.
double Grafo::calcularPeso(char a, char b) {
    int x = (int)a;
    int y = (int)b;
    int diferencia = x - y;

    if (diferencia < 0) { 
        diferencia = -diferencia; 
    }

    double denominador = 1.0 + (double)diferencia;
    return 1.0 / denominador;
}

// Reconstruir ruta desde inicio hasta fin.
vector<pair<int,int>> Grafo::obtenerRuta(int filaInicio, int columnaInicio,int filaFin, int columnaFin) {
    vector<pair<int,int>> ruta;
    vector<pair<int,int>> invertida;

    // Índices de inicio y fin.
    int inicio = indexar(filaInicio, columnaInicio);
    int fin = indexar(filaFin, columnaFin);
    int actual = fin;

    // Reconstruir ruta hacia atrás.
    while (actual != -1) {
        int fila = actual / columnas;
        int columna = actual % columnas;

        // Almacenar en orden.
        invertida.push_back(pair<int,int>(fila, columna));
        if (actual == inicio) { 
            break; 
        }
        actual = predecesores[actual];
    }

    // Invertir manualmente.
    for (int i = invertida.size() - 1; i >= 0; i--) {
        ruta.push_back(invertida[i]);
    }
    return ruta;
}
