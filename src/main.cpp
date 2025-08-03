#include <iostream>

using namespace std;

int main() {
      // Este ciclo permite ejecutar el men?
  do 
  {
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~  JAVEBIBLIOTECA  ~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "0. Salir." << endl;
    cout << "1. Agregar libros." << endl;
    cout << "2. Registrar nuevos usuario." << endl;
    cout << "3. Realizar pr?stamo." << endl;
    cout << "4. Devolver libro." << endl;
    cout << "5. Buscar libro." << endl;
    cout << "6. Mostrar libros disponibles." << endl;
    cout << "7. Guardar datos de la biblioteca." << endl;
    cout << "8. Cargar datos de la biblioteca." << endl;
    cout << "~" << endl;
    cout << "Elija su opci?n: ";

    // Validamos que la entrada del usuario si sea un n?mero del men?.
    while (!(cin >> opcion) || opcion < 0 || opcion > 8 ) 
    {
      cout << "Opci?n inv?lida. Por favor, ingrese un n?mero entre 0 y 8: ";
      cin.clear();
      cin.ignore(10000, '\n');
    }

    // MEN? - Evaluamos la opci?n seleccionada
    switch (opcion) 
    {
      case 0: // Salir
        cout << "Gracias por usar JAVEBIBLIOTECA." << endl;
        cout << "Saliendo..." << endl;
      break;

      case 1: // Punto 1
        cout << endl << " - AGREGAR LIBROS - " << endl;
        libros = agregarLibros(libros, &numLibros);
      break;

      case 2: // Punto 2
        cout << endl << " - REGISTRAR NUEVOS USUARIOS - " << endl;
        usuarios = agregarUsuario(usuarios, &numUsuarios);
      break;

      case 3: // Punto 3
        cout << endl << "- REALIZAR PR?STAMO - " << endl;
        prestamoLibro(prestamos, &numPrestamos, usuarios, &numUsuarios, libros, &numLibros);
      break;

      case 4: // Punto 4
        cout << endl << " - DEVOLVER LIBRO - " << endl;
        devolverLibro(prestamos, &numPrestamos, libros, &numLibros);
      break;

      case 5: // Punto 5
        cout << endl << " - BUSCAR LIBRO - " << endl;
        buscarLibro(libros, &numLibros);
      break;

      case 6: // Punto 6
        cout << endl << " - MOSTRAR LIBROS DISPONIBLES - " << endl;
        mostrarLibrosDisponibles(libros, numLibros);
      break;

      case 7: // Punto 7
        cout << endl << " - GUARDAR DATOS DE LA JAVEBIBLIOTECA - " << endl;
        menuGuardar(libros, numLibros, usuarios, numUsuarios, prestamos, numPrestamos, devoluciones, numDevoluciones);
      break;

      case 8: // Punto 8
        cout << endl << " - CARGAR DATOS A LA JAVEBIBLIOTECA - " << endl;
        menuCargar(libros, numLibros, usuarios, numUsuarios, prestamos, numPrestamos, devoluciones, numDevoluciones);
      break;

      default: // Opci?n no v?lida
        cout << "Opci?n no v?lida." << endl;
        cout << "Intentelo de nuevo." << endl;
      break;
    }
  } while (opcion != 0);
}