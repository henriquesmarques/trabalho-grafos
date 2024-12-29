//
// Created by gomes on 25/12/2024.
//

#ifndef VERTICE_H
#define VERTICE_H
#include "Aresta.h"
#include "Coloracao.h"

class Aresta;

class Vertice {
public:
    Vertice(int _id);
    ~Vertice();
    void setPeso(int val);
    int getPeso();
    void setProx(Vertice* v);
    Vertice* getProx();
    int getId();
    void inserirAresta(Aresta* a);
    Aresta* getAresta(int i);
    int totalArestas();


    void setCorVisita(Coloracao _cor);
    Coloracao getVisitado();
    void removerAresta(Aresta* a);
    Aresta* getArestaPara(Vertice* v);

private:
    Aresta *listaAresta;
    bool visitado;
    int disc;
    int low;
    Coloracao cor;
    int id;
    int peso;
    Vertice* prox;
    Aresta** arestas; /// Vetor de ponteiros de Arestas
    int n; /// Total de arestas
    int tam; /// Tamanho do vetor
    void aumentarVetor();
};

#endif //VERTICE_H