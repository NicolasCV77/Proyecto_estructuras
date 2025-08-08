#include "menu.h"
#include <iomanip>

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
// Determinamos el numero de comandos.
const int numComandos = sizeof(comandos) / sizeof(Comando);

void imprimir_menu(){
     // Interfaz de bienvenida.
    cout << "\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t  |          FASTA - TOOL         |" << endl;
    cout << "\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t By Mafe Cruz, Nicolas Castaneda & Daniel Ortiz" << endl;

    cout << endl << " - Bienvenid@! -" << endl << " - Escribe 'ayuda' para ver los comandos disponibles -" << endl;

    // Bucle principal.
    while (true) {
        bool encontrado = false;
        char *token, *a1, *a2;
        char linea[200];
        int argc = 0;

        cout << endl << "$ ";  // Imprime el prompt.

        // Lee una linea de entrada y la guarda en el arreglo 'linea'.
        if (!cin.getline(linea, sizeof(linea))) 
            break;

        // Linea vacia, se omite iteracion del ciclo.
        if (strlen(linea) == 0) 
            continue;

        // strtok para dividir la linea en palabras separadas.
        token = strtok(linea, " ");

        // Busca los dos posibles argumentos (si existen).
        a1 = strtok(nullptr, " ");
        a2 = strtok(nullptr, " ");

        // Convierte tokens tipo 'char*' a 'string'.
        string comando(token), arg1, arg2;
 
        // Si los argumentos existen, se guardan.
        if (a1 != nullptr) {
            arg1 = string(a1);
            argc++;
        }

        if (a2 != nullptr) {
            arg2 = string(a2);
            argc++;
        }

        // Recorre la lista de comandos 'comandos[]'.
        for (int i = 0; i < numComandos; i++) {
            // Compara el comando ingresado.
            if (comando == comandos[i].nombre) {
                encontrado = true;

                // Verifica la cantidad de argumentos.
                if (argc != comandos[i].argumentos) {
                    cout << "[ERROR] Uso: " << comandos[i].uso << endl;
                } else {
                    // Verifica el numero de argumentos, ejecuta la funcion asociada.
                    comandos[i].funcion(arg1, arg2);
                }

                // Se encontro el comando.
                break;
            }
        }

        // Comando que no existe.
        if (!encontrado) {
            cout << "[ERROR] Comando invalido. Usa 'ayuda'." << endl;
        }
    }
}
// Implementacion de funciones.
void comando_ayuda(const string& arg1, const string&)
{
    if(arg1 == ""){
        printf("~~~~~~~~~~~~~~~~~~~ Lista de comandos ~~~~~~~~~~~~~~~~~~~\n");
        for(int i = 0; i<numComandos; i++){
            cout<<left<<comandos[i].nombre<< setw(20) <<"\t"<<comandos[i].descripcion<<"\n";
        }
        printf("\nSi desea ayuda con un comando especifico coloque ayuda <comando>");
    }else{
        for(int i = 0; i<numComandos; i++){

        }
    }
}

void comando_cargar(const string& arg1, const string&)
{
}

void comando_listar_secuencias(const string&, const string&)
{
}

void comando_histograma(const string& arg1, const string&)
{
}

void comando_subsecuencia(const string& arg1, const string& arg2)
{
}

void comando_enmascarar(const string& arg1, const string&)
{
}

void comando_guardar(const string& arg1, const string&)
{
}

void comando_codificar(const string& arg1, const string&)
{
}

void comando_decodificar(const string& arg1, const string&)
{
}

void comando_ruta_mas_corta(const string& arg1, const string&)
{
}

void comando_base_remota(const string& arg1, const string&)
{
}

void comando_salir(const string&, const string&)
{
    exit(0);
}