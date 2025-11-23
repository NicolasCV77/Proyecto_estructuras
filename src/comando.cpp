#include <fstream>

#include "comando.h"

// Constructor Comando.
Comando::Comando(ComandoFuncion accion, const string& nombre, int argumentos, const string& descripcion, const string& uso) {
    this->accion = accion;
    this->nombre = nombre;
    this->argumentos = argumentos;
    this->descripcion = descripcion;
    this->uso = uso;
}

// Nombre del comando.
string Comando::getNombre() {
    return nombre;
}

// Descripción del comando.
string Comando::getDescripcion() {
    return descripcion;
}

// Forma de uso del comando.
string Comando::getUso() {
    return uso;
}

// Cantidad de argumentos requeridos.
int Comando::getArgumentos() {
    return argumentos;
} 

// Ejecuta la función asociada al comando.
void Comando::ejecutar(const string& arg1, const string& arg2, const string& arg3, const string& arg4, const string& arg5) {
    if (accion != nullptr) {
        accion(arg1, arg2, arg3, arg4, arg5);
    }
}
