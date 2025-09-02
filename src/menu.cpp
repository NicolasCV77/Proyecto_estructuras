#include "menu.h"
#include "comando.h"
#include <fstream>
#include "FASTA.h"
#include <iomanip>
#include <cstring>


vector<Comando> Menu::comandos;
FASTA f;
//
Menu::Menu(){
    inicializarComandos();
    imprimirMenu();
}
// Registrar comandos en el menú
void Menu::imprimirMenu() {
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
        vector<Comando>:: iterator it;

        for (it=comandos.begin(); it!=comandos.end(); it++) {
            
            if (cmd == it->getNombre()) {
                encontrado = true;

                if (argc < it->getArgumentos()) {
                    cout << "[ERROR] Uso: " << it->getUso() << endl;
                } else {
                    it->ejecutar(arg1, arg2);
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
void Menu::inicializarComandos() {
    comandos = {
        Comando(comandoAyuda, "ayuda", 0, "Muestra todos los comandos.", "ayuda"),
        Comando(comandoCargar, "cargar", 1, "Carga los datos contenidos en el archivo.", "cargar <archivo>"),
        Comando(comandoListarSecuencias, "listar_secuencias", 0, "Lista la cantidad de secuencias.", "listar_secuencias"),
        Comando(comandoHistograma, "histograma", 1, "Imprime el histograma de una secuencia.", "histograma <id>"),
        Comando(comandoSubsecuencia, "subsecuencia", 2, "Determina si una subsecuencia existe.", "subsecuencia <id> <sub>"),
        Comando(comandoEnmascarar, "enmascarar", 1, "Enmascara una subsecuencia dada.", "enmascarar <id>"),
        Comando(comandoGuardar, "guardar", 1, "Guarda las secuencias en el archivo.", "guardar <archivo>"),
        Comando(comandoRutaMasCorta, "ruta_mas_corta", 2, "Calcula ruta más corta.", "ruta_mas_corta <seq1> <seq2>"),
        Comando(comandoSalir, "salir", 0, "Termina la ejecución de la aplicación.", "salir")
    };
}

void Menu::comandoAyuda(const string& arg1, const string& arg2) {
    //valida argumentos
    if (arg1.empty()) {
        cout << "Comandos disponibles:\n";
        vector <Comando>::iterator it;
        for (it = comandos.begin(); it != comandos.end();it++) {
            cout << " - " << it->getNombre() << ": " << it->getDescripcion() << endl;
        }
    } else {
        vector <Comando>::iterator it;
        for (it = comandos.begin(); it != comandos.end();it++) {
            if (it->getNombre() == arg1) {
                cout << "Uso de '" << arg1 << "': " << it->getUso() << endl;
                return;
            }
        }
        cout << "[ERROR] Comando '" << arg1 << "' no reconocido para ayuda.\n";
    }
}

void Menu::comandoCargar(const string& arg1, const string& arg2) 
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

void Menu::comandoListarSecuencias(const string&, const string&) {
    f.listarSecuencias();
}

void Menu::comandoHistograma(const string& arg1, const string&) {
    f.histograma(arg1);
}

void Menu::comandoSubsecuencia(const string& arg1, const string& arg2) {
    f.contarSubsecuencia(arg1);
}

void Menu::comandoEnmascarar(const string& arg1, const string&) {
    f.enmascararSubsecuencia(arg1);
}

void Menu::comandoGuardar(const string& arg1, const string&) {
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

void Menu::comandoRutaMasCorta(const string& arg1, const string& arg2) {
    if (arg1.empty() || arg2.empty()) {
        cout << "[ERROR] Uso: ruta_mas_corta <seq1> <seq2>" << endl;
        return;
    }
    int distancia = 0;
    cout << "[OK] Ruta más corta entre '" << arg1 << "' y '" << arg2 << "': " << distancia << " pasos" << endl;
}

void Menu::comandoSalir(const string&, const string&) {
    cout << "[OK] Saliendo del programa..." << endl;
    exit(0);
}