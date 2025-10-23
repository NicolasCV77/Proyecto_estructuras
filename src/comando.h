#ifndef COMANDO_H
#define COMANDO_H

#include <string>

using namespace std;

// Alias de tipo ComandoFuncion, para punteros a funciones de comandos. 
typedef void (*ComandoFuncion)(const string&, const string&);

// Clase Comando, representa un comando que puede ejecutarse desde el menú.
class Comando {
    private:
        // Atributos de un comando.
        ComandoFuncion accion; 
        string nombre;
        int argumentos;
        string descripcion;
        string uso;
        
    public:
        // Constructor.
        Comando(ComandoFuncion accion, const string& nombre, int argumentos, const string& descripcion, const string& uso);

        // Métodos de acceso.
        string getNombre();
        string getDescripcion();
        string getUso();
        int getArgumentos();

        // Ejecutar la función asociada al comando.
        void ejecutar(const string& arg1, const string& arg2);
        
};

#endif
