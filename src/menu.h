#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>

#include "comando.h"

using namespace std;

// Clase Menú, representa la interfaz del usuario en consola.
class Menu {
    private:
        // Lista de comandos registrados.
        static vector <Comando> comandos;

    public:
        // Constructor.
        Menu();

        //Imprime el menú.
        void imprimirMenu();

        // Inicializa todos los comandos del sistema.
        void inicializarComandos();

        // Comandos del menú.
        static void comandoAyuda(const string& arg1, const string& arg2, const string&, const string&, const string&);
        static void comandoCargar(const string& arg1, const string& arg2, const string&, const string&, const string&);
        static void comandoListarSecuencias(const string&, const string&, const string&, const string&, const string&);
        static void comandoHistograma(const string& arg1, const string&, const string&, const string&, const string&);
        static void comandoSubsecuencia(const string& arg1, const string&, const string&, const string&, const string&);
        static void comandoEnmascarar(const string& arg1, const string&, const string&, const string&, const string&);
        static void comandoGuardar(const string& arg1, const string&, const string&, const string&, const string&);
        static void comandoSalir(const string&, const string&, const string&, const string&, const string&);
        static void comandoCodificar(const string& arg1, const string&, const string&, const string&, const string&);
        static void comandoDecodificar(const string& arg1, const string&, const string&, const string&, const string&);
        static void comandoRutaMasCorta(const string& arg1, const string& arg2, const string& arg3, const string& arg4, const string& arg5);
        static void comandoBaseRemota(const string& arg1, const string& arg2, const string& arg3, const string&, const string&);

};

#endif
