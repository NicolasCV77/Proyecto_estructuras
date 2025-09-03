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
    } else {
        cout << "Hay " << secuencias.size() << " Cargadas en memoria" << endl;
        vector<Secuencia>::iterator it;
        for(it = secuencias.begin();it !=  secuencias.end(); it++){
            if(it->ContarNoExactas()>0){
                cout <<"Secuencia " << it->getDescripcion() << " contiene al menos " << it->ContarExactas() << " bases" << endl;
            }else{
                cout <<"Secuencia " << it->getDescripcion() << " contiene " << it->ContarExactas() << " bases" << endl;
            }
        }
    }
} 

void FASTA::histograma(string descripcion) {
    FASTA();
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

Secuencia FASTA::buscarSecuencia(string descripcion){
    vector<Secuencia> :: iterator itSec;
    for(itSec = secuencias.begin(); itSec != secuencias.end(); itSec++){
        if(itSec->getDescripcion() == descripcion){
            return *itSec;
        }
    }
    cout << "No se encontro la secuencia" << endl;
}

int FASTA::contarPosiblesBases(Secuencia secuencia){

    vector <vector<char>> :: iterator itComp;
    vector <char> :: iterator itCompComp;
    vector <char> :: iterator itBases;
    vector <char> :: iterator itEquivalentes;

    vector <char> bases = secuencia.getBases();
    vector <char> equivalentes;
    vector <char> distintas;

    for (itBases = bases.begin(); itBases != bases.end(); itBases++) {
        vector <char> equivalentes = getEquivalencias(*itBases);

        if(equivalentes.size()>1){
            for(itEquivalentes = equivalentes.begin() ; itEquivalentes != equivalentes.end(); itEquivalentes++){
                if(*itEquivalentes != *itBases){
                    distintas.push_back(*itEquivalentes);
                }
            }
        }else{
            distintas.push_back(*itBases);
        }
    }
    return distintas.size();
}

vector<char> FASTA::getEquivalencias(char base){
    vector <char> equivalencias;
    vector <vector<char>> :: iterator itComp;
    for(itComp = componentes.begin(); itComp != componentes.end(); itComp++){
        if(base==(*itComp)[0]){
            return *itComp;
        }
    }
}
vector<Secuencia>& FASTA::getSecuencias() {
    return secuencias;
}
vector<vector<char>>& FASTA::getComponentes(){
    return componentes;
}