#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <string>
#include <map>
#include <cstdint>

#include "FASTA.h"
#include "arbolHuffman.h"

using namespace std;

// Clase Sistema, representa el núcleo del programa.
class Sistema {
    private:
        // Objeto que administra las secuencias FASTA.
        FASTA fasta;
        map<char, int> frecuencias;
        arbolHuffman arbol;

        // Funciones auxiliares.
        bool validarExtensionFA(string& nombreArchivo);
        bool validarExtensionFABIN(string& nombreArchivo);
        bool validarLineas(vector<string>& lineas, string& descripcion, int ancho);
        bool validarBases(string& linea, string& descripcion, vector<char>& bases);
        void guardarSecuencia(string& descripcion, vector<char>& bases, int ancho, int& contador);
        void escribirSecuencia(ofstream& archivo, vector<Secuencia>::iterator it);

    public:
        // Manejo de archivos. 
        void cargarArchivo(string nombreArchivo);
        void guardarArchivo(string nombreArchivo);

        //Codificación y decodificacion
        void generarMapFrecuencia();
        void guardarCodificacion(string nombreArchivo);
        void cargarCodificacion(string nombreArchivo);

        // Referencia del objeto FASTA.
        FASTA& getFASTA();
        
};

#endif