#include <iostream>
#include <fstream>

#include "sistema.h"

// Validar extensión .fa del archivo.
bool Sistema::validarExtensionFA(string& nombreArchivo) {
    return (nombreArchivo.rfind(".fa") == nombreArchivo.size() - 3);
}

// Validar extensión .fabin del archivo.
bool Sistema::validarExtensionFABIN(string& nombreArchivo) {
    return (nombreArchivo.rfind(".fabin") == nombreArchivo.size() - 6);
}

// Validar el ancho de cada una de las líneas.
bool Sistema::validarLineas(vector<string>& lineas, string& descripcion, int ancho) {
    // Recorremos todas las líneas guardadas.
    vector<string>::iterator itLineas;
    for (itLineas = lineas.begin(); itLineas != lineas.end(); itLineas++) {
        bool esUltima = (itLineas == lineas.end() - 1);
        int tamano = (*itLineas).size();

        if (!esUltima && tamano != ancho) {
            cout << "[ERROR] Ancho inválido en la secuencia '" << descripcion << "'." << endl;
            return false;
        }

        if (esUltima && tamano > ancho) {
            cout << "[ERROR] Ancho inválido en la secuencia '" << descripcion << "'." << endl;
            return false;
        }
    }
    return true;
}

// Validar la existencia de las bases.
bool Sistema::validarBases(string& linea, string& descripcion, vector<char>& bases) {
    for (int i = 0; i < linea.size(); i++) {
        char base = linea[i];
        bool valida = false;

        // Recorremos todos los componentes dentro del sistema.
        vector<vector<char>>::iterator itComponentes;
        for (itComponentes = fasta.getComponentes().begin(); itComponentes != fasta.getComponentes().end(); itComponentes++) {
            if (base == (*itComponentes)[0]) {
                valida = true;
                break;
            }
        }

        // No se encontró dentro del sistema.
        if (!valida) {
            cout << "[ERROR] Base inválida '" << base << "' encontrada en la secuencia '" << descripcion << "'." << endl;
            return false;
        }

        bases.push_back(base);
    }
    return true;
}

// Guardar una secuencia dentro del sistema.
void Sistema::guardarSecuencia(string& descripcion, vector<char>& bases, int ancho, int& contador) {
    Secuencia secuencia(descripcion, bases, ancho);
    fasta.agregarSecuencia(secuencia);
    contador++;
}

// Escribe una secuencia en un archivo .fa
void Sistema::escribirSecuencia(ofstream& archivo, vector<Secuencia>::iterator it) {
    archivo << ">" << it->getDescripcion() << endl;

    vector<char> bases = it->getBases();
    int ancho = it->getAncho();
    int contador = 0;

    vector<char>::iterator itB;
    for (itB = bases.begin(); itB != bases.end(); itB++) {
        archivo << *itB;
        contador++;

        if (contador == ancho) {
            archivo << endl;
            contador = 0;
        }
    }

    // Última línea incompleta.
    if (contador != 0) {
        archivo << endl;
    }
}

// Cargar un archivo FASTA en memoria.
void Sistema::cargarArchivo(string nombreArchivo) {
    // Validar extensión.
    if (!validarExtensionFA(nombreArchivo)) {
        cout << "[ERROR] '" << nombreArchivo << "' no es un archivo .fa válido." << endl;
        return;
    }

    // Intentar abrir el archivo.
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "[ERROR] '" << nombreArchivo << "' no se encuentra o no puede leerse." << endl;
        return;
    }

    // Reiniciar contenedor.
    fasta = FASTA();

    // Variables auxiliares.
    vector<string> lineas; 
    vector<char> bases;
    string linea;
    string descripcion = ""; 
    int ancho, secuencias = 0;
    bool bandera = true;

    // Leer archivo línea por línea.
    while (getline(archivo, linea)) {
        // Saltar líneas vacías.
        if (linea.empty()) {
            continue;
        }

        // Validar carácter '>', nueva descripción.
        if (linea[0] == '>') {
            if (!bandera && !descripcion.empty()) {
                // Validar ancho de las líneas de la secuencia.
                if (!validarLineas(lineas, descripcion, ancho)) {
                    return;
                }

                // Guardar la secuencia dentro del sistema.
                guardarSecuencia(descripcion, bases, ancho, secuencias);
            }

            // Actualizar descripción y limpiar varibles.
            lineas.clear();
            bases.clear();
            descripcion = linea.substr(1);
            ancho = 0; 
            bandera = false;
        } else {
            // No se encontró una descripción.
            if (bandera) {
                cout << "[ERROR] Formato inválido... El archivo no inicia con '>'." << endl;
                return;
            }

            // Guardar la línea completa.
            lineas.push_back(linea);

            // Registrar ancho de la primera línea.
            if (lineas.size() == 1) {
                ancho = linea.size();
            }

            // Validar las bases de la secuencia.
            if (!validarBases(linea, descripcion, bases)) {
                return;
            }
        }
    }

    // Guardar última secuencia si existe.
    if (!descripcion.empty()) {
        // Validar ancho de las líneas de la secuencia.
        if (!validarLineas(lineas, descripcion, ancho)) {
            return;
        }

        // Guardar la secuencia dentro del sistema.
        guardarSecuencia(descripcion, bases, ancho, secuencias);
    }

    // Mensajes en pantalla.
    if (secuencias == 0) {
        cout << "[ERROR] '" << nombreArchivo << "' no contiene ninguna secuencia." << endl;  
    } else if (secuencias == 1) {
        cout << "[OK] 1 secuencia cargada correctamente desde '" << nombreArchivo << "'." << endl; 
    } else {
        cout << "[OK] " << secuencias << " secuencias cargadas desde '" << nombreArchivo << "'." << endl;
    }

    archivo.close();
}

// Guardar un archivo FASTA con las secuencias.
void Sistema::guardarArchivo(string nombreArchivo) {
    // Validar extensión.
    if (!validarExtensionFA(nombreArchivo)) {
        cout << "[ERROR] '" << nombreArchivo << "' no es un archivo .fa válido." << endl;
        return;
    }

    // Verificar secuencias cargadas.
    vector<Secuencia>& secuencias = fasta.getSecuencias();
    if (secuencias.empty()) {
        cout << "[ERROR] No hay secuencias guardadas en memoria." << endl;
        return;
    }

    // Abrir archivo.
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "[ERROR] Problemas guardando en '" << nombreArchivo << "'." << endl;
        return;
    }

    // Escribir cada secuencia.
    vector<Secuencia>::iterator it;
    for (it = secuencias.begin(); it != secuencias.end(); it++) {
        escribirSecuencia(archivo, it);
    }

    archivo.close();
    cout << "Las secuencias han sido guardadas en '" << nombreArchivo << "'." << endl;
}

// Generar el mapa de frecuencias a partir de las secuencias cargadas.
void Sistema::generarMapFrecuencia() {
    vector<Secuencia>& secuencias = fasta.getSecuencias();
    vector<char> secuencia;
    vector<Secuencia>::iterator it;
    vector<char>::iterator itBase;

    for (it = secuencias.begin(); it != secuencias.end(); it++) {
        secuencia = it->getBases();
        for (itBase = secuencia.begin(); itBase != secuencia.end(); itBase++) {
            frecuencias[*itBase]++;
        }
    }

    cout << "[OK] Mapa de frecuencias generado correctamente." << endl;
}

// Codificar las secuencias y guardarlas en un archivo .fabin
void Sistema::guardarCodificacion(string nombreArchivo) {
    // Validar extensión.
    if (!validarExtensionFABIN(nombreArchivo)) {
        cout << "[ERROR] '" << nombreArchivo << "' no es un archivo .fabin válido." << endl;
        return;
    }

    // Obtener secuencias del sistema.
    vector<Secuencia> secuencias = fasta.getSecuencias();
    uint32_t numSecuencias = static_cast<uint32_t> (secuencias.size());

    // Verificar que hayan secuencias para codificar.
    if (numSecuencias == 0) {
        cout << "No hay secuencias cargadas, vuelva a intentarlo" << endl;
        return;
    }

    // Primeros pasos para realizar el archivo codificado.
    frecuencias.clear();
    generarMapFrecuencia();
    uint16_t numBases = static_cast<uint16_t> (frecuencias.size());

    // Debug
    cout << "[OK] Mapa de frecuencias generado correctamente.\n";
    for (auto &p : frecuencias) {
        cout << (int)p.first << " [" << p.first << "]: " << p.second << endl;
    }

    arbol.construir(frecuencias);

    // Abrir archivo.
    ofstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cout << "[ERROR] Problemas guardando en '" << nombreArchivo << "'." << endl;
        return;
    }

    // Se escribe el número de bases.
    archivo.write(reinterpret_cast<const char*>(&numBases), sizeof(numBases));


    // Escribir bases con su frecuencia según el mapa.
    map<char, int>::iterator itFrec = frecuencias.begin();
    for (itFrec = frecuencias.begin(); itFrec != frecuencias.end(); ++itFrec) {
        char base = itFrec->first;               // Ejemplo: 'A', 'C', 'G', 'T'
        int frec = itFrec->second;     // Frecuencia asociada a la base

        if (frec < 0) {
            frec = 0; // Seguridad
        }

        uint8_t ci = static_cast<uint8_t>(static_cast<unsigned char>(base));
        uint64_t fi = static_cast<uint64_t>(frec);

        archivo.write(reinterpret_cast<const char*>(&ci), sizeof(ci));
        archivo.write(reinterpret_cast<const char*>(&fi), sizeof(fi));

        if (!archivo) {
            cerr << "Error al escribir par (ci, fi) para la base: " << base << "\n";
            archivo.close();
            return;
        }
    }   

    //Se escribe el numero de secuencias
    archivo.write(reinterpret_cast<const char*>(&numSecuencias), sizeof(numSecuencias));
    if (!archivo) {
        std::cerr << "Error al escribir el número de secuencias.\n";
        archivo.close();
        return;
    }

    // Recorrer las secuencias y guardarlas en el archivo
    vector<Secuencia>::iterator itSec;
    vector<char> bases;
    string secuenciaSinCodificar;
    string secuenciaCodificada;

    // Debug: Mostrar los códigos generados
    map<char, string> codigos = arbol.obtenerCodigos();
    cout << "Códigos de Huffman generados:\n";
    for (const auto& par : codigos) {
        cout << "'" << (par.first ? par.first : '.') << "': " << par.second << "\n";
    }

    for (itSec = secuencias.begin(); itSec != secuencias.end(); ++itSec) {
        // 1️⃣ Obtener las bases sin codificar
        bases = itSec->getBases();
        secuenciaSinCodificar = string(bases.begin(), bases.end());

        // 2️⃣ Codificar usando el árbol de Huffman
        secuenciaCodificada = arbol.codificar(secuenciaSinCodificar);

        // 3️⃣ Guardar la descripción de la secuencia (longitud + texto)
        string descripcion = itSec->getDescripcion();
        uint16_t tamDescripcion = static_cast<uint16_t>(descripcion.size());
        archivo.write(reinterpret_cast<const char*>(&tamDescripcion), sizeof(tamDescripcion));
        archivo.write(descripcion.c_str(), tamDescripcion);

        // 4️⃣ Guardar la longitud de la secuencia codificada (en bits o bytes, según tu diseño)
        uint32_t tamCodificada = static_cast<uint32_t>(secuenciaCodificada.size());
        archivo.write(reinterpret_cast<const char*>(&tamCodificada), sizeof(tamCodificada));

        // 5️⃣ Guardar la secuencia codificada (como texto binario)
        archivo.write(secuenciaCodificada.c_str(), tamCodificada);

        // 6️⃣ Verificación
        if (!archivo) {
            cerr << "Error al escribir la secuencia: " << descripcion << "\n";
            archivo.close();
            return;
        }
    }
}

// Cargar un archivo .fabin y decodificar las secuencias.
void Sistema::cargarCodificacion(string nombreArchivo) {
    // Validar extensión
    if (!validarExtensionFABIN(nombreArchivo)) {
        cout << "[ERROR] '" << nombreArchivo << "' no es un archivo .fabin válido." << endl;
        return;
    }

    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cout << "[ERROR] '" << nombreArchivo << "' no se encuentra o no puede leerse." << endl;
        return;
    }

    // Limpiar datos previos
    frecuencias.clear();
    fasta = FASTA();

    // 1️⃣ Leer el número de bases
    uint16_t numBases;
    archivo.read(reinterpret_cast<char*>(&numBases), sizeof(numBases));

    if (!archivo) {
        cout << "[ERROR] No se pudo leer el número de bases." << endl;
        archivo.close();
        return;
    }

    // 2️⃣ Leer pares (base, frecuencia)
    for (int i = 0; i < numBases; ++i) {
        uint8_t ci;
        uint64_t fi;
        archivo.read(reinterpret_cast<char*>(&ci), sizeof(ci));
        archivo.read(reinterpret_cast<char*>(&fi), sizeof(fi));

        char base = static_cast<char>(ci);
        frecuencias[base] = static_cast<int>(fi);
    }

    cout << "[OK] Mapa de frecuencias leído correctamente.\n";
    for (auto &par : frecuencias) {
        cout << par.first << " : " << par.second << endl;
    }

    // 3️⃣ Reconstruir el árbol Huffman
    cout << "Reconstruyendo árbol de Huffman...\n";
    arbol.construir(frecuencias);

    // 4️⃣ Leer número de secuencias
    uint32_t numSecuencias;
    archivo.read(reinterpret_cast<char*>(&numSecuencias), sizeof(numSecuencias));

    cout << "[OK] Número de secuencias: " << numSecuencias << endl;

    // 5️⃣ Leer cada secuencia
    int contador = 0;
    for (uint32_t i = 0; i < numSecuencias; ++i) {
        // Longitud de la descripción
        uint16_t tamDescripcion;
        archivo.read(reinterpret_cast<char*>(&tamDescripcion), sizeof(tamDescripcion));

        // Descripción
        string descripcion(tamDescripcion, '\0');
        archivo.read(&descripcion[0], tamDescripcion);

        // Longitud de la secuencia codificada
        uint32_t tamCodificada;
        archivo.read(reinterpret_cast<char*>(&tamCodificada), sizeof(tamCodificada));

        // Secuencia codificada
        string secuenciaCodificada(tamCodificada, '\0');
        archivo.read(&secuenciaCodificada[0], tamCodificada);

        cout << "Decodificando secuencia: " << descripcion << " (" << tamCodificada << " bits)\n";

        // 6️⃣ Decodificar usando el árbol
        string secuenciaDecodificada = arbol.decodificar(secuenciaCodificada);

        // 7️⃣ Guardar en el sistema FASTA
        vector<char> bases(secuenciaDecodificada.begin(), secuenciaDecodificada.end());
        int ancho = 70; // Puedes ajustarlo según tus necesidades
        guardarSecuencia(descripcion, bases, ancho, contador);
    }

    archivo.close();
    cout << "[OK] Archivo '" << nombreArchivo << "' decodificado exitosamente." << endl;
}


// Devuelve una referencia al objeto que pertenece al Sistema.
FASTA& Sistema::getFASTA() {
    return fasta;
}
