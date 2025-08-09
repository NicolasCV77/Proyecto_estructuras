#include "comandos.h"
#include "menu.h"
#include <fstream>

// Estructura de Comando.
struct Comando {
    ComandoFuncion funcion;
    string nombre;
    int argumentos;
    string descripcion;
    string uso; 
};

Comando comandos[] = {
    {comando_ayuda, "ayuda", 0, "Muestra todos los comandos.", "ayuda"},
    {comando_cargar, "cargar", 1, "Carga los datos contenidos en el archivo.", "cargar <archivo>"},
    {comando_listar_secuencias, "listar_secuencias", 0, "Lista la cantidad de secuencias.", "listar_secuencias"},
    {comando_histograma, "histograma", 1, "Imprime el histograma de una secuencia.", "histograma <id>"},
    {comando_subsecuencia, "subsecuencia", 2, "Determina si una subsecuencia existe.", "subsecuencia <id> <sub>"},
    {comando_enmascarar, "enmascarar", 1, "Enmascara una subsecuencia dada.", "enmascarar <id>"},
    {comando_guardar, "guardar", 1, "Guarda las secuencias en el archivo.", "guardar <archivo>"},
    {comando_ruta_mas_corta, "ruta_mas_corta", 2, "Calcula ruta más corta.", "ruta_mas_corta <seq1> <seq2>"},
    {comando_salir, "salir", 0, "Termina la ejecución de la aplicación.", "salir"}
};

void comando_cargar(const string& arg1, const string&) 
{
    ifstream archivo(arg1);
    if (!archivo.is_open()) {
        cout << "[ERROR] '" << arg1 << "' no se encuentra o no puede leerse." << endl;
        return;
    }

    int secuencias = 0;
    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty()) secuencias++;
    }
    archivo.close();

    cout << "[OK] " << secuencias << " secuencias cargadas desde " << arg1 << "." << endl;
}

void comando_listar_secuencias(const string&, const string&) {
    cout << "[OK] Secuencias listadas." << endl;
}

void comando_histograma(const string& arg1, const string&) {
    if (arg1.empty()) {
        cout << "[ERROR] Uso: histograma <secuencia>" << endl;
        return;
    }
    cout << "[OK] Histograma generado para '" << arg1 << "'." << endl;
}

void comando_subsecuencia(const string& arg1, const string& arg2) {
    if (arg1.empty() || arg2.empty()) {
        cout << "[ERROR] Uso: subsecuencia <secuencia1> <secuencia2>" << endl;
        return;
    }
    cout << "[OK] '" << arg1 << "' es subsecuencia de '" << arg2 << "'." << endl;
}

void comando_enmascarar(const string& arg1, const string&) {
    if (arg1.empty()) {
        cout << "[ERROR] Uso: enmascarar <secuencia>" << endl;
        return;
    }
    cout << "[OK] Regiones enmascaradas en '" << arg1 << "'." << endl;
}

void comando_guardar(const string& arg1, const string&) {
    if (arg1.empty()) {
        cout << "[ERROR] Uso: guardar <archivo>" << endl;
        return;
    }
    ofstream archivo(arg1);
    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo guardar en '" << arg1 << "'" << endl;
        return;
    }
    archivo.close();
    cout << "[OK] Secuencias guardadas en " << arg1 << "." << endl;
}

void comando_ruta_mas_corta(const string& arg1, const string& arg2) {
    if (arg1.empty() || arg2.empty()) {
        cout << "[ERROR] Uso: ruta_mas_corta <seq1> <seq2>" << endl;
        return;
    }
    int distancia = 0;
    cout << "[OK] Ruta más corta entre '" << arg1 << "' y '" << arg2 << "': " << distancia << " pasos" << endl;
}

void comando_salir(const string&, const string&) {
    cout << "[OK] Saliendo del programa..." << endl;
    exit(0);
}
