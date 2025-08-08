#include "menu.h"
#include "comandos.h"
#include "comandos.cpp"
#include <iomanip>

// Determinamos el numero de comandos.
const int numComandos = sizeof(comandos) / sizeof(Comando);

void imprimir_menu(){
    char linea[200];

    cout << "\t~" << endl;
    cout << "\t|          FASTA - TOOL         |" << endl;
    cout << "\t~\t"<< endl;
    cout << endl << "By Mafe Cruz, Nicolas Castaneda & Daniel Ortiz\t" << endl;

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

                if (argc < comandos[i].argumentos) {
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
}
//implementación de funcion ayuda
void comando_ayuda(const string& arg1, const string& arg2)
{
    //valida argumentos
    if (arg1.empty()) {
        cout << "Comandos disponibles:\n";
        for (int i = 0; i < numComandos; i++) {
            cout << " - " << comandos[i].nombre << ": " << comandos[i].descripcion << endl;
        }
    } else {
        for (int i = 0; i < numComandos; i++) {
            if (comandos[i].nombre == arg1) {
                cout << "Uso de '" << arg1 << "': " << comandos[i].uso << endl;
                return;
            }
        }
        cout << "[ERROR] Comando '" << arg1 << "' no reconocido para ayuda.\n";
    }
}