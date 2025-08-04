#include <iostream>

using namespace std;

struct Comando {
    string nombre;
    string description;
    string exito;
    string error;
};

void comando_ayuda();
void comando_cargar();
void comando_listar_secuencias();
void comando_histograma();
void comando_subsecuencia();
void comando_enmascarar();
void comando_guardar();
void comando_cofificr();
void comando_decodificar();
void comando_ruta_mas_corta();
void comando_base_remota();
void comando_salir();


int main() {
    setlocale(LC_ALL, "");
    string linea;

    cout << "\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t\t  |          FASTA - TOOL         |" << endl;
    cout << "\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t By Mafe Cruz, Nicolas Castaneda & Daniel Ortiz" << endl;

    cout << " - Bienvenid@! -" << endl << " - Escribe 'ayuda' para ver los comandos disponibles -" << endl;
    
    while (true) {
        cout << "$ ";
        if (!getline(cin, linea)) {
            cout << "ERROR" << endl;
            break;
        }

        // MENU - Evaluamos la opcion seleccionada.
        switch (linea) 
        {
            case "ayuda":
                cout << "" << endl;
            break;

            case "cargar":
                cout << "" << endl;
            break;

            case "listar_secuencias":
                cout << "" << endl;
            break;

            case "histograma":
                cout << "" << endl;
            break;

            case "subsecuencia":
                cout << "" << endl;
            break;

            case "enmascarar":
                cout << "" << endl;
            break;

            case "guardar":
                cout << "" << endl;
            break;

            case "codificar":
                cout << "" << endl;
            break;

            case "decodificar":
                cout << "" << endl;
            break;

            case "ruta_mas_corta":
                cout << "" << endl;
            break;

            case "base_remota":
                cout << "" << endl;
            break;

            case "salir":
                cout << "" << endl;
            break;
            
            // Opcion no valida.
            default: 
                cout << "Opcion no valida." << endl;
                cout << "Intentelo de nuevo." << endl;
            break;
        }
    }
}