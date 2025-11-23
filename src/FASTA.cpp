#include "FASTA.h"

// Constructor FASTA.
FASTA::FASTA() {
    // Inicializamos las equivalencias de las bases.
    componentes = {
        {'A'},                         // A -> Adenina
        {'C'},                         // C -> Citosina
        {'G'},                         // G -> Guanina
        {'T'},                         // T -> Timina
        {'U'},                         // U -> Uracilo
        {'R','A', 'G'},                // R -> A o G
        {'Y','C', 'T', 'U'},           // Y -> C, T o U
        {'K','G', 'T', 'U'},           // K -> G, T o U
        {'M','A', 'C'},                // M -> A o C
        {'S','C', 'G'},                // S -> C o G
        {'W','A', 'T', 'U'},           // W -> A, T o U
        {'B','C', 'G', 'T', 'U'},      // B -> C, G, T o U
        {'D','A', 'G', 'T', 'U'},      // D -> A, G, T o U
        {'H','A', 'C', 'T', 'U'},      // H -> A, C, T o U
        {'V','A', 'C', 'G'},           // V -> A, C o G
        {'N','A', 'C', 'G', 'T', 'U'}, // N -> A, C, G, T o U
        {'X'},                         // X -> Máscara (ninguna base real)
        {'-'}                          // - -> Espacio indeterminado (ninguna base real)
    };

    // Límite bases exactas.
    limiteExactas = 5;
}

// Agrega una secuencia al conjunto de secuencias cargadas.
void FASTA::agregarSecuencia(const Secuencia& secuencia) {
    secuencias.push_back(secuencia);
}

// Retorna la cantidad total de secuencias cargadas.
int FASTA::totalSecuencias() { 
    return secuencias.size();
}

// Lista todas las secuencias almacenadas y su información básica.
void FASTA::listarSecuencias() {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }

    cout << "Hay " << secuencias.size() << " cargadas en memoria." << endl;

    vector<Secuencia>::iterator itSec;
    for (itSec = secuencias.begin(); itSec != secuencias.end(); itSec++) {
        // Contar posibles bases distintas.
        int numBases = contarPosiblesBases(*itSec);

        // Verificar si contiene alguna base no exacta.
        bool tieneNoExactas = false;
        vector<char> bases = itSec->getBases();

        vector<char>::iterator itBase;
        for (itBase = bases.begin(); itBase != bases.end(); itBase++) {
            vector<char> eq = getEquivalencias(*itBase);

            if (eq.size() > 1) { 
                tieneNoExactas = true;
                break;
            }
        }

        if (tieneNoExactas) {
            cout << "Secuencia " << itSec->getDescripcion()<< " contiene al menos " << numBases << " bases." << endl;
        } else {
            cout << "Secuencia " << itSec->getDescripcion()<< " contiene " << numBases << " bases." << endl;
        }

    }
}

// Genera un histograma de conteo de bases para una secuencia dada por su descripción.
void FASTA::histograma(string descripcion) {
    vector<Secuencia>:: iterator itSec;
    for (itSec = secuencias.begin(); itSec != secuencias.end(); itSec++) {
        if (itSec->getDescripcion()== descripcion) {
            break;
        }
    }

    if (itSec == secuencias.end()) {
        cout << "Secuencia invalida"<< endl;
        return;
    }

    vector<vector<char>>::iterator it;
    int numBase;

    // Recorremos todas las bases posibles y contamos su frecuencia.
    for (it = componentes.begin(); it != componentes.end(); it++) {
        numBase = itSec->contarBase((*it)[0]);
        cout << (*it)[0] << ": " << numBase << endl;
    } 
}

// Cuenta cuántas veces aparece una subsecuencia en todas las secuencias cargadas.
void FASTA::contarSubsecuencia(string sub) {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas" << endl;
        return;
    }

    vector<char> subSecuencia(sub.begin(), sub.end());
    int siSubsecuencia = 0;

    vector<Secuencia>::iterator it;
    for (it = secuencias.begin(); it != secuencias.end(); it++) {
        vector<char> bases = it->getBases();
        int n = bases.size();
        int m = subSecuencia.size();

        // Recorremos la secuencia buscando coincidencias con la subsecuencia.
        for (int i = 0; i <= n - m; i++) {
            bool encontrada = subEncontrada(bases, subSecuencia, i);
            if (encontrada) {
                siSubsecuencia++;
            }
        }
    }

    if (siSubsecuencia > 0) {
        cout << "La subsecuencia dada se repite "<< siSubsecuencia<< " veces dentro de las secuencias cargadas en memoria." << endl;
    } else {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria." << endl;
    }
}

// Enmascara las apariciones de una subsecuencia dentro de las secuencias cargadas.
void FASTA::enmascararSubsecuencia(string sub) {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas" << endl;
        return;
    }

    vector<char> subSecuencia(sub.begin(), sub.end());
    int enmascaradas = 0;

    for (vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); it++) {
        // Recorremos cada posible posición.
        for (int i = 0; i <= it->getBases().size() - subSecuencia.size(); i++) {
            if (subEncontrada(it->getBases(), subSecuencia, i)) {
                int inicio = i;
                int fin = i + subSecuencia.size() - 1;
                enmascaradas += it->enmascarar(inicio, fin);
            }
        }
    }

    if (enmascaradas > 0) {
        cout << "La subsecuencia dada se enmascaro " << enmascaradas << " veces dentro de las secuencias cargadas en memoria." << endl;
    } else {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria." << endl;
    }
}

// Busca una secuencia por su descripción y retorna un puntero a la misma.
Secuencia* FASTA::buscarSecuencia(const string& descripcion) {
    vector<Secuencia>::iterator it;
    for (it = secuencias.begin(); it != secuencias.end(); it++) {
        if (it->getDescripcion() == descripcion) {
            return &(*it);
        }
    }
    return nullptr;
}

// Cuenta cuántas bases distintas posibles hay en una secuencia.
int FASTA::contarPosiblesBases(Secuencia secuencia) {
    vector<char> bases = secuencia.getBases();
    vector<char>::iterator itBases;

    vector<char> contadas;
    vector<char>::iterator itCont;
    int contador = 0;

    for (itBases = bases.begin(); itBases != bases.end(); itBases++) {
        if (*itBases == '-' || *itBases == 'X') {
            continue;
        }

        vector<char> equivalentes = getEquivalencias(*itBases);
        vector<char>::iterator itEq;

        if (equivalentes.size() == 1 && equivalentes[0] == *itBases) {
            // Caso de base exacta.
            bool yaEsta = false;
            for (itCont = contadas.begin(); itCont != contadas.end(); itCont++) {
                if (*itCont == *itBases) {
                    yaEsta = true;
                    break;
                }
            }

            if (!yaEsta) {
                contadas.push_back(*itBases);
                contador++;
            }
        } else {
            // Caso de base no exacta.
            bool algunoYaContado = false;

            for (itEq = equivalentes.begin() + 1; itEq != equivalentes.end(); itEq++) {
                for (itCont = contadas.begin(); itCont != contadas.end(); itCont++) {
                    if (*itCont == *itEq) {
                        algunoYaContado = true;
                        break;
                    }
                }
                
                if (algunoYaContado) {
                    break;
                }
            }

            if (!algunoYaContado) {
                if (equivalentes.size() > 1) {
                    contadas.push_back(*(equivalentes.begin() + 1));
                    contador++;
                }
            }
        }
    }

    return contador;
}

// Verifica si una subsecuencia está presente en una posición dada de la secuencia.
bool FASTA::subEncontrada(vector<char> bases, vector<char> subSecuencia, int inicio) {
    vector<char>::iterator itSubsecuencia;
    int contador = 0; 

    for (itSubsecuencia = subSecuencia.begin(); itSubsecuencia != subSecuencia.end(); itSubsecuencia++) {
        char baseSecuencia = bases[inicio + contador];
        char baseSub = *itSubsecuencia;
        contador++;

        vector<char> grupoSecuencia = getEquivalencias(baseSecuencia);
        vector<char>::iterator itEq;

        bool pertenece = false;
        for (itEq = grupoSecuencia.begin(); itEq != grupoSecuencia.end(); itEq++) {
            if (*itEq == baseSub) {
                pertenece = true;
                break;
            }
        }

        if (!pertenece) {
            return false;
        }
    }

    return true;
}

// Retorna el conjunto de equivalencias para una base dada.
vector<char> FASTA::getEquivalencias(char base) {
    vector <char> equivalencias;
    
    vector <vector<char>> :: iterator itComp;
    for (itComp = componentes.begin(); itComp != componentes.end(); itComp++) {
        if (base == (*itComp)[0]) {
            return *itComp;
        }
    }
    return {base};
}

// Retorna una referencia al conjunto de secuencias cargadas.
vector<Secuencia>& FASTA::getSecuencias() {
    return secuencias;
}

// Retorna una referencia a la lista de componentes equivalentes de bases.
vector<vector<char>>& FASTA::getComponentes() {
    return componentes;
}
