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
            cout << "[ERROR] Base inválida: '" << base << "' encontrada en la secuencia '" << descripcion << "'." << endl;
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
        for (int i = 0; i < linea.size(); i++) {
            if (linea[i] == '\r') {
                linea.erase(i, 1);
                i--; // retroceder porque la cadena se acortó
            }
        }
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
        linea.clear();
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
    // Obtener secuencias del sistema FASTA.
    vector<Secuencia>& secuencias = fasta.getSecuencias();
    vector<char> secuencia;

    vector<Secuencia>::iterator it;
    vector<char>::iterator itBase;

    // Recorrer todas las secuencias y contar frecuencias.
    for (it = secuencias.begin(); it != secuencias.end(); it++) {
        secuencia = it->getBases();
        for (itBase = secuencia.begin(); itBase != secuencia.end(); itBase++) {
            frecuencias[*itBase]++;
        }
    }
}

// Codificar las secuencias y guardarlas en un archivo .fabin
void Sistema::guardarCodificacion(string nombreArchivo) {
    // Validar extensión .fabin.
    if (!validarExtensionFABIN(nombreArchivo)) {
        cout << "[ERROR] '" << nombreArchivo << "' no es un archivo .fabin válido." << endl;
        return;
    }

    // Obtener secuencias en memoria.
    vector<Secuencia> secuencias = fasta.getSecuencias();
    uint32_t numSecuencias = static_cast<uint32_t>(secuencias.size());

    if (numSecuencias == 0) {
        cout << "[ERROR] No hay secuencias cargadas para codificar." << endl;
        return;
    }

    // Generar mapa de frecuencias y construir árbol de Huffman.
    frecuencias.clear();
    generarMapFrecuencia();
    uint16_t numBases = static_cast<uint16_t>(frecuencias.size());

    // Mostrar mapa de frecuencias (debug).
    cout << "[OK] Mapa de frecuencias generado correctamente:\n";
    map<char, int>::iterator itFrec;
    for (itFrec = frecuencias.begin(); itFrec != frecuencias.end(); itFrec++) {
        cout << "'" << itFrec->first << "' : " << itFrec->second << endl;
    }

    arbol.construir(frecuencias);

    // Abrir archivo binario de salida.
    ofstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo crear el archivo '" << nombreArchivo << "'." << endl;
        return;
    }

    // Escribir número de bases (n).
    archivo.write(reinterpret_cast<const char*>(&numBases), sizeof(numBases));

    // Escribir pares (ci, fi).
    for (itFrec = frecuencias.begin(); itFrec != frecuencias.end(); itFrec++) {
        uint8_t ci = static_cast<uint8_t>(itFrec->first);
        uint64_t fi = static_cast<uint64_t>(itFrec->second);
        archivo.write(reinterpret_cast<const char*>(&ci), sizeof(ci));
        archivo.write(reinterpret_cast<const char*>(&fi), sizeof(fi));
    }

    // Escribir número de secuencias (ns).
    archivo.write(reinterpret_cast<const char*>(&numSecuencias), sizeof(numSecuencias));

    // Mostrar los códigos de Huffman generados (debug).
    map<char, string> codigos = arbol.obtenerCodigos();
    map<char, string>::iterator itCodigo;
    cout << endl << "Códigos de Huffman generados: " << endl;
    for (itCodigo = codigos.begin(); itCodigo != codigos.end(); itCodigo++) {
        cout << "'" << itCodigo->first << "': " << itCodigo->second << endl;
    }

    // Recorrer las secuencias y guardarlas.
    vector<Secuencia>::iterator itSec;
    for (itSec = secuencias.begin(); itSec != secuencias.end(); itSec++) {
        // Obtener descripción y bases.
        string descripcion = itSec->getDescripcion();
        vector<char> bases = itSec->getBases();
        string texto(bases.begin(), bases.end());

        // Codificar usando Huffman.
        string bits = arbol.codificar(texto);

        // Empaquetar bits a bytes (binary_code).
        vector<uint8_t> bytes;
        for (size_t i = 0; i < bits.size(); i += 8) {
            string bloque = bits.substr(i, 8);
            while (bloque.size() < 8) {
                bloque.push_back('0');
            }
            
            uint8_t byte = 0;
            for (int b = 0; b < 8; b++) {
                if (bloque[b] == '1') {
                    byte |= (1 << (7 - b));
                }
            }
            bytes.push_back(byte);
        }

        // Campos según formato del enunciado.
        uint16_t li = static_cast<uint16_t>(descripcion.size());
        uint64_t vi = static_cast<uint64_t>(bits.size());
        uint16_t xi = static_cast<uint16_t>(itSec->getAncho());

        // Escribir: li, sij, vi, xi.
        archivo.write(reinterpret_cast<const char*>(&li), sizeof(li));
        archivo.write(descripcion.c_str(), li);
        archivo.write(reinterpret_cast<const char*>(&vi), sizeof(vi));
        archivo.write(reinterpret_cast<const char*>(&xi), sizeof(xi));

        // Escribir la secuencia codificada empaquetada.
        archivo.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());

        // Validación.
        if (!archivo) {
            cout << "[ERROR] Fallo al escribir la secuencia '" << descripcion << "'." << endl;
            archivo.close();
            return;
        }
    }

    archivo.close();
    cout << endl << "[OK] Archivo '" << nombreArchivo << "' generado exitosamente según formato .fabin." << endl;
}

// Cargar un archivo .fabin y decodificar las secuencias.
void Sistema::cargarCodificacion(string nombreArchivo) {
    // Validar extensión .fabin.
    if (!validarExtensionFABIN(nombreArchivo)) {
        cout << "[ERROR] '" << nombreArchivo << "' no es un archivo .fabin válido." << endl;
        return;
    }

    // Abrir archivo binario de entrada.
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo abrir '" << nombreArchivo << "'." << endl;
        return;
    }

    // Limpiar estructuras anteriores.
    frecuencias.clear();
    fasta = FASTA();

    // Leer número de bases (n).
    uint16_t numBases = 0;
    archivo.read(reinterpret_cast<char*>(&numBases), sizeof(numBases));
    if (!archivo) {
        cout << "[ERROR] No se pudo leer el número de bases." << endl;
        archivo.close();
        return;
    }

    // Leer pares (ci, fi).
    for (int i = 0; i < numBases; i++) {
        uint8_t ci = 0;
        uint64_t fi = 0;
        archivo.read(reinterpret_cast<char*>(&ci), sizeof(ci));
        archivo.read(reinterpret_cast<char*>(&fi), sizeof(fi));

        char base = static_cast<char>(ci);
        frecuencias[base] = static_cast<int>(fi);
    }

    // Mostrar mapa de frecuencias leído (debug).
    cout << "[OK] Frecuencias leídas correctamente: " << endl;
    map<char, int>::iterator it;
    for (it = frecuencias.begin(); it != frecuencias.end(); it++) {
        cout << "'" << it->first << "': " << it->second << endl;
    }

    // Reconstruir árbol de Huffman.
    arbol.construir(frecuencias);
    cout << "[OK] Árbol de Huffman reconstruido." << endl;

    // Leer número de secuencias (ns).
    uint32_t numSecuencias = 0;
    archivo.read(reinterpret_cast<char*>(&numSecuencias), sizeof(numSecuencias));
    if (!archivo) {
        cout << "[ERROR] No se pudo leer el número de secuencias." << endl;
        archivo.close();
        return;
    }

    cout << "[OK] Se encontraron " << numSecuencias << " secuencias codificadas." << endl;

    // Leer cada secuencia.
    for (uint32_t i = 0; i < numSecuencias; i++) {
        uint16_t li = 0;
        archivo.read(reinterpret_cast<char*>(&li), sizeof(li));

        // Leer nombre (sij).
        string descripcion(li, '\0');
        archivo.read(&descripcion[0], li);

        // Leer longitud (vi).
        uint64_t vi = 0;
        archivo.read(reinterpret_cast<char*>(&vi), sizeof(vi));

        // Leer ancho (xi).
        uint16_t xi = 0;
        archivo.read(reinterpret_cast<char*>(&xi), sizeof(xi));

        // Calcular cuántos bytes ocupa el código binario.
        uint64_t numBytes = (vi + 7) / 8;
        vector<uint8_t> bytes(numBytes);
        archivo.read(reinterpret_cast<char*>(&bytes[0]), numBytes);

        if (!archivo) {
            cout << "[ERROR] Error al leer los datos de la secuencia " << descripcion << endl;
            archivo.close();
            return;
        }

        // Desempaquetar los bits del binary_code a una cadena.
        string bits;
        bits.reserve(vi);
        for (uint64_t b = 0; b < numBytes; b++) {
            for (int k = 7; k >= 0; k--) {
                if (((bytes[b] >> k) & 1)) {
                    bits.push_back('1');
                } else {
                    bits.push_back('0');
                }
            }
        }

        // Si el último byte tenía bits de relleno, recortamos.
        if (bits.size() > vi) {
            bits.resize(vi);
        }

        // Decodificar con el árbol Huffman.
        string secuenciaDecodificada = arbol.decodificar(bits);

        // Guardar en el sistema FASTA.
        vector<char> bases(secuenciaDecodificada.begin(), secuenciaDecodificada.end());
        int contador = static_cast<int>(i);
        guardarSecuencia(descripcion, bases, xi, contador);

        cout << "[OK] Secuencia '" << descripcion << "' decodificada. " << "Longitud: " << vi << " bits (" << bases.size() << " bases) ." << endl;
    }

    archivo.close();
    cout << endl << "[OK] Archivo '" << nombreArchivo << "' decodificado exitosamente." << endl;
}

// Devuelve una referencia al objeto que pertenece al Sistema.
FASTA& Sistema::getFASTA() {
    return fasta;
}
