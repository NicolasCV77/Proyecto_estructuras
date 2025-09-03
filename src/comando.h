#ifndef COMANDO_H
#define COMANDO_H

#include <string>

using namespace std;

// Alias para punteros a funciones de comandos.
typedef void (*ComandoFuncion)(const string&, const string&);

class Comando {
    private:
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

        // Ejecutar.
        void ejecutar(const string& arg1, const string& arg2);
        
};

#endif