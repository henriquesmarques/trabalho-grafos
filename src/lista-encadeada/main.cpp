#include <iostream>
#include "GrafoLista.h"

using namespace std;

int main() {

    GrafoLista g;
    g.carregaGrafo();

    cout << endl << endl;

    if (g.arestaPonderada())
        cout << "Arestas ponderadas." << endl;
    else
        cout << "Arestas nao ponderadas." << endl;

    cout << "Ordem do grafo: " << g.getOrdem() << endl;

    if (g.ehDirecionado())
        cout << "Eh direcionado." << endl;
    else
        cout << "Nao eh direcionado." << endl;

    if (g.ehConexo())
        cout << "Eh conexo." << endl;
    else
        cout << "Nao eh conexo." << endl;

    cout << "Eh " << g.nConexo() << "-conexo." << endl;

    if (g.ehArvore())
        cout << "Eh arvore." << endl;
    else
        cout << "Nao eh arvore." << endl;


    cout << endl << endl;

    if (g.verticePonderado())
        cout<< "Vertice Ponderada." << endl;
    else
        cout << "Nao eh vertice ponderada." << endl;

    cout<<"Grau do grafo: " << g.getGrau()<<endl;

    if (g.ehCompleto())
        cout << "Eh completo." << endl;
    else
        cout << "Nao eh completo." << endl;

    if (g.ehBipartido())
        cout << "Eh Bipartido." << endl;
    else
        cout << "Nao eh Bipartido." << endl;

    /*cout << endl << "FUNCAO ARTICULACAO" << endl;
    if (g.possuiArticulacao())
        cout << "Possui articulacao." << endl;
    else
        cout << "Nao possui articulacao." << endl;

    cout << endl << "FUNCAO PONTE" << endl;
    if (g.possuiPonte())
        cout<< "Possui Ponte." << endl;
    else
        cout << "Nao possui Ponte." << endl;*/

    return 0;
}
