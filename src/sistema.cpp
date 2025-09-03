#include <iostream>
#include <fstream>

#include "sistema.h"
 
void Sistema::cargarArchivo(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "[ERROR] '" << nombreArchivo << "' no se encuentra o no puede leerse." << endl;
        return;
    }

    if (nombreArchivo.substr(nombreArchivo.size() - 3) != ".fa") {
        cout << "[ERROR] '" << nombreArchivo << "' no es un archivo .fa válido." << endl;
        return;
    }

    // Reiniciar contenedor.
    fasta = FASTA();

    string linea;
    string descripcion = "";
    vector<char> bases;
    bool bandera = true;
    int ancho, secuencias = 0;

    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        if (linea[0] == '>') {
            if (bandera) {
                bandera = false;
            } else if (descripcion.empty()) {
                cout << "[ERROR] Formato inválido... El archivo no inicia con '>'." << endl;
                return;
            } else {
                Secuencia secuencia(descripcion, bases, ancho);
                fasta.agregarSecuencia(secuencia);
                secuencias++;
            }
            descripcion = linea.substr(1);
            bases.clear();
            ancho = 0;
        } else {
            if (bandera) {
                cout << "[ERROR] Formato inválido... El archivo no inicia con '>'." << endl;
                return;
            }
                
            if (ancho == 0) {
                ancho = linea.size();
            }

            for (int i = 0; i < linea.size(); i++) {
                bases.push_back(linea[i]);
            }
        }
    }

    if (!descripcion.empty()) {
        Secuencia secuencia(descripcion, bases, ancho);
        fasta.agregarSecuencia(secuencia);
        secuencias++;
    }

    if (secuencias == 0) {
        cout << nombreArchivo << " no contiene ninguna secuencia." << endl;  
    } else if (secuencias == 1) {
        cout << "[OK] 1 secuencia cargada correctamente desde " << nombreArchivo << "." << endl; 
    } else {
        cout << "[OK] " << secuencias << " secuencias cargadas desde " << nombreArchivo << "." << endl;
    }
    
    archivo.close();
}

void Sistema::guardarArchivo(string nombreArchivo) {
    // Validar extensión.
    if (nombreArchivo.substr(nombreArchivo.size() - 3) != ".fa") {
        cout << "[ERROR] '" << nombreArchivo << "' no es un archivo .fa válido." << endl;
        return;
    }

    // Verificar secuencias cargadas.
    vector<Secuencia>& secuencias = fasta.getSecuencias();
    if (secuencias.empty()) {
        cout << "[ERROR] No hay secuencias guardadas en memoria." << endl;
        return;
    }

    // Abrir archivo.
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "[ERROR] Problemas guardando en '" << nombreArchivo << "'." << endl;
    }

    // Secuencias en formato FASTA.
    vector<Secuencia>:: iterator it;
    for (it = secuencias.begin(); it != secuencias.end(); it++) {
        archivo << ">" << it->getDescripcion() << endl;

        vector<char> bases = it->getBases();
        int ancho = it->getAncho();
        int contador = 0;

        vector<char>:: iterator itB;
        for (itB = bases.begin(); itB != bases.end(); itB++) {
            archivo << *itB;
            contador++;

            if (contador == ancho) {
                archivo << endl;
                contador = 0;
            }
        }

        // Última línea incompleta.
        if (contador != 0) {
            archivo << endl;
        }
        
    }
    
    archivo.close();
    cout << "Las secuencias han sido guardadas en '" << nombreArchivo << "'." << endl;
}

// Devuelve una referencia al objeto que pertenece al Sistema.
FASTA& Sistema::getFASTA() {
    return fasta;
}