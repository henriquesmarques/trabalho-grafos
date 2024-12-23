#include <iostream>
#include "GrafoLista.h"

using namespace std;

int main() {

    GrafoLista g;
    g.carregaGrafo();

    if (g.arestaPonderada())
        cout << "Arestas ponderadas." << endl;
    else
        cout << "Arestas nao ponderadas." << endl;

    cout << "Ordem do grafo: " << g.getOrdem();

    return 0;
}