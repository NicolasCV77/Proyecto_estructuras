#include <iostream>
#include <cstring>
#include <locale>
#include <cstdlib>

using namespace std;

typedef void (*ComandoFuncion)(const string&, const string&);

// Estructura de Comando.
struct Comando {
    string nombre;
    string descripcion;
    string uso;
    int argumentos;
    ComandoFuncion funcion;
};

// Prototipos de funciones de comando.
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

// Tabla de comandos
Comando comandos[] = {
    {"ayuda", "Muestra todos los comandos.", "ayuda <comando>", 1, comando_ayuda},
    {"cargar", "Carga los datos contenidos en el archivo.", "cargar <archivo>", 1, comando_cargar},
    {"listar_secuencias", "Lista la cantidad de secuencias.", "listar_secuencias", 0, comando_listar_secuencias},
    {"histograma", "Imprime el histograma de una secuencia.", "histograma <id>", 1, comando_histograma},
    {"subsecuencia", "Determina si una subsecuencia existe.", "subsecuencia <id> <sub>", 2, comando_subsecuencia},
    {"enmascarar", "Enmascara una subsecuencia dada.", "enmascarar <id>", 1, comando_enmascarar},
    {"guardar", "Guarda las secuencias en el archivo.", "guardar <archivo>", 1, comando_guardar},
    {"codificar", "Genera el archivo binario.", "codificar <id>", 1, comando_codificar},
    {"decodificar", "Cargar las secuencias en el archivo binario.", "decodificar <id>", 1, comando_decodificar},
    {"ruta_mas_corta", "Calcula ruta más corta.", "ruta_mas_corta <archivo>", 1, comando_ruta_mas_corta},
    {"base_remota", "Busca la ubicación de la misma base.", "base_remota <URL>", 1, comando_base_remota},
    {"salir", "Termina la ejecución de la aplicación.", "salir", 0, comando_salir}
};


// Determinamos el numero de comandos.
const int numComandos = sizeof(comandos) / sizeof(Comando);

// Programa principal.
int main() {
    char linea[200];

    cout << "\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t\t  |          FASTA - TOOL         |" << endl;
    cout << "\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t By Mafe Cruz, Nicolas Castaneda & Daniel Ortiz" << endl;
    
    cout << " - Bienvenid@! -" << endl << " - Escribe 'ayuda' para ver los comandos disponibles -" << endl;

    while (true) {
        cout << "$ ";

        if (!cin.getline(linea, sizeof(linea))) 
            break;
        if (strlen(linea) == 0) 
            continue;

        // Tokeniza la línea de entrada
        char* token = strtok(linea, " ");
        char* a1 = strtok(nullptr, " ");
        char* a2 = strtok(nullptr, " ");

        if (!token) 
            continue;

        string comando(token), arg1, arg2;
        int argc = 0;

        // Convertir char a string.
        if (a1 != nullptr) {
            arg1 = string(a1);
            argc++;
        }
        if (a2 != nullptr) {
            arg2 = string(a2);
            argc++;
        }

        bool encontrado = false;
        for (int i = 0; i < numComandos; i++) {
            if (comando == comandos[i].nombre) {
                encontrado = true;

                if (argc != comandos[i].argumentos) {
                    cout << "[ERROR] Uso: " << comandos[i].uso << endl;
                } else {
                    comandos[i].funcion(arg1, arg2);
                }
                break;
            }
        }

        if (!encontrado) {
            cout << "[ERROR] Comando invalido. Usa 'ayuda'." << endl;
        }
    }

    return 0;
}

// Implementacion de funciones.
void comando_ayuda()
{
}

void comando_cargar()
{
}

void comando_listar_secuencias()
{
}

void comando_histograma()
{
}

void comando_subsecuencia()
{
}

void comando_enmascarar()
{
}

void comando_guardar()
{
}

void comando_codificar()
{
}

void comando_decodificar()
{
}

void comando_ruta_mas_corta()
{
}

void comando_base_remota()
{
}

void comando_salir()
{
}