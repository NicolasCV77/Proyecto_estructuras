#include "arbolHuffman.h"
#include "queue"

using namespace std;

arbolHuffman::arbolHuffman() {
    this->raiz = NULL;
}


arbolHuffman::~arbolHuffman() {
    if (this->raiz != NULL) {
        delete this->raiz;
        this->raiz = NULL;
    }
}


bool arbolHuffman::esVacio() {
    return this->raiz == NULL;
}


nodoHuffman arbolHuffman::datoRaiz() {
    return (this->raiz)->obtenerDato();
}


int arbolHuffman::altura() {
    if (this->esVacio()) {
        return -1;
    } else {
        return (this->raiz)->altura();
    }
}


int arbolHuffman::tamano() {
    if (this->esVacio()) {
        return 0;
    } else {
        return (this->raiz)->tamano();
    }
}


bool arbolHuffman::insertar(int val) {

    if (this->esVacio()) {
        this->raiz = new nodoHuffman(val);
        return true;
    }

    nodoHuffman *actual = this->raiz;
    while (true) {
        if (val < actual->obtenerDato()) {
            if (actual->obtenerHijoIzq() == NULL) {
                actual->fijarHijoIzq(new nodoHuffman(val));
                return true;
            }
            actual = actual->obtenerHijoIzq();
        } 
        else if (val > actual->obtenerDato()) {
            if (actual->obtenerHijoDer() == NULL) {
                actual->fijarHijoDer(new nodoHuffman(val));
                return true;
            }
            actual = actual->obtenerHijoDer();
        } 
        else {
            return false; 
        }
    }
}


bool arbolHuffman::eliminar(int val) {
    if (this->raiz == NULL) {
        return false;
    }

    nodoHuffman *actual = this->raiz;
    nodoHuffman *padre = NULL;

    while (actual != NULL && actual->obtenerDato() != val) {
        padre = actual;
        if (val < actual->obtenerDato()) {
            actual = actual->obtenerHijoIzq();
        } else {
            actual = actual->obtenerHijoDer();
        }
    }

    if (actual == NULL) {
        return false;
    }

    if (actual->obtenerHijoIzq() == NULL && actual->obtenerHijoDer() == NULL) {
        if (padre == NULL) {
            this->raiz = NULL;
        } else if (padre->obtenerHijoIzq() == actual) {
            padre->fijarHijoIzq(NULL);
        } else {
            padre->fijarHijoDer(NULL);
        }
        actual->fijarHijoIzq(NULL);
        actual->fijarHijoDer(NULL);
        delete actual;
    } else if (actual->obtenerHijoIzq() == NULL || actual->obtenerHijoDer() == NULL) {
        nodoHuffman* hijo = NULL;

        if (actual->obtenerHijoIzq() != NULL) {
            hijo = actual->obtenerHijoIzq();
        } else {
            hijo = actual->obtenerHijoDer();
        }

        if (padre == NULL) {
            this->raiz = hijo;
        } else if (padre->obtenerHijoIzq() == actual) {
            padre->fijarHijoIzq(hijo);
        } else {
            padre->fijarHijoDer(hijo);
        }

        actual->fijarHijoIzq(NULL);
        actual->fijarHijoDer(NULL);
        delete actual;
    } else {
        nodoHuffman* reemplazo = actual->obtenerHijoIzq();
        nodoHuffman* padreReemplazo = actual;

        while (reemplazo->obtenerHijoDer() != NULL) {
            padreReemplazo = reemplazo;
            reemplazo = reemplazo->obtenerHijoDer();
        }

        actual->fijarDato(reemplazo->obtenerDato());

        if (padreReemplazo->obtenerHijoIzq() == reemplazo) {
            padreReemplazo->fijarHijoIzq(reemplazo->obtenerHijoIzq());
        } else {
            padreReemplazo->fijarHijoDer(reemplazo->obtenerHijoIzq());
        }
        reemplazo->fijarHijoIzq(NULL);
        reemplazo->fijarHijoDer(NULL);
        delete reemplazo;
    }

    return true;
}


bool arbolHuffman::buscar (int val) {
    nodoHuffman *nodo = this->raiz;
    bool encontrado = false;

    while (nodo != NULL && !encontrado){
        if(val < nodo->obtenerDato()){
            nodo = nodo->obtenerHijoIzq();
        } else if (val > nodo ->obtenerDato()){
            nodo = nodo->obtenerHijoDer();
        } else {
            encontrado = true;
        }
    }
    return encontrado;
}


void arbolHuffman::preOrden () {
    if(!this->esVacio()){
        (this->raiz)->preOrden();
    }
}


void arbolHuffman::postOrden () {
    if(!this->esVacio()){
        (this->raiz)->posOrden();
    }
}


void arbolHuffman::inOrden (){
    if(!this->esVacio()){
        (this->raiz)->inOrden();
    }
}


void arbolHuffman::nivelOrden(){
    if (!this->esVacio()){
        queue <nodoHuffman*> q;
        q.push(this->raiz);

        nodoHuffman* nodo;

        while(!q.empty()){
            nodo = q.front();
            q.pop();
            cout << nodo->obtenerDato() << " ";
            if (nodo->obtenerHijoIzq() != NULL) {
                q.push(nodo->obtenerHijoIzq());
            }
            if (nodo->obtenerHijoDer() != NULL) {
                q.push(nodo->obtenerHijoDer());
            }
        }
    }
}
