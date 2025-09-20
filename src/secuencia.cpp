#include "secuencia.h"

// Constructor Secuencia.
Secuencia::Secuencia(const string& descripcion, const vector<char>& bases, int ancho) {
    this->descripcion = descripcion;
    this->bases = bases;
    this->ancho = ancho;
}

// Retorna la descripción de la secuencia.
string Secuencia::getDescripcion() {
    return descripcion;
}

// Retorna las bases que conforman la secuencia.
vector <char> Secuencia::getBases() {
    return bases;
}

// Retorna el ancho de la secuencia.
int Secuencia::getAncho() {
    return ancho;
}

// Cuenta la cantidad de veces que aparece una base en la secuencia.
int Secuencia::contarBase(char base) {
    int contador = 0;

    vector<char>::iterator it; 
    for (it = bases.begin(); it != bases.end(); it++) {
        if (*it == base) {
            contador++;
        }
    }
    return contador;
}

// Enmascara las bases de un rango dado reemplazándolas por 'X'.
int Secuencia::enmascarar(int inicio, int fin) {
    if (inicio < 0 || fin >= bases.size() || inicio > fin) {
        // Rango inválido, no se realiza enmascaramiento.
        return 0;
    }

    for (int i = inicio; i <= fin; i++) {
        bases[i] = 'X';
    }

    // Se realizó un enmascaramiento.
    return 1;
}
