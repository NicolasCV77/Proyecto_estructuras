#include <iostream>
#include <fstream>

#include "sistema.h"

// Cargar un archivo FASTA (extensión .fa) en memororia
void Sistema::cargarArchivo(string nombreArchivo) {
    // Validar extensión .fa
    if (nombreArchivo.rfind(".fa") != nombreArchivo.size() - 3) {
        cout << "[ERROR] '" << nombreArchivo << "' no es un archivo .fa válido." << endl;
        return;
    }

    // Intentar abrir el archivo.
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "[ERROR] '" << nombreArchivo << "' no se encuentra o no puede leerse." << endl;
        return;
    }

    // Reiniciar contenedor.
    fasta = FASTA();

    // Variables auxiliares.
    string linea;
    string descripcion = "";
    vector<char> bases;
    bool bandera = true;
    int ancho, secuencias = 0;

    // Leer archivo línea por línea
    while (getline(archivo, linea)) {
        // Saltar líneas vacías.
        if (linea.empty()) {
            continue;
        }

        // Validar carácter '>', nueva descripción.
        if (linea[0] == '>') {
            if (bandera) {
                bandera = false;
            } else if (descripcion.empty()) {
                // Archivo no empezó con '>'.
                cout << "[ERROR] Formato inválido... El archivo no inicia con '>'." << endl;
                return;
            } else {
                // Guardar secuencia anterior.
                Secuencia secuencia(descripcion, bases, ancho);
                fasta.agregarSecuencia(secuencia);
                secuencias++;
            }
            // Actualizar descripción y reinicar acumuladores.
            descripcion = linea.substr(1);
            bases.clear();
            ancho = 0;
        } else {
            // No se encontró una descripción.
            if (bandera) {
                cout << "[ERROR] Formato inválido... El archivo no inicia con '>'." << endl;
                return;
            }
                
            // Registrar ancho de la línea de la secuencia.
            if (ancho == 0) {
                ancho = linea.size();
            } else {
                if (linea.size() != ancho) {
                    if (linea.size() < ancho) {
                        // La dejamos pasar como "posible última".
                    } else {
                        cout << "[ERROR] Ancho inválido en la secuencia '" << descripcion << "." << endl;
                        return;
                    }
                } 
            }

            for (int i = 0; i < linea.size(); i++) {
                char base = linea[i];
                bool valida = false;

                // Iterador explícito sobre los componentes
                vector<vector<char>>::iterator itComp;
                for (itComp = fasta.getComponentes().begin(); itComp != fasta.getComponentes().end(); itComp++) {
                    if (base == (*itComp)[0]) {
                        valida = true;
                        break;
                    }
                }

                if (!valida) {
                    cout << "[ERROR] Base inválida '" << base 
                        << "' encontrada en la secuencia " << descripcion << endl;
                    return; // OJO: aborta toda la carga
                }

                bases.push_back(base);
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
    if (nombreArchivo.rfind(".fa") != nombreArchivo.size() - 3) {
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