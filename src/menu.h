#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include "comando.h"
#include "FASTA.h"

using namespace std;

class Menu {
    private:
        // Lista de comandos registrados.
        static vector <Comando> comandos;   // lista de comandos registrados

    public:
        // Constructor.
        Menu();

        //Imprime el menu
        void imprimirMenu();

        // Registrar un comando.
        void inicializarComandos();

        // Mostrar todos los comandos.
        static void comandoAyuda(const string& arg1, const string& arg2);
        static void comandoCargar(const string& arg1, const string& arg2);
        static void comandoListarSecuencias(const string&, const string&);
        static void comandoHistograma(const string& arg1, const string&);
        static void comandoSubsecuencia(const string& arg1, const string& arg2);
        static void comandoEnmascarar(const string& arg1, const string&);
        static void comandoGuardar(const string& arg1, const string&);
        static void comandoRutaMasCorta(const string& arg1, const string& arg2);
        static void comandoSalir(const string&, const string&);
        
};

#endif