#include "comando.h"
#include <fstream>

Comando::Comando(ComandoFuncion accion, const string& nombre, int argumentos, const string& descripcion, const string& uso){
    this->accion = accion;
    this->nombre = nombre;
    this->argumentos = argumentos;
    this->descripcion = descripcion;
    this->uso = uso;
}


string Comando::getNombre(){
    return nombre;
}
string Comando::getDescripcion(){
    return descripcion;
}
string Comando::getUso(){
    return uso;
}
int Comando::getArgumentos(){
    return argumentos;
} 
void Comando::ejecutar(const string& arg1, const string& arg2){
    if (accion != nullptr) {
        accion(arg1, arg2);
    }
}


