#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Clase Secuencia, representa una secuencia de bases.
class Secuencia {
    private:
        // Atributos.
        vector <char> bases;    
        string descripcion; 
        int ancho;

    public:
        // Constructor.
        Secuencia(const string& descripcion, const vector<char>& linea, int anchoLinea);

        // Métodos de acceso.
        string getDescripcion();
        vector <char> getBases();
        int getAncho();

        // Operaciones principales.
        int contarBase(char base);
        int enmascarar(int inicio, int fin);

};

#endif
