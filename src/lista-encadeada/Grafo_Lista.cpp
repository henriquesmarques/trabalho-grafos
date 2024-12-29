#include "GrafoLista.h"
#include "Coloracao.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include <string>
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
    return true;
}
bool GrafoLista::ehBipartido() {
    /// eh bipartido se seus vértices puderem ser divididos em dois conjuntos disjuntos,
    /// de forma que não haja arestas entre vértices do mesmo conjunto
    if (ehCompleto())
        return false;
    for (int i=0; i<getOrdem(); i++)
        vertices[i]->setCorVisita(Coloracao::SEMCOR);

    for (int i = 0; i < getOrdem(); i++) {
        if (vertices[i]->getVisitado() == Coloracao::SEMCOR) {
            if (!auxEhBipartido(vertices[i],Coloracao::AZUL))
                return false;
        }
        return true;
    }
}
bool GrafoLista::auxEhBipartido(Vertice* v, Coloracao cor) {
        v->setCorVisita(cor);
        Coloracao corOposta = (cor == Coloracao::AZUL) ? Coloracao::VERDE : Coloracao::AZUL;
        Aresta* a = v->listaAresta;
        while (a != nullptr) {
            Vertice* adj = a->getFim();
            if (adj->getVisitado() == Coloracao::SEMCOR) {
                if (!auxEhBipartido(adj, corOposta))
                    return false;
            } else if (adj->getVisitado() != corOposta) {
                return false;
            } a = a->getProx();
        } return true;
}
bool GrafoLista::possuiArticulacao() {
    ///definição: se retira um vertice, aumenta o numero de componentes conexas;

    ///um grafo completo se retirado um vertice não aumenta o numero de componentes conexas
    if (ehCompleto())
        return false;
    ///calcula o numero de componentes conexas;
    int componentesConexas = nConexo();

    Vertice* v = raizVertice;
    ///laco para realizar a remoção de um no por vez no grafo
    for (int i=0; i<getOrdem(); i++) {
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
    int comp2 = nConexo(); ///contabiliza o numero de componentes apos a remocao
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
Vertice* GrafoLista::buscaVertice(int info){
    Vertice* p = raizVertice;
    while(p != nullptr){
        if( p->getId() == info)
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
    int componentesConexas = nConexo();
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
        int comp2 = nConexo();
        if (comp2 > comp)
            return true;
    }
    return false;
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