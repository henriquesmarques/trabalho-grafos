#include "GrafoLista.h"
#include "Vertice.h"
#include <iostream>
#include <fstream>

using namespace std;

bool GrafoLista::verticePonderado() {
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
int GrafoLista::getGrau() {
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
bool GrafoLista::ehCompleto() {
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

    if (grauGrafo == get_ordem()-1)
        return true;
    return false;
}
bool GrafoLista::ehBipartido() {
    /// eh bipartido se seus vértices puderem ser divididos em dois conjuntos disjuntos,
    /// de forma que não haja arestas entre vértices do mesmo conjunto
    if (ehCompleto())
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

bool GrafoLista::possuiArticulacao() {
    ///definição: se retira um vertice, aumenta o numero de componentes conexas;
    ///um grafo completo se retirado um vertice não aumenta o numero de componentes conexas
    if (ehCompleto())
        return false;
    ///calcula o numero de componentes conexas;
    int componentesConexas = n_conexo();
    Vertice* v = raizVertice;
    ///laco para realizar a remoção de um no por vez no grafo
    for (int i=0; i<get_ordem(); i++) {
        GrafoLista* grafo = copiarGrafo(); ///a cada iteração faz a copia grafo
        if (grafo->auxArticulacao(v, componentesConexas))///chama a funcao auxiliar para o vertice do grafo copiado
        {
            delete grafo;
            return true;
        }
        delete grafo;
        v = v->getProx(); ///atualização para o proximo vertice
    }
    return false;
}
bool GrafoLista::auxArticulacao(Vertice *v, int comp) {
    ///retira um vertice e verifica o numero de componentes conexas
    retiraVertice(v->getId()); ///chama a função que remove o vertice
    int comp2 = n_conexo(); ///contabiliza o numero de componentes apos a remocao
    return comp2 > comp;
}

void GrafoLista::retiraVertice(int id){
        Vertice* p = raizVertice;
        Vertice* aux = nullptr;
        // Remover arestas que têm 'id' como destino
        while (p != nullptr) {
            for (int i =0; i<p->totalArestas(); i++) {
                Aresta *a = p->getAresta(i);
                while (a!= nullptr) {
                    if (a->getFim()->getId() == id) {
                        p->removerAresta(a);
                        i--;
                    }
                }
            }
            p = p->getProx();
        } // Resetar o ponteiro 'p' para procurar o vértice a ser removido
        p = raizVertice;
        while (p != nullptr && p->getId() != id) {
            aux = p;
            p = p->getProx();
        } // Se o vértice foi encontrado
        if (p != nullptr && p->getId() == id) {
            if (aux == nullptr) {
                // Caso o vértice a ser removido seja o primeiro vértice (raizVertice)
                raizVertice = p->getProx(); }
            else{ // Caso o vértice a ser removido não seja o primeiro
                aux->setProx(p->getProx()); }
            delete p;
            cout << "No " << id << " removido com sucesso.\n"; }
        else {
            cout << "No " << id << " não encontrado.\n";
        }
}
Aresta* GrafoLista::buscaAresta(int vert1, int vert2){
    Vertice* p = buscaVertice(vert1);
    Aresta* aux = p->getAresta(vert2);
    if(p != nullptr && aux != nullptr){
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



bool GrafoLista::possuiPonte() {
    ///definição: se retira uma aresta, aumenta o numero de componentes conexas;
    ///um grafo completo se retirado um vertice não aumenta o numero de componentes conexas
    if (ehCompleto())
        return false;
    ///calcula o numero de componentes conexas;
    int componentesConexas = n_conexo();
    ///laco para realizar a remoção de um no por vez no grafo
    for (Vertice* v = raizVertice; v!= nullptr; v = v->getProx()) {
        GrafoLista* grafo = copiarGrafo(); ///a cada iteração faz a copia grafo
        if (grafo->auxPonte(grafo->buscaVertice(v->getId()), componentesConexas))///chama a funcao auxiliar para o vertice do grafo copiado
        {
            delete grafo;
            return true;
        }
        delete grafo;
    }
    return false;
}
bool GrafoLista::auxPonte(Vertice *v, int comp){
    for (int i=0; i<v->totalArestas(); i++) {
        Aresta* a = v->getAresta(i);
        Vertice* destino = a->getFim();
        ///remove a aresta
        v->removerAresta(a);
        destino->removerAresta(destino->getArestaPara(v));
        int comp2 = n_conexo();
        if (comp2 > comp)
            return true;
    }
    return false;
}
void GrafoLista::removerAresta(Aresta* a) {
        Vertice* v = a->getInicio();
        v->removerAresta(a);
        if (direcionado != true) {
            v = a->getFim();
            v->removerAresta(a);
        }

        if (raizAresta == a) {
            raizAresta = a->getProx();
            delete a;
        } else {
            Aresta* ant = raizAresta;
            while (ant->getProx() != a) {
                ant = ant->getProx();
            }
            ant->setProx(a->getProx());
            delete a;
        }
}

GrafoLista* GrafoLista::copiarGrafo() {
    GrafoLista* grafo = new GrafoLista();
    ///Copia os vertices do grafo;
    Vertice* v = raizVertice;
    while (v != nullptr) {
        grafo->inserirVertice(v->getId(), v->getPeso()); ///chama a função para inserir os vertices
        v = v->getProx(); ///atualiza para o proximo vertice
    }
    imprimirVertices();
    ///Copia as arestas do grafo;
    Aresta* a = raizAresta;
    v = raizVertice; ///atualiza v para o inicio
    while (v!= nullptr) {
        while (a != nullptr) {
            ///insere cada aresta
            grafo->inserirAresta(a->getInicio(), a->getFim(), a->getPeso());
            a = a->getProx();
        }
        v = v->getProx();
    }
    return grafo;
}