#include "FASTA.h"

FASTA::FASTA() {
    componentes = {
        'A', 'C', 'G', 'T', 'U', 'R', 'Y',
        'K', 'M', 'S', 'W', 'B', 'D', 'H',
        'V', 'N', 'X', '-'
    };
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
    } else {
        cout << "Hay " << secuencias.size() << " Cargadas en memoria" << endl;

        vector<Secuencia>::iterator it;
        vector<char>:: reverse_iterator itComponentes;
        int contiene, numeroBases;
            
        for (it = secuencias.begin(); it != secuencias.end(); it++) {
            int completo = it->contarBase('-');

            numeroBases = 0;
            for (itComponentes = componentes.rbegin(); itComponentes != componentes.rend(); itComponentes++) {
                contiene = it->contarBase(*itComponentes);
                numeroBases++;
            }

            if (completo == 0) {
                cout << "Secuencia" << it->getDescripcion() << "contiene " << numeroBases << "bases" << endl;
            } else {
                cout << "Secuencia" << it->getDescripcion() << "contiene al menos " << numeroBases << " bases" << endl;
            }
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

    vector<char>::iterator it;
    int numBase;

    for (it = componentes.begin(); it != componentes.end(); it++) {
        numBase = itSec->contarBase(*it);
        if (numBase!=0) {
            cout << *it << ": " << numBase << endl;
        }
    }
}

void FASTA::contarSubsecuencia(string sub) {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas" << endl;
        exit(0);
    }

    vector<Secuencia>::iterator it;
    int siSubsecuencia = 0;

    for (it = secuencias.begin(); it != secuencias.end(); it++) {
        siSubsecuencia+=it->esSubsecuencia(sub);
    }

    if(siSubsecuencia > 0) {
        cout << "La subsecuencia dada se repite " << siSubsecuencia << " veces dentro de las secuencias cargadas en memoria." << endl;
    } else {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria." << endl;
    }
} 

void FASTA::enmascararSubsecuencia(string sub) {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas" << endl;
        exit(0);
    }

    vector<Secuencia>::iterator it;
    int enmascaradas = 0;

    for (it = secuencias.begin(); it != secuencias.end(); it++) {
        enmascaradas+=it->enmascarar(sub);
    }

    if (enmascaradas > 0) {
        cout << "La subsecuencia dada se repite " << enmascaradas << " veces dentro de las secuencias cargadas en memoria." << endl;
    } else {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria." << endl;
    }
}

vector<Secuencia> FASTA::getSecuencias() {
    vector<Secuencia> n;
    return n;
}