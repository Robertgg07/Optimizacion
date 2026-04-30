/*
 *  GRAFO.h - definicion de la clase GRAFO
 *
 *  Autor : Robert García García
 *  Cursos  : 2025-26
 */

#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

const int maxint = numeric_limits<int>::max();

typedef struct
{
    unsigned j;
    int c;
} ElementoLista;

typedef vector<ElementoLista> LA_nodo;

class GRAFO
{
    unsigned dirigido;
    unsigned n;
    unsigned m;
    vector<LA_nodo> LS;
    vector<LA_nodo> LP;

    void destroy();
    void build(char nombrefichero[85], int &errorapertura);

public:
    GRAFO(char nombrefichero[], int &errorapertura);
    void actualizar(char nombrefichero[], int &errorapertura);

    unsigned Es_dirigido();
    void Info_Grafo();
    void Mostrar_Listas(int l);
    void ListaPredecesores();

    void Prim();
    ~GRAFO();
};

#endif