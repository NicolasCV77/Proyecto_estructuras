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
        // Eliminar caracteres '\r' si existen.
        for (int i = 0; i < linea.size(); i++) {
            if (linea[i] == '\r') {
                linea.erase(i, 1);
                i--;
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
    vector<Secuencia> listaSecuencias = fasta.getSecuencias();
    uint32_t cantidadSecuencias = static_cast<uint32_t>(listaSecuencias.size());

    if (cantidadSecuencias == 0) {
        cout << "[ERROR] No hay secuencias cargadas para codificar." << endl;
        return;
    }

    // Generar mapa de frecuencias y construir árbol de Huffman.
    frecuencias.clear();
    generarMapFrecuencia();
    uint16_t cantidadBasesUnicas = static_cast<uint16_t>(frecuencias.size());

    // Mostrar mapa de frecuencias.
    cout << "[OK] Frecuencias calculadas correctamente: " << endl;
    
    map<char, int>::iterator iteradorFrecuencia;
    for (iteradorFrecuencia = frecuencias.begin(); iteradorFrecuencia != frecuencias.end(); iteradorFrecuencia++) {
        cout << "'" << iteradorFrecuencia->first << "' : " << iteradorFrecuencia->second << endl;
    }

    arbol.construir(frecuencias);

    // Abrir archivo binario de salida.
    ofstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo crear el archivo '" << nombreArchivo << "'." << endl;
        return;
    }

    // Escribir número de bases únicas.
    archivo.write(reinterpret_cast<const char*>(&cantidadBasesUnicas), sizeof(cantidadBasesUnicas));

    // Escribir pares (base, frecuenciaBase).
    for (iteradorFrecuencia = frecuencias.begin(); iteradorFrecuencia != frecuencias.end(); iteradorFrecuencia++) {
        uint8_t baseActual = static_cast<uint8_t>(iteradorFrecuencia->first);
        uint64_t frecuenciaBase = static_cast<uint64_t>(iteradorFrecuencia->second);
        archivo.write(reinterpret_cast<const char*>(&baseActual), sizeof(baseActual));
        archivo.write(reinterpret_cast<const char*>(&frecuenciaBase), sizeof(frecuenciaBase));
    }

    // Escribir número total de secuencias.
    archivo.write(reinterpret_cast<const char*>(&cantidadSecuencias), sizeof(cantidadSecuencias));

    // Mostrar los códigos de Huffman generados.
    cout << endl << "Códigos de Huffman generados: " << endl;

    map<char, string> codigos = arbol.obtenerCodigos();
    map<char, string>::iterator iteradorCodigo;
    for (iteradorCodigo = codigos.begin(); iteradorCodigo != codigos.end(); iteradorCodigo++) {
        cout << "'" << iteradorCodigo->first << "': " << iteradorCodigo->second << endl;
    }

    // Recorrer las secuencias y guardarlas.
    vector<Secuencia>::iterator iteradorSecuencia;
    for (iteradorSecuencia = listaSecuencias.begin(); iteradorSecuencia != listaSecuencias.end(); iteradorSecuencia++) {
        // Obtener descripción y bases.
        string descripcion = iteradorSecuencia->getDescripcion();
        vector<char> bases = iteradorSecuencia->getBases();
        string texto(bases.begin(), bases.end());

        // Codificar usando Huffman.
        string bits = arbol.codificar(texto);

        // Empaquetar bits a bytes.
        vector<uint8_t> bytesCodificados;
        for (size_t i = 0; i < bits.size(); i += 8) {
            string bloque = bits.substr(i, 8);
            while (bloque.size() < 8) {
                bloque.push_back('0');
            }
            
            uint8_t byte = 0;
            // Convertir bloque de 8 bits a un byte.
            for (int b = 0; b < 8; b++) {
                if (bloque[b] == '1') {
                    int posicionBit = 7 - b;
                    uint8_t mascara = (1 << posicionBit);
                    byte = byte + mascara;
                }
            }
            bytesCodificados.push_back(byte);
        }

        // Campos según formato del enunciado.
        uint16_t longitudDescripcion = static_cast<uint16_t>(descripcion.size());
        uint64_t longitudBitsCodificados = static_cast<uint64_t>(bits.size());
        uint16_t anchoSecuencia = static_cast<uint16_t>(iteradorSecuencia->getAncho());

        // Escribir: longitudDescripcion, descripcion, longitudBitsCodificados, anchoSecuencia.
        archivo.write(reinterpret_cast<const char*>(&longitudDescripcion), sizeof(longitudDescripcion));
        archivo.write(descripcion.c_str(), longitudDescripcion);
        archivo.write(reinterpret_cast<const char*>(&longitudBitsCodificados), sizeof(longitudBitsCodificados));
        archivo.write(reinterpret_cast<const char*>(&anchoSecuencia), sizeof(anchoSecuencia));

        // Escribir la secuencia codificada empaquetada.
        archivo.write(reinterpret_cast<const char*>(bytesCodificados.data()), bytesCodificados.size());

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

    // Leer número de bases únicas.
    uint16_t cantidadBasesUnicas = 0;
    archivo.read(reinterpret_cast<char*>(&cantidadBasesUnicas), sizeof(cantidadBasesUnicas));
    if (!archivo) {
        cout << "[ERROR] No se pudo leer el número de bases." << endl;
        archivo.close();
        return;
    }

    // Leer pares (baseActual, frecuenciaBase).
    for (int i = 0; i < cantidadBasesUnicas; i++) {
        uint8_t baseActual = 0;
        uint64_t frecuenciaBase = 0;
        archivo.read(reinterpret_cast<char*>(&baseActual), sizeof(baseActual));
        archivo.read(reinterpret_cast<char*>(&frecuenciaBase), sizeof(frecuenciaBase));

        char base = static_cast<char>(baseActual);
        frecuencias[base] = static_cast<int>(frecuenciaBase);
    }

    // Mostrar mapa de frecuencias leído.
    cout << "[OK] Frecuencias leídas correctamente: " << endl;

    map<char, int>::iterator iteradorFrecuencia;
    for (iteradorFrecuencia = frecuencias.begin(); iteradorFrecuencia != frecuencias.end(); iteradorFrecuencia++) {
        cout << "'" << iteradorFrecuencia->first << "': " << iteradorFrecuencia->second << endl;
    }

    // Reconstruir árbol de Huffman.
    arbol.construir(frecuencias);
    cout << "[OK] Árbol de Huffman reconstruido." << endl;

    // Leer número de secuencias.
    uint32_t cantidadSecuencias = 0;
    archivo.read(reinterpret_cast<char*>(&cantidadSecuencias), sizeof(cantidadSecuencias));
    if (!archivo) {
        cout << "[ERROR] No se pudo leer el número de secuencias." << endl;
        archivo.close();
        return;
    }

    cout << "[OK] Se encontraron " << cantidadSecuencias << " secuencias codificadas." << endl;

    // Leer cada secuencia codificada.
    for (uint32_t i = 0; i < cantidadSecuencias; i++) {
        // Leer longitud de la descripción.
        uint16_t longitudDescripcion = 0;
        archivo.read(reinterpret_cast<char*>(&longitudDescripcion), sizeof(longitudDescripcion));

        // Leer descripción o nombre.
        string descripcion(longitudDescripcion, '\0');
        archivo.read(&descripcion[0], longitudDescripcion);

        // Leer longitud en bits.
        uint64_t longitudBitsCodificados = 0;
        archivo.read(reinterpret_cast<char*>(&longitudBitsCodificados), sizeof(longitudBitsCodificados));

        // Leer ancho original.
        uint16_t anchoSecuencia = 0;
        archivo.read(reinterpret_cast<char*>(&anchoSecuencia), sizeof(anchoSecuencia));

        // Calcular bytes necesarios para almacenar los bits.
        uint64_t cantidadBytesCodificados = (longitudBitsCodificados + 7) / 8;
        vector<uint8_t> bytesCodificados(cantidadBytesCodificados);
        archivo.read(reinterpret_cast<char*>(&bytesCodificados[0]), cantidadBytesCodificados);

        if (!archivo) {
            cout << "[ERROR] Error al leer los datos de la secuencia " << descripcion << endl;
            archivo.close();
            return;
        }

        // Desempaquetar los bits a una cadena.
        string cadenaBits;
        cadenaBits.reserve(longitudBitsCodificados);
        for (uint64_t b = 0; b < cantidadBytesCodificados; b++) {
            for (int k = 7; k >= 0; k--) {
                if (((bytesCodificados[b] >> k) & 1)) {
                    cadenaBits.push_back('1');
                } else {
                    cadenaBits.push_back('0');
                }
            }
        }

        // Eliminar bits de relleno sobrantes.
        if (cadenaBits.size() > longitudBitsCodificados) {
            cadenaBits.resize(longitudBitsCodificados);
        }

        // Decodificar usando el árbol Huffman.
        string textoDecodificado = arbol.decodificar(cadenaBits);

        // Guardar en el sistema FASTA.
        vector<char> bases(textoDecodificado.begin(), textoDecodificado.end());
        int indiceSecuencia = static_cast<int>(i);
        guardarSecuencia(descripcion, bases, anchoSecuencia, indiceSecuencia);

        cout << "[OK] Secuencia '" << descripcion << "' decodificada. " << endl;
        cout << "Longitud: " << longitudBitsCodificados << " bits (" << bases.size() << " bases)." << endl;
    }

    archivo.close();
    cout << endl << "[OK] Archivo '" << nombreArchivo << "' decodificado exitosamente." << endl;
}

// Encontrar la ruta más corta entre dos coordenadas en una secuencia dada.
void Sistema::rutaMasCorta(const string& descripcion, const string& i, const string& j, const string& x, const string& y) {
    // Convertir coordenadas a enteros.
    int filaInicio = stoi(i);
    int columnaInicio = stoi(j);
    int filaFin = stoi(x);
    int columnaFin = stoi(y);

    // Obtener la secuencia desde FASTA.
    Secuencia* secuencia = fasta.buscarSecuencia(descripcion);

    if (secuencia == nullptr) {
        cout << "[ERROR] La secuencia '" << descripcion << "' no existe." << endl;
        return;
    }

    vector<char> bases = secuencia->getBases();
    int ancho = secuencia->getAncho();
    int total = bases.size();

    // Construir matriz irregular SOLO para validar coordenadas
    int filas = (total + ancho - 1) / ancho;
    vector<vector<char>> matriz(filas);
    int posicion = 0;

    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < ancho && posicion < total; columna++) {
            matriz[fila].push_back(bases[posicion]);
            posicion++;
        }
    }

    // Validar coordenada inicial.
    if (filaInicio < 0 || filaInicio >= filas || columnaInicio < 0 || columnaInicio >= matriz[filaInicio].size()) {
        cout << "La base en la posición [" << i << " ," << j << "] no existe." << endl;
        return;
    }

    // Validar coordenada final.
    if (filaFin < 0 || filaFin >= filas || columnaFin < 0 || columnaFin >= matriz[filaFin].size()) {
        cout << "La base en la posición [" << x << " ," << y << "] no existe." << endl;
        return;
    }

    // Obtener bases inicial y final.
    char baseInicio = matriz[filaInicio][columnaInicio];
    char baseFin = matriz[filaFin][columnaFin];

    // Obtener el grafo que ya viene construido dentro de la secuencia
    Grafo& grafo = secuencia->getGrafo();

    // Ejecutar dijkstra.
    grafo.dijkstra(filaInicio, columnaInicio, filaFin, columnaFin);

    // Obtener distancia y ruta.
    double distancia = grafo.obtenerDistancia(filaFin, columnaFin);
    vector<pair<int,int>> ruta = grafo.obtenerRuta(filaInicio, columnaInicio, filaFin, columnaFin);

    cout << "Para la secuencia " << descripcion << ", la ruta más corta entre la base " << baseInicio
        << " en [" << i << " ," << j << "] y la base " << baseFin << " en [" << x << " ," << y << "] es: " << endl;

    // Imprimir la secuencia de bases en la ruta.
    for (int i = 0; i < ruta.size(); i++) {
        int rf = ruta[i].first;
        int rc = ruta[i].second;
        cout << matriz[rf][rc];

        if (i + 1 < ruta.size()) { 
            cout << " -> "; 
        }
    }

    cout << endl << "El costo total de la ruta es: " << distancia << endl;
}

// Encontrar la base remota en una secuencia dada.
void Sistema::baseRemota(const string& descripcion, const string& i, const string& j) {
    // Convertir coordenadas a enteros.
    int filaInicio = stoi(i);
    int colInicio  = stoi(j);

    // Obtener la secuencia desde FASTA.
    Secuencia* secuencia = fasta.buscarSecuencia(descripcion);

    if (secuencia == nullptr) {
        cout << "La secuencia " << descripcion << " no existe." << endl;
        return;
    }

    vector<char> bases = secuencia->getBases();
    int ancho = secuencia->getAncho();
    int total = bases.size();

    // Construir matriz irregular.
    int filas = (total + ancho - 1) / ancho;
    vector<vector<char>> matriz(filas);
    int posicion = 0;

    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < ancho && posicion < total; columna++) {
            matriz[fila].push_back(bases[posicion]);
            posicion++;
        }
    }

    // Validar coordenada inicial.
    if (filaInicio < 0 || filaInicio >= filas || colInicio < 0 || colInicio >= matriz[filaInicio].size()) {
        cout << "La base en la posición [" << i << " ," << j << "] no existe." << endl;
        return;
    }

    // Encontrar todas las ocurrencias de la base objetivo.
    char baseObjetivo = matriz[filaInicio][colInicio];
    vector<pair<int,int>> ocurrencias;
    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < matriz[fila].size(); columna++) {
            if (matriz[fila][columna] == baseObjetivo) {
                ocurrencias.push_back({fila, columna});
            }
        }
    }

    // Eliminar la ocurrencia inicial.
    for (int i = 0; i < ocurrencias.size(); i++) {
        if (ocurrencias[i].first == filaInicio && ocurrencias[i].second == colInicio) {
            ocurrencias.erase(ocurrencias.begin() + i);
            break;
        }
    }

    // No hay otras ocurrencias.
    if (ocurrencias.empty()) {
        cout << "No existe otra base '" << baseObjetivo << "' diferente a la ubicada en [" << i << " ," << j << "]." << endl;
        return;
    }

    Grafo& grafo = secuencia->getGrafo();
    double maxDistancia = -1;
    int rf = -1;
    int rc = -1;

    // Buscar la base remota que maximiza distancia en grafo.
    for (int k = 0; k < ocurrencias.size(); k++) {

        int f2 = ocurrencias[k].first;
        int c2 = ocurrencias[k].second;

        grafo.dijkstra(filaInicio, colInicio, f2, c2);
        double distancia = grafo.obtenerDistancia(f2, c2);

        if (distancia > maxDistancia) {
            maxDistancia = distancia;
            rf = f2;
            rc = c2;
        }
    }

    // Obtener ruta final hacia la base remota más lejana.
    grafo.dijkstra(filaInicio, colInicio, rf, rc);
    vector<pair<int,int>> ruta = grafo.obtenerRuta(filaInicio, colInicio, rf, rc);

    // Imprimir resultados.
    cout << "Para la secuencia " << descripcion << ", la base remota está ubicada en [" << rf << " ," << rc 
        << "], y la ruta entre la base en [" << i << " ," << j << "] y la base remota en [" << rf << " ," << rc << "] es: " << endl;

    // Imprimir la secuencia de bases en la ruta.
    for (int i = 0; i < ruta.size(); i++) {
        int rf = ruta[i].first;
        int rc = ruta[i].second;
        cout << matriz[rf][rc];

        if (i + 1 < ruta.size()) { 
            cout << " -> "; 
        }
    }

    cout << endl << "El costo total de la ruta es: " << maxDistancia << endl;
}


// Devuelve una referencia al objeto que pertenece al Sistema.
FASTA& Sistema::getFASTA() { return fasta; }
