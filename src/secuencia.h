#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Secuencia {
    private:
        string descripcion;
        vector <char> bases;
        vector <char> componentesExactos;
        vector <char> componentesNoExactos;
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
        int enmascarar(const string& sub);
        int esSubsecuencia(string subsecuencia);

        // Exportar en formato FASTA.
        vector<string> formatoFASTA();
        
};

#endif