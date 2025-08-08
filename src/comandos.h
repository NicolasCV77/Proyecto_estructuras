#ifndef COMANDOS_H
#define COMANDOS_H
#include <iostream>
#include <cstring>

using namespace std;
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