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
void comando_cargar(const string& arg1, const string&);
void comando_listar_secuencias(const string& arg1, const string&);
void comando_histograma(const string& arg1, const string&);
void comando_subsecuencia(const string& arg1, const string&);
void comando_enmascarar(const string& arg1, const string&);
void comando_guardar(const string& arg1, const string&);
void comando_codificar(const string& arg1, const string&);
void comando_decodificar(const string& arg1, const string&);
void comando_ruta_mas_corta(const string& arg1, const string&);
void comando_base_remota(const string& arg1, const string&);
void comando_salir(const string&, const string&);

#endif