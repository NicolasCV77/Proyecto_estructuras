#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Secuencia {
    private:
        vector <char> bases;    
        string descripcion; 
        int ancho;

    public:
        // Constructor.
        Secuencia(const string& descripcion, const vector<char>& linea, int anchoLinea);

        // Getters.
        string getDescripcion();
        vector <char> getBases();
        int getAncho();

        // Operaciones principales.
        int contarBase(char base);
        int enmascarar(int inicio, int fin);

};

#endif