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

int Secuencia::enmascarar(int inicio, int fin) {
    if (inicio < 0 || fin >= bases.size() || inicio > fin) {
        return 0; // nada que enmascarar
    }

    for (int i = inicio; i <= fin; i++) {
        bases[i] = 'X';
    }
    return 1; // un enmascaramiento hecho
}
    