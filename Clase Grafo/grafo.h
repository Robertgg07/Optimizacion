/*
 *  GRAFO.h - definicion de la clase GRAFO
 *
 *  Autor : Robert García García
 *  Cursos  : 2025-26
 */

#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <deque>

using namespace std;

#define gotoxy(x,y)  printf("\33[%d;%dH",y,x)
#define clrscr()     gotoxy(1,1); printf("\33[2J")

const unsigned UERROR = 65000;
const int maxint      = 1000000;

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

    void dfs_cc(unsigned i, vector<bool> &visitado);
    void dfs_postnum(unsigned i, vector<bool> &visitado, vector<unsigned> &postnum, unsigned &postnum_ind);
    void dfs_cfc(unsigned i, vector<bool> &visitado);

public:
    GRAFO(char nombrefichero[], int &errorapertura);
    void actualizar(char nombrefichero[], int &errorapertura);
    unsigned Es_dirigido();
    void Info_Grafo();
    void Mostrar_Listas(int l);
    void ListaPredecesores();
    void ComponentesConexas();
    void ComponentesFuertementeConexas();
    ~GRAFO();
    void Sollin();
};

#endif