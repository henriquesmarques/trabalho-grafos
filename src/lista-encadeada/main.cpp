#include <cassert>
#include <iostream>
#include "GrafoLista.h"

using namespace std;

void testarPossuiArticulacao() {
    // Teste 1: Grafo completo (não deve ter articulação)
    GrafoLista grafoCompleto;
    grafoCompleto.inserirVertice(1, 1);
    grafoCompleto.inserirVertice(2, 1);
    grafoCompleto.inserirVertice(3, 1);
    grafoCompleto.inserirAresta(grafoCompleto.buscaVertice(1), grafoCompleto.buscaVertice(2), 1);
    grafoCompleto.inserirAresta(grafoCompleto.buscaVertice(1), grafoCompleto.buscaVertice(3), 1);
    grafoCompleto.inserirAresta(grafoCompleto.buscaVertice(2), grafoCompleto.buscaVertice(3), 1);
    assert(grafoCompleto.possui_articulacao() == false);

    // Teste 2: Grafo com articulação
    GrafoLista grafoComArticulacao;
    grafoComArticulacao.inserirVertice(1, 1);
    grafoComArticulacao.inserirVertice(2, 1);
    grafoComArticulacao.inserirVertice(3, 1);
    grafoComArticulacao.inserirVertice(4, 1);
    grafoComArticulacao.inserirAresta(grafoComArticulacao.buscaVertice(1), grafoComArticulacao.buscaVertice(2), 1);
    grafoComArticulacao.inserirAresta(grafoComArticulacao.buscaVertice(2), grafoComArticulacao.buscaVertice(3), 1);
    grafoComArticulacao.inserirAresta(grafoComArticulacao.buscaVertice(3), grafoComArticulacao.buscaVertice(4), 1);
    assert(grafoComArticulacao.possui_articulacao() == true);

    // Teste 3: Grafo sem articulação
    GrafoLista grafoSemArticulacao;
    grafoSemArticulacao.inserirVertice(1, 1);
    grafoSemArticulacao.inserirVertice(2, 1);
    grafoSemArticulacao.inserirVertice(3, 1);
    grafoSemArticulacao.inserirVertice(4, 1);
    grafoSemArticulacao.inserirAresta(grafoSemArticulacao.buscaVertice(1), grafoSemArticulacao.buscaVertice(2), 1);
    grafoSemArticulacao.inserirAresta(grafoSemArticulacao.buscaVertice(2), grafoSemArticulacao.buscaVertice(3), 1);
    grafoSemArticulacao.inserirAresta(grafoSemArticulacao.buscaVertice(3), grafoSemArticulacao.buscaVertice(4), 1);
    grafoSemArticulacao.inserirAresta(grafoSemArticulacao.buscaVertice(4), grafoSemArticulacao.buscaVertice(1), 1);
    assert(grafoSemArticulacao.possui_articulacao() == false);

    cout << "Todos os testes passaram!" << endl;
}

void testarNConexo() {
    // Teste 1: Grafo 1-conexo (grafo simples)
    GrafoLista grafo1Conexo;
    grafo1Conexo.inserirVertice(1, 1);
    grafo1Conexo.inserirVertice(2, 1);
    grafo1Conexo.inserirVertice(3, 1);
    grafo1Conexo.inserirAresta(grafo1Conexo.buscaVertice(1), grafo1Conexo.buscaVertice(2), 1);
    grafo1Conexo.inserirAresta(grafo1Conexo.buscaVertice(2), grafo1Conexo.buscaVertice(3), 1);
    assert(grafo1Conexo.n_conexo() == 1);

    // Teste 2: Grafo 2-conexo (grafo com dois caminhos independentes entre quaisquer dois vértices)
    GrafoLista grafo2Conexo;
    grafo2Conexo.inserirVertice(1, 1);
    grafo2Conexo.inserirVertice(2, 1);
    grafo2Conexo.inserirVertice(3, 1);
    grafo2Conexo.inserirVertice(4, 1);
    grafo2Conexo.inserirAresta(grafo2Conexo.buscaVertice(2), grafo2Conexo.buscaVertice(3), 1);
    grafo2Conexo.inserirAresta(grafo2Conexo.buscaVertice(4), grafo2Conexo.buscaVertice(1), 1);
    assert(grafo2Conexo.n_conexo() == 2);

    cout << "Todos os testes de n_conexo passaram!" << endl;
}

void testarCopiarGrafo() {
    // Cria um grafo original
    GrafoLista grafoOriginal;
    grafoOriginal.inserirVertice(1, 1);
    grafoOriginal.inserirVertice(2, 1);
    grafoOriginal.inserirVertice(3, 1);
    grafoOriginal.inserirAresta(grafoOriginal.buscaVertice(1), grafoOriginal.buscaVertice(2), 1);
    grafoOriginal.inserirAresta(grafoOriginal.buscaVertice(2), grafoOriginal.buscaVertice(3), 1);
    grafoOriginal.inserirAresta(grafoOriginal.buscaVertice(3), grafoOriginal.buscaVertice(1), 1);

    // Copia o grafo
    GrafoLista* grafoCopia = grafoOriginal.copiarGrafo();

    // Verifica se os vértices foram copiados corretamente
    assert(grafoCopia->buscaVertice(1) != nullptr);
    assert(grafoCopia->buscaVertice(2) != nullptr);
    assert(grafoCopia->buscaVertice(3) != nullptr);

    // Verifica se as arestas foram copiadas corretamente
    assert(grafoCopia->buscaAresta(1, 1) != nullptr);
    assert(grafoCopia->buscaAresta(2, 1) != nullptr);
    assert(grafoCopia->buscaAresta(3, 1) != nullptr);

    // Verifica se a cópia é independente do original
    grafoOriginal.removerVertice(grafoOriginal.buscaVertice(1));
    assert(grafoCopia->buscaVertice(1) != nullptr);

    delete grafoCopia;

    cout << "Todos os testes de copiarGrafo passaram!" << endl;
}

void testarBuscaVertice() {
    // Cria um grafo
    GrafoLista grafo;
    grafo.inserirVertice(1, 1);
    grafo.inserirVertice(2, 1);
    grafo.inserirVertice(3, 1);

    // Testa a busca de vértices existentes
    assert(grafo.buscaVertice(1) != nullptr);
    assert(grafo.buscaVertice(2) != nullptr);
    assert(grafo.buscaVertice(3) != nullptr);

    // Testa a busca de um vértice inexistente
    assert(grafo.buscaVertice(4) == nullptr);

    cout << "Todos os testes de buscaVertice passaram!" << endl;
}

void testarBuscaAresta() {
    // Cria um grafo
    GrafoLista grafo;
    grafo.inserirVertice(1, 1);
    grafo.inserirVertice(2, 1);
    grafo.inserirVertice(3, 1);
    grafo.inserirAresta(grafo.buscaVertice(1), grafo.buscaVertice(2), 1);
    grafo.inserirAresta(grafo.buscaVertice(2), grafo.buscaVertice(3), 1);
    grafo.inserirAresta(grafo.buscaVertice(3), grafo.buscaVertice(1), 1);

    // Testa a busca de arestas existentes
    assert(grafo.buscaAresta(1, 1) != nullptr);
    assert(grafo.buscaAresta(2, 1) != nullptr);
    assert(grafo.buscaAresta(3, 1) != nullptr);

    // Testa a busca de uma aresta inexistente
    assert(grafo.buscaAresta(1, 3) == nullptr);

    cout << "Todos os testes de buscaAresta passaram!" << endl;
}

int main() {

    GrafoLista g;
    //g.carrega_grafo();
    g.novo_grafo();

    //cout << endl << endl;

    /*if (g.aresta_ponderada())
        cout << "Arestas ponderadas." << endl;
    else
        cout << "Arestas nao ponderadas." << endl;

    cout << "Ordem do grafo: " << g.get_ordem() << endl;

    if (g.eh_direcionado())
        cout << "Eh direcionado." << endl;
    else
        cout << "Nao eh direcionado." << endl;

    cout << "Eh " << g.n_conexo() << "-conexo." << endl;

    if (g.eh_arvore())
        cout << "Eh arvore." << endl;
    else
        cout << "Nao eh arvore." << endl;


    cout << endl << endl;

    if (g.verticePonderado())
        cout<< "Vertice Ponderada." << endl;
    else
        cout << "Nao eh vertice ponderada." << endl;

    cout<<"Grau do grafo: " << g.getGrau()<<endl;*/

    /*if (g.ehCompleto())
        cout << "Eh completo." << endl;
    else
        cout << "Nao eh completo." << endl;

    if (g.ehBipartido())
        cout << "Eh Bipartido." << endl;
    else
        cout << "Nao eh Bipartido." << endl;*/

    /*if (g.possuiArticulacao())
        cout << "Possui articulacao." << endl;
    else
        cout << "Nao possui articulacao." << endl;

    if (g.possuiPonte())
        cout<< "Possui Ponte." << endl;
    else
        cout << "Nao possui Ponte." << endl;*/

    return 0;
}
