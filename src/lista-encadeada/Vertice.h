#ifndef VERTICE_H
#define VERTICE_H

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

    void setAresta(Aresta* a);
    Aresta* getAresta();
private:
    int id;
    int peso;
    Vertice* prox;
    Aresta* aresta;
};

#endif //VERTICE_H
