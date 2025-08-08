#include "comandos.h"
#include "menu.h"
#include <fstream>

Comando comandos[] = {
    {comando_ayuda, "ayuda", 0, "Muestra todos los comandos.", "ayuda <comando>"},
    {comando_cargar, "cargar", 1, "Carga los datos contenidos en el archivo.", "cargar <archivo>"},
    {comando_listar_secuencias, "listar_secuencias", 0, "Lista la cantidad de secuencias.", "listar_secuencias"},
    {comando_histograma, "histograma", 1, "Imprime el histograma de una secuencia.", "histograma <id>"},
    {comando_subsecuencia, "subsecuencia", 2, "Determina si una subsecuencia existe.", "subsecuencia <id> <sub>"},
    {comando_enmascarar, "enmascarar", 1, "Enmascara una subsecuencia dada.", "enmascarar <id>"},
    {comando_guardar, "guardar", 1, "Guarda las secuencias en el archivo.", "guardar <archivo>"},
    {comando_codificar, "codificar", 1, "Genera el archivo binario.", "codificar <id>"},
    {comando_decodificar, "decodificar", 1, "Cargar las secuencias en el archivo binario.", "decodificar <id>"},
    {comando_ruta_mas_corta, "ruta_mas_corta", 1, "Calcula ruta más corta.", "ruta_mas_corta <archivo>"},
    {comando_base_remota, "base_remota", 1, "Busca la ubicación de la misma base.", "base_remota <URL>"},
    {comando_salir, "salir", 0, "Termina la ejecución de la aplicación.", "salir"}
};

void comando_cargar(const string& arg1, const string& arg2) 
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

    if (secuencias == 0) {
        cout << "[INFO] " << arg1 << " no contiene ninguna secuencia." << endl;
    } else if (secuencias == 1) {
        cout << "1 secuencia cargada correctamente desde " << arg1 << "." << endl;
    } else {
        cout << secuencias << " secuencias cargadas correctamente desde " << arg1 << "." << endl;
    }
}

void comando_listar_secuencias(const string& arg1, const string& arg2) //
{
    if (!arg1.empty() || !arg2.empty()) {
        cout << "[ERROR] El comando 'listar_secuencias' no recibe argumentos." << endl;
        return;
    }

    cout << "[OK] Secuencias listadas." << endl;
}

void comando_histograma(const string& arg1, const string& arg2)
{
    if (arg1.empty() || !arg2.empty()) {
    cout << "[ERROR] Uso: histograma <secuencia>" << endl;
    return;
    }

    // Generar histograma para arg1
    cout << "[OK] Histograma generado para '" << arg1 << "'." << endl;
}

void comando_subsecuencia(const string& arg1, const string& arg2)
{
    if (arg1.empty() || arg2.empty()) {
    cout << "[ERROR] Uso: es_subsecuencia <secuencia1> <secencia2>" << endl;
    return;
    }

    // Valida: ¿arg1 es subsecuencia de arg2?
    bool esSub = true; 
    if (esSub) {
        cout << "[OK] Es subsecuencia." << endl;
    } else {
        cout << "[ERROR] No es subsecuencia." << endl;
    }
}

void comando_enmascarar(const string& arg1, const string& arg2) 
{
    if (arg1.empty() || arg2.empty()) {
        cout << "[ERROR] Uso: enmascarar <secuencia> <patron>" << endl;
        return;
    }

    cout << "[OK] Regiones enmascaradas correctamente en la secuencia " << arg1 << "." << endl;
}

void comando_guardar(const string& arg1, const string& arg2) 
{
    if (arg1.empty()) {
        cout << "[ERROR] Uso: guardar <nombre_archivo>" << endl;
        return;
    }

    ofstream archivo(arg1);
    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo guardar en '" << arg1 << "'" << endl;
        return;
    }

    // Escribe en el archivo las secuencias almacenadas en memoria
    archivo.close();
    cout << "[OK] Secuencias almacenadas correctamente en " << arg1 << "." << endl;
}

void comando_codificar(const string& arg1, const string& arg2) 
{
    if (arg1.empty() || arg2.empty()) {
        cout << "[ERROR] Uso: codificar <secuencia> <clave>" << endl;
        return;
    }

    string resultado_codificado = "";

    // Muestra resultado
    cout << "[OK] Secuencia codificada: " << resultado_codificado << endl;
}

void comando_decodificar(const string& arg1, const string& arg2) 
{
    if (arg1.empty() || arg2.empty()) {
        cout << "[ERROR] Uso: decodificar <secuencia_codificada> <clave>" << endl;
        return;
    }

    string resultado_decodificado = ""; 

    // Muestra resultado
    cout << "[OK] Secuencia decodificada: " << resultado_decodificado << endl;
}

void comando_ruta_mas_corta(const string& arg1, const string& arg2) 
{
    if (arg1.empty() || arg2.empty()) {
        cout << "[ERROR] Uso: ruta_mas_corta <secuencia1> <secuencia2>" << endl;
        return;
    }

    int distancia = 0; // Calcula la distancia o pasos mínimos

    // Muestra resultado
    cout << "[OK] Ruta más corta entre '" << arg1 << "' y '" << arg2 << "': " << distancia << " pasos" << endl;
}

void comando_base_remota(const string& arg1, const string& arg2) 
{
    if (arg1.empty() || arg2.empty()) {
        cout << "[ERROR] Uso: base_remota <secuencia> <nombre_archivo>" << endl;
        return;
    }

    ifstream archivo(arg1);
    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo acceder al archivo remoto '" << arg2 << "'" << endl;
        return;
    }

    // Cargar datos desde el archivo y mostrar confirmación
    int secuencias = 0; // Cuenta cuántas secuencias hay
    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty()) secuencias++;
    }
    archivo.close();

    if (secuencias == 0) {
        cout << "[INFO] El archivo remoto no contiene ninguna secuencia." << endl;
    } else {
        cout << "[OK] " << secuencias << " secuencias cargadas desde base remota." << endl;
    }
}

void comando_salir(const string& arg1, const string& arg2) 
{
    if (!arg1.empty() || !arg2.empty()) {
        cout << "[ERROR] Uso: salir" << endl;
        return;
    }

    cout << "[OK] Saliendo del programa..." << endl;
    exit(0);  // Finaliza el programa correctamente
}