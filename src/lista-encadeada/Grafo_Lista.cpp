#include "GrafoLista.h"
#include "Vertice.h"
#include <iostream>
#include <fstream>

using namespace std;

bool GrafoLista::vertice_ponderado() {
    ///verifica se o vertice possui peso
    Vertice *v = raizVertice;
    while (v != nullptr) {
        if (v->getPeso() != 1) {
            return true;
        }
        v = v->getProx();
    }
    return false;
}

int GrafoLista::get_grau() {
    Vertice *v = raizVertice;
    int grauGrafo =0;
    int grau = 0;
    while (v != nullptr) {
        grau = v->totalArestas();
        if (grau > grauGrafo) {
            grauGrafo = grau;
        }
        v = v->getProx();
    }
    return grauGrafo;
}

bool GrafoLista::eh_completo() {
    ///verifica se todos os nos possuem mesmo grau
    int grau = 0, grauGrafo = 0, aux = 0;
    Vertice *v = raizVertice;

    while (v != nullptr) {
        aux++;
        grau = v->totalArestas();
        if (aux == 1)
            grauGrafo = grau;
        if (grau != grauGrafo) {
            return false;
        }
        v = v->getProx();
    }
    if (!eh_direcionado()) {
        if (grauGrafo == get_ordem()-1)
            return true;
    } else if (grauGrafo == 2*get_ordem()-2) {
        return true;
    }
    return false;
}

bool GrafoLista::eh_bipartido() {
    /// eh bipartido se seus vértices puderem ser divididos em dois conjuntos disjuntos,
    /// de forma que não haja arestas entre vértices do mesmo conjunto
    if (eh_completo())
        return false;
    int n = get_ordem();
    int *cor = new int[n];
    ///Inicializa todos como sem cor = -1
    for (int i=0;i<n;i++)
        cor[i]=-1;
    for (int i=0; i<n; i++) {
        if (cor[i]==-1) { ///vertice nãoo visitado
            if (!auxEhBipartido(i, 0, cor)) {
                delete [] cor;
                return false;
            }
        }
    }
    delete [] cor;
    return true;
}

bool GrafoLista::auxEhBipartido(int i, int c, int *cor) {
    cor[i]=c; ///colore o vertice U com a cor c
    for ( Vertice* vizinho = buscaVertice(i); vizinho!= nullptr; vizinho=vizinho->getProx()) {
        int id = vizinho->getId();
        if (cor[id]==-1) {
            ///se o vertice não foi visitado
            if (!auxEhBipartido(id, 1-c, cor)) ///se não for possivel colorir com a cor oposta
                return false;
        }
        else if (cor[id] == c) ///se vizinhos possuem a mesma cor
                return false;
    }
    return true;
}

bool GrafoLista::possui_articulacao() {
    ///definição: se retira um vertice, aumenta o numero de componentes conexas;
    if (eh_completo()) ///um grafo completo se retirado um vertice não aumenta o numero de componentes conexas
        return false;
    ///calcula o numero de componentes conexas;
    int componentesConexas = n_conexo();
    ///laco para realizar a remoção de um no por vez no grafo
    GrafoLista* grafo = copiarGrafo();
    for (Vertice* v = raizVertice; v != nullptr; v = v->getProx()) {
        int tam = v->totalArestas();
        Aresta** arestas = v->copiarVetorArestas();

        ///retira um vertice
        grafo->removerVertice(grafo->buscaVertice(v->getId()));

        ///verifica se o numero de componentes aumentou
        if (grafo->n_conexo() > componentesConexas) {
            delete grafo;
            delete [] arestas;
            return true;
        }

        ///reinsere o vertice no grafo
        grafo->inserirVertice(v->getId(), v->getPeso());
        for (int i = 0; i < tam; i++)
            grafo->inserirAresta(arestas[i]->getInicio(), arestas[i]->getFim(), arestas[i]->getPeso());

        ///proximo vertice
        delete [] arestas;
    }
    delete grafo;
    return false;
}

bool GrafoLista::possui_ponte() {
    ///definição: se retira uma aresta, aumenta o numero de componentes conexas;
    ///um grafo completo se retirado um vertice não aumenta o numero de componentes conexas
    if (eh_completo())
        return false;
    ///calcula o numero de componentes conexas;
    int componentesConexas = n_conexo();
    ///laco para realizar a remoção de um no por vez no grafo
    GrafoLista* grafo = copiarGrafo();
    for (Vertice* v = raizVertice; v != nullptr; v = v->getProx()) {
            int tam = v->totalArestas();
            for (int i = 0; i < tam; i++) {
                Aresta* a = v->getAresta(i);
                Vertice* destino = a->getFim();
                ///remove a aresta
                v->removerAresta(a);
                destino->removerAresta(destino->getArestaPara(v));
                int comp2 = n_conexo();
                if (comp2 > componentesConexas)
                    return true;
            }
    }
    delete grafo;
    return false;
}

void GrafoLista::removerVertice(Vertice* v) {
    /// Remover arestas do vetor de arestas do vértice
    for (int i = v->totalArestas()-1; i >= 0; i--) {
        removerAresta(v->getAresta(i));
    }

    /// Remover vértice da lista de vértices do Grafo
    if (raizVertice == v) {
        raizVertice = v->getProx();
    } else {
        Vertice* ant = raizVertice;
        while (ant->getProx() != v) {
            ant = ant->getProx();
        }
        ant->setProx(v->getProx());
    }
    delete v;
}

void GrafoLista::removerAresta(Aresta* a) {
    /// Remove aresta dos Vetores
    Vertice* v = a->getInicio();
    v->removerAresta(a);
    v = a->getFim();
    v->removerAresta(a);

    /// Remove aresta da lista de arestas do Grafo
    if (raizAresta == a) {
        raizAresta = a->getProx();
    } else {
        Aresta* ant = raizAresta;
        while (ant->getProx() != a) {
            ant = ant->getProx();
        }
        ant->setProx(a->getProx());
    }
    delete a;
}

Aresta* GrafoLista::buscaAresta(int vert1, int vert2){
    Vertice* p = buscaVertice(vert1);
    Aresta* aux = p->getAresta(vert2);
    if(aux != nullptr){
        while(aux != nullptr){
            if(aux->getPeso() == vert2)
                return aux;
            aux = aux->getProx();
        }
    }
    return aux;
}

Vertice* GrafoLista::buscaVertice(int id){
    Vertice* p = raizVertice;
    while(p != nullptr){
        if( p->getId() == id)
            return p;
        p = p->getProx();
    }
    return p;
}

GrafoLista* GrafoLista::copiarGrafo() {
    GrafoLista* grafo = new GrafoLista();
    ///Copia os vertices do grafo;
    Vertice* v = raizVertice;
    while (v != nullptr) {
        grafo->inserirVertice(v->getId(), v->getPeso()); ///chama a função para inserir os vertices
        v = v->getProx(); ///atualiza para o proximo vertice
    }
    //imprimirVertices();
    ///Copia as arestas do grafo;
    Aresta* a = raizAresta;

    while (a != nullptr) {///insere cada aresta
        grafo->inserirAresta(grafo->buscaVertice(a->getInicio()->getId()), grafo->buscaVertice(a->getFim()->getId()), a->getPeso());
        a = a->getProx();
    }
    return grafo;
}