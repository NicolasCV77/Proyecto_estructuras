#include <iostream>
#include <fstream>
#include <iomanip> 
#include <cstring>

#include "menu.h"
#include "comando.h"
#include "sistema.h"
#include "FASTA.h"

vector<Comando> Menu::comandos;
Sistema sistema;
FASTA& fasta = sistema.getFASTA();

// Constructor.
Menu::Menu() {
    inicializarComandos();
    imprimirMenu();
}

// Registrar comandos en el menú.
void Menu::imprimirMenu() {
    char linea[200];

    cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t|         >>> FASTA - TOOL <<<             |" << endl;
    cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "By Mafe Cruz, Nicolas Castaneda & Daniel Ortiz\t" << endl;

    cout << " - Bienvenid@! -" << endl << " - Escribe 'ayuda' para ver los comandos disponibles -" << endl;

    while (true) {
        cout << endl << "$ ";

        if (!cin.getline(linea, sizeof(linea))) 
            break;
        if (strlen(linea) == 0) 
            continue;

        // Tokeniza la línea de entrada.
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

// Implementación para inicializar todos los comandos.
void Menu::inicializarComandos() {
    comandos = {
        Comando(comandoAyuda, "ayuda", 0, "Muestra todos los comandos.", "ayuda"),
        Comando(comandoCargar, "cargar", 1, "Carga los datos contenidos en el archivo.", "cargar nombre_archivo"),
        Comando(comandoListarSecuencias, "listar_secuencias", 0, "Lista la cantidad de secuencias.", "listar_secuencias"),
        Comando(comandoHistograma, "histograma", 1, "Imprime el histograma de una secuencia.", "histograma descripcion_secuencia"),
        Comando(comandoSubsecuencia, "subsecuencia", 2, "Determina si una subsecuencia existe.", "es_subsecuencia subsecuencia"),
        Comando(comandoEnmascarar, "enmascarar", 1, "Enmascara una subsecuencia dada.", "enmascarar subsecuencia"),
        Comando(comandoGuardar, "guardar", 1, "Guarda las secuencias en el archivo.", "guardar nombre_archivo"),
        Comando(comandoCodificar, "codificar", 1, "Codifica las secuencias en formato binario (.fabin).", "codificar nombre_archivo.fabin"), 
        Comando(comandoDecodificar, "decodificar", 1, "Decodifica un archivo binario .fabin a formato FASTA.", "decodificar nombre_archivo.fabin"),
        Comando(comandoRutaMasCorta, "ruta_mas_corta", 5, "Calcula la ruta más corta entre dos posiciones de una secuencia.", "ruta_mas_corta descripcion_secuencia i j x y"),
        Comando(comandoBaseRemota, "base_remota", 3, "Consulta la base ubicada en una posición de la secuencia.", "base_remota descripcion_secuencia i j"),
        Comando(comandoSalir, "salir", 0, "Termina la ejecución de la aplicación.", "salir"),
    };
}

// Implementación del comando ayuda.
void Menu::comandoAyuda(const string& arg1, const string& arg2) {
    // Validar argumentos.
    if (arg1.empty()) {
        cout << "Comandos disponibles: " << endl;
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

// Cargar un archivo.
void Menu::comandoCargar(const string& arg1, const string& arg2) {
    sistema.cargarArchivo(arg1);
}

// Listar el conjunto de secuencias.
void Menu::comandoListarSecuencias(const string&, const string&) {
    fasta.listarSecuencias();
}

// Mostrar histograma por secuencia.
void Menu::comandoHistograma(const string& arg1, const string&) {
    fasta.histograma(arg1);
}

// Determinar si es subsecuencia dado un string.
void Menu::comandoSubsecuencia(const string& arg1, const string& arg2) {
    fasta.contarSubsecuencia(arg1);
}

// Enmascarar la secuencia.
void Menu::comandoEnmascarar(const string& arg1, const string&) {
    fasta.enmascararSubsecuencia(arg1);
}

// Guardar las secuencias en un archivo .fa
void Menu::comandoGuardar(const string& arg1, const string&) {
    sistema.guardarArchivo(arg1);
}

// Encontrar la ruta más corta entre secuencias.
void Menu::comandoRutaMasCorta(const string& arg1, const string& arg2) {
    if (arg1.empty() || arg2.empty()) {
        cout << "[ERROR] Uso: ruta_mas_corta <seq1> <seq2>" << endl;
        return;
    }
    int distancia = 0;
    cout << "[OK] Ruta más corta entre '" << arg1 << "' y '" << arg2 << "': " << distancia << " pasos" << endl;
}

// Salir del programa.
void Menu::comandoSalir(const string&, const string&) {
    cout << "[OK] Saliendo del programa..." << endl;
    exit(0);
}

// Codificar archivo en formato binario.
void Menu::comandoCodificar(const string& arg1, const string&) {
    if (arg1.empty()) {
        cout << "[ERROR] Uso: codificar nombre_archivo.fabin" << endl;
        return;
    }
    cout << "[OK] Archivo '" << arg1 << "' codificado (implementación pendiente)." << endl;
}

// Decodificar archivo binario a FASTA.
void Menu::comandoDecodificar(const string& arg1, const string&) {
    if (arg1.empty()) {
        cout << "[ERROR] Uso: decodificar nombre_archivo.fabin" << endl;
        return;
    }
    cout << "[OK] Archivo '" << arg1 << "' decodificado (implementación pendiente)." << endl;
}

// Obtener base remota.
void Menu::comandoBaseRemota(const string& arg1, const string& arg2) {
    if (arg1.empty() || arg2.empty()) {
        cout << "[ERROR] Uso: base_remota descripcion_secuencia i j" << endl;
        return;
    }
    cout << "[OK] Base remota en secuencia '" << arg1 
         << "' en posición (" << arg2 << ") (implementación pendiente)." << endl;
}
