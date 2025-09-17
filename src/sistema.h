#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <string>

#include "FASTA.h"

using namespace std;

// Clase Sistema, representa el núcleo del programa.
class Sistema {
    private:
        // Objeto que administra las secuencias FASTA.
        FASTA fasta;

        // Funciones auxiliares.
        bool validarExtensionFA(string& nombreArchivo);
        bool validarLineas(vector<string>& lineas, string& descripcion, int ancho);
        bool validarBases(string& linea, string& descripcion, vector<char>& bases);
        void guardarSecuencia(string& descripcion, vector<char>& bases, int ancho, int& contador);
        void escribirSecuencia(ofstream& archivo, vector<Secuencia>::iterator it);

    public:
        // Manejo de archivos. 
        void cargarArchivo(string nombreArchivo);
        void guardarArchivo(string nombreArchivo);

        // Referencia del objeto FASTA.
        FASTA& getFASTA();
        
};

#endif