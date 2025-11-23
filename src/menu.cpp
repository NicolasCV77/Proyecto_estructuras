#include <iostream>
#include <fstream>
#include <iomanip> 
#include <cstring>

#include "menu.h"
#include "comando.h"
#include "sistema.h"

// Vector que almacena todos los comandos de menú.
vector<Comando> Menu::comandos;

// Instancia principal del sistema.
Sistema sistema;

// Constructor Menú.
Menu::Menu() {
    inicializarComandos();
    imprimirMenu();
}

// Implementación para inicializar todos los comandos.
void Menu::inicializarComandos() {
    comandos = {
        Comando(comandoAyuda, "ayuda", 0, "Muestra todos los comandos.", "ayuda"),
        Comando(comandoCargar, "cargar", 1, "Carga los datos contenidos en el archivo.", "cargar nombre_archivo"),
        Comando(comandoListarSecuencias, "listar_secuencias", 0, "Lista la cantidad de secuencias.", "listar_secuencias"),
        Comando(comandoHistograma, "histograma", 1, "Imprime el histograma de una secuencia.", "histograma descripcion_secuencia"),
        Comando(comandoSubsecuencia, "es_subsecuencia", 1, "Determina si una subsecuencia existe.", "es_subsecuencia subsecuencia"),
        Comando(comandoEnmascarar, "enmascarar", 1, "Enmascara una subsecuencia dada.", "enmascarar subsecuencia"),
        Comando(comandoGuardar, "guardar", 1, "Guarda las secuencias en el archivo.", "guardar nombre_archivo"),
        Comando(comandoSalir, "salir", 0, "Termina la ejecución de la aplicación.", "salir"),
        Comando(comandoCodificar, "codificar", 1, "Codifica las secuencias en formato binario (.fabin).", "codificar nombre_archivo.fabin"), 
        Comando(comandoDecodificar, "decodificar", 1, "Decodifica un archivo binario .fabin a formato FASTA.", "decodificar nombre_archivo.fabin"),
        Comando(comandoRutaMasCorta, "ruta_mas_corta", 5, "Calcula la ruta más corta entre dos posiciones de una secuencia.", "ruta_mas_corta descripcion_secuencia i j x y"),
        Comando(comandoBaseRemota, "base_remota", 3, "Consulta la base ubicada en una posición de la secuencia.", "base_remota descripcion_secuencia i j"),
    };
}

// Loop principal que lee los comandos del usuario y los ejecuta.
void Menu::imprimirMenu() {
    char linea[200];

    cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t|         >>> FASTA - TOOL <<<             |" << endl;
    cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "By Mafe Cruz, Nicolas Castaneda & Daniel Ortiz\t" << endl;

    cout << " - Bienvenid@! -" << endl << " - Escribe 'ayuda' para ver los comandos disponibles -" << endl;

    // Bucle de lectura de comandos.
    while (true) {
        cout << endl << "$ ";

        // Leer línea completa.
        if (!cin.getline(linea, sizeof(linea))) {
            break;
        }

        if (strlen(linea) == 0) {
            continue;
        }

        // Tokeniza la línea de entrada, separando comandos de argumentos.
        char* token = strtok(linea, " ");
        char* a1 = strtok(nullptr, " ");
        char* a2 = strtok(nullptr, " ");
        char* a3 = strtok(nullptr, " ");
        char* a4 = strtok(nullptr, " ");
        char* a5 = strtok(nullptr, " ");

        if (!token) {
            continue;
        }

        // Guardar en strings independientes.
        string cmd(token);
        string arg1;
        string arg2;
        string arg3;
        string arg4;
        string arg5;
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

        if (a3 != nullptr) {
            arg3 = string(a3);
            argc++;
        }

        if (a4 != nullptr) {
            arg4 = string(a4);
            argc++;
        }

        if (a5 != nullptr) {
            arg5 = string(a5);
            argc++;
        }

        bool encontrado = false;
        vector<Comando>:: iterator it;

        // Buscar en los comandos registrados.
        for (it = comandos.begin(); it != comandos.end(); it++) {
            if (cmd == it->getNombre()) { 
                encontrado = true;

                // Validar cantidad de argumentos.
                if (argc < it->getArgumentos()) {
                    cout << "[ERROR] Uso: " << it->getUso() << endl;
                } else {
                    // Ejecutar el comando encontrado.
                    it->ejecutar(arg1, arg2, arg3, arg4, arg5);
                }

                break;
            }
        }

        // No se encontró el comando ingresado.
        if (!encontrado) {
            cout << "[ERROR] Comando invalido. Usa 'ayuda'." << endl;
        }
    }
}

// Listar todos los comandos o uno en específico.
void Menu::comandoAyuda(const string& arg1, const string& arg2, const string&, const string&, const string&) {
    // Validar argumentos.
    if (arg1.empty()) {
        cout << "Comandos disponibles: " << endl;

        vector <Comando>::iterator it;
        for (it = comandos.begin(); it != comandos.end(); it++) {
            cout << " - " << it->getNombre() << ": " << it->getDescripcion() << endl;
        }
    } else {
        vector <Comando>::iterator it;
        for (it = comandos.begin(); it != comandos.end(); it++) {
            if (it->getNombre() == arg1) {
                cout << "Uso de '" << arg1 << "': " << it->getUso() << endl;
                return;
            }
        }
        cout << "[ERROR] Comando '" << arg1 << "' no reconocido para ayuda.\n";
    }
}

// Cargar las secuencias al sistema.
void Menu::comandoCargar(const string& arg1, const string& arg2, const string&, const string&, const string&) {
    sistema.cargarArchivo(arg1);
}

// Listar el conjunto de secuencias.
void Menu::comandoListarSecuencias(const string&, const string&, const string&, const string&, const string&) {
    sistema.getFASTA().listarSecuencias();
}

// Mostrar histograma de una secuencia específica.
void Menu::comandoHistograma(const string& arg1, const string&, const string&, const string&, const string&) {
    sistema.getFASTA().histograma(arg1);
}

// Verificar si existe una subsecuencia dentro de las secuencias.
void Menu::comandoSubsecuencia(const string& arg1, const string&, const string&, const string&, const string&) {
    sistema.getFASTA().contarSubsecuencia(arg1);
}

// Enmascara una subsecuencia dada en todas las secuencias.
void Menu::comandoEnmascarar(const string& arg1, const string&, const string&, const string&, const string&) {
    sistema.getFASTA().enmascararSubsecuencia(arg1);
}

// Guardar las secuencias actuales en un archivo FASTA.
void Menu::comandoGuardar(const string& arg1, const string&, const string&, const string&, const string&) {
    sistema.guardarArchivo(arg1);
}

// Finalizar el programa.
void Menu::comandoSalir(const string&, const string&, const string&, const string&, const string&) {
    cout << "[OK] Saliendo del programa..." << endl;
    exit(0);
}

// Exportar secuencias en un formato binario personalizado.
void Menu::comandoCodificar(const string& arg1, const string&, const string&, const string&, const string&) {
    sistema.guardarCodificacion(arg1);
}

// Importar un archivo binario al formato FASTA.
void Menu::comandoDecodificar(const string& arg1, const string&, const string&, const string&, const string&) {
    sistema.cargarCodificacion(arg1);
}

// Encontrar la ruta más corta entre secuencias.
void Menu::comandoRutaMasCorta(const string& arg1, const string& arg2, const string& arg3, const string& arg4, const string& arg5) {
    sistema.rutaMasCorta(arg1, arg2, arg3, arg4, arg5);
}

// Consulta la base de una secuencia en coordenadas dadas.
void Menu::comandoBaseRemota(const string& arg1, const string& arg2, const string& arg3, const string&, const string&) {
    sistema.baseRemota(arg1, arg2, arg3);
}
