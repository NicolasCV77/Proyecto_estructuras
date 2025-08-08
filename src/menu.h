#include <iostream>
#include <cstring>
#ifndef MENU_H
#define MENU_H
using namespace std;

// Define un alias para punteros a funciones que reciben dos strings constantes por referencia.
typedef void (*ComandoFuncion)(const string&, const string&);

// Estructura de Comando.
struct Comando {
    ComandoFuncion funcion;
    string nombre;
    int argumentos;
    string descripcion;
    string uso; 
};

// Prototipos de funciones de comando.
void imprimir_menu();
void comando_ayuda(const string& arg1, const string&);

#endif