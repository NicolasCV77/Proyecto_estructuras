#include "secuencia.h"

Secuencia::Secuencia(const string& descripcion, const vector<char>& bases, int ancho) {
    this->descripcion = descripcion;
    this->bases = bases;
    this->ancho = ancho;
}

string Secuencia::getDescripcion() {
    return descripcion;
}

vector <char> Secuencia::getBases() {
    return bases;
}

int Secuencia::getAncho() {
    return ancho;
}

int Secuencia::contarBase(char base) {
    int contador = 0;
    vector<char>::iterator it;

    for (it = bases.begin(); it != bases.end(); it++) {
        if (*it==base) {
            contador++;
        }
    }
    return contador;
}

int Secuencia::enmascarar(const string& sub) {
    int numeroRemplazos = 0;

    

    vector<char>::iterator it;

    for (it = bases.begin(); it <= bases.end() - sub.size(); ++it) {
        if (equal(sub.begin(), sub.end(), it)) {
            // Reemplazar cada caracter de la subcadena encontrada por 'X'.
            fill(it, it + sub.size(), 'X');
            numeroRemplazos++;
        }
    }
    return numeroRemplazos;
}

 
vector<string> Secuencia::formatoFASTA() {
    vector<string> lineas;
    vector<char>::iterator it;
    vector<char>::iterator fin;

    if(bases.empty()) {
        return lineas;
    }

    for (auto it = bases.begin(); it != bases.end(); ) {
        fin = it + ancho;
        if (fin > bases.end()) {
            fin = bases.end();
        }

        lineas.emplace_back(it, fin);
        it = fin;
    }

    return lineas;
}

