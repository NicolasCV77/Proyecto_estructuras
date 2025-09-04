#include "FASTA.h"

FASTA::FASTA() {
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
        {'-'}                          // - -> Espacio identerminado (ninguna base real)
    };

    limiteExactas = 5;
}

void FASTA::agregarSecuencia(const Secuencia& secuencia) {
    secuencias.push_back(secuencia);
}

int FASTA::totalSecuencias(){ 
    return secuencias.size();
}

void FASTA::listarSecuencias() {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria" << endl;
        return;
    }

    cout << "Hay " << secuencias.size() << " cargadas en memoria" << endl;

    vector<Secuencia>::iterator itSec;
    for (itSec = secuencias.begin(); itSec != secuencias.end(); itSec++) {
        // contar posibles bases distintas
        int numBases = contarPosiblesBases(*itSec);

        // verificar si contiene alguna base NO exacta
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
            cout << "Secuencia " << itSec->getDescripcion()<< " contiene AL MENOS " << numBases << " bases." << endl;
        } else {
            cout << "Secuencia " << itSec->getDescripcion()<< " contiene " << numBases << " bases." << endl;
        }

    }
}


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

    for (it = componentes.begin(); it != componentes.end(); it++) {
        numBase = itSec->contarBase((*it)[0]);
        cout << (*it)[0] << ": " << numBase << endl;
        
    }
}

void FASTA::contarSubsecuencia(string sub) {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas" << endl;
        return; // mejor return en vez de exit(0)
    }

    vector<char> subSecuencia(sub.begin(), sub.end()); // convertir string a vector<char>
    int siSubsecuencia = 0;

    // Recorremos cada secuencia cargada
    vector<Secuencia>::iterator it;
    for (it = secuencias.begin(); it != secuencias.end(); it++) {
        vector<char> bases = it->getBases();
        int n = bases.size();
        int m = subSecuencia.size();

        // revisar todas las posiciones posibles dentro de la secuencia
        for (int i = 0; i <= n - m; i++) {
            if (subEncontrada(bases, subSecuencia, i)) {
                siSubsecuencia++;
            }
        }
    }

    if (siSubsecuencia > 0) {
        cout << "La subsecuencia dada se repite " << siSubsecuencia<< " veces dentro de las secuencias cargadas en memoria." << endl;
    } else {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria." << endl;
    }
}
 

void FASTA::enmascararSubsecuencia(string sub) {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas" << endl;
        return;
    }

    vector<char> subSecuencia(sub.begin(), sub.end());
    int enmascaradas = 0;

    for (auto& sec : secuencias) {
        // Recorremos cada posible posición
        for (int i = 0; i <= sec.getBases().size() - subSecuencia.size(); i++) {
            if (subEncontrada(sec.getBases(), subSecuencia, i)) {
                int inicio = i;
                int fin = i + subSecuencia.size() - 1;
                enmascaradas += sec.enmascarar(inicio, fin);
            }
        }
    }

    if (enmascaradas > 0) {
        cout << "La subsecuencia dada se enmascaró " 
             << enmascaradas << " veces dentro de las secuencias cargadas en memoria." << endl;
    } else {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria." << endl;
    }
}


Secuencia FASTA::buscarSecuencia(string descripcion){
    vector<Secuencia> :: iterator itSec;
    for(itSec = secuencias.begin(); itSec != secuencias.end(); itSec++){
        if(itSec->getDescripcion() == descripcion){
            return *itSec;
        }
    }
    cout << "No se encontro la secuencia" << endl;
    return Secuencia("",{},0);
}

int FASTA::contarPosiblesBases(Secuencia secuencia) {
    vector<char> bases = secuencia.getBases();
    vector<char>::iterator itBases;

    vector<char> contadas; // aquí guardamos las bases exactas ya contadas
    vector<char>::iterator itCont;
    int contador = 0;

    for (itBases = bases.begin(); itBases != bases.end(); itBases++) {
        // Ignorar '-' y 'X'
        if (*itBases == '-' || *itBases == 'X') {
            continue;
        }

        vector<char> equivalentes = getEquivalencias(*itBases);
        vector<char>::iterator itEq;

        if (equivalentes.size() == 1 && equivalentes[0] == *itBases) {
            // Caso base exacta
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
            // Caso base NO exacta (R, Y, K, etc.)
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
                    // tomamos un representante (el primero exacto de la lista)
                    contadas.push_back(*(equivalentes.begin() + 1));
                    contador++;
                }
            }
        }
    }

    return contador;
}







bool FASTA::subEncontrada(vector<char> bases, vector<char> subSecuencia, int inicio) {
    vector<char>::iterator itSubsecuencia;
    vector<char>::iterator itEq;

    int contador = 0;
    for (itSubsecuencia = subSecuencia.begin(); itSubsecuencia != subSecuencia.end(); itSubsecuencia++) {
        char baseSecuencia = bases[inicio + contador];
        char basePatron = *itSubsecuencia;
        contador++;

        // Obtener las equivalencias de la base en la SECUENCIA (NO del patrón)
        vector<char> grupoSecuencia = getEquivalencias(baseSecuencia);

        // Verificar si el patrón pertenece al grupo de la secuencia
        bool pertenece = false;
        for (itEq = grupoSecuencia.begin(); itEq != grupoSecuencia.end(); itEq++) {
            if (*itEq == basePatron) {
                pertenece = true;
                break;
            }
        }

        if (!pertenece) {
            return false; // si no coincide en esta posición, no hay match
        }
    }

    return true; // todas las posiciones coincidieron
}



vector<char> FASTA::getEquivalencias(char base){
    vector <char> equivalencias;
    vector <vector<char>> :: iterator itComp;
    for(itComp = componentes.begin(); itComp != componentes.end(); itComp++){
        if(base==(*itComp)[0]){
            return *itComp;
        }
    }
    return {base};
}
vector<Secuencia>& FASTA::getSecuencias() {
    return secuencias;
}
vector<vector<char>>& FASTA::getComponentes(){
    return componentes;
}