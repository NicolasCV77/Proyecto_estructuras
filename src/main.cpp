#include <iostream>
#include <cstring>
#include <locale>
#include <cstdlib>

using namespace std;

typedef void (*CmdFunc)(const string&, const string&);

// Estructura de Comando.
struct Comando {
     string nombre;
    string descripcion;
    int argumentos;
    CmdFunc funcion;
    string uso;
};

// Prototipos de funciones de comando
void comando_ayuda();
void comando_cargar();
void comando_listar_secuencias();
void comando_histograma();
void comando_subsecuencia();
void comando_enmascarar();
void comando_guardar();
void comando_cofificar();
void comando_decodificar();
void comando_ruta_mas_corta();
void comando_base_remota();
void comando_salir();

// Tabla de comandos
Comando comandos[] = {
    {"ayuda", "Muestra todos los comandos", 1, comando_ayuda, ""},
    {"cargar", "Carga los datos contenidos en el archivo", 1, comando_cargar, ""},
    {"listar_secuencias", "Lista la cantidad de secuencias", 0, comando_listar_secuencias, ""},
    {"histograma", "Imprime el histograma de una secuencia", 1, comando_histograma, ""},
    {"es_subsecuencia", "Determina si una subsecuencia existe", 2, comando_subsecuencia, ""},
    {"enmasacarar", "Enmascara una subsecuencia dada", 1, comando_enmascarar, ""},
    {"guardar", "Guarda las secuencias en el archivo", 1, comando_guardar, ""},
    {"codificar", "Genera el archivo binario", 1, comando_codificar, ""},
    {"decodificar", "Cargar las secuencias en el archivo binario", 1, comando_decodificar, ""},
    {"ruta_mas_corta", "Calcula ruta más corta",1, comando_ruta_mas_corta, ""},
    {"base_remota", "Busca la ubicación de la misma base",1, comando_base_remota, ""},
    {"salir", "Termina la ejecución de la aplicación",0, comando_salir, ""}
};

const int numComandos = sizeof(comandos) / sizeof(Comando);

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

        string cmd(token);
        string arg1;
        string arg2;
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
        for (int i = 0; i < numComandos; ++i) {
            if (cmd == comandos[i].nombre) {
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

//implementación de funciones
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

void comando_cofificar()
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