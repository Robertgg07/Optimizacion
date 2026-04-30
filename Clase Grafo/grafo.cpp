    /*
    *  GRAFO.CPP - Implementación Clase Grafo
    *
    *
    *  Autor    : Robert García García
    *  Cursos   : 2025-26
    */

#include "grafo.h"

void GRAFO::destroy()
{
    for (unsigned i = 0; i < n; i++)
    {
        LS[i].clear();
        if (dirigido == 1)
            LP[i].clear();
    }
    LS.clear();
    if (dirigido == 1)
        LP.clear();
}

void GRAFO::build(char nombrefichero[85], int &errorapertura)
{
    ElementoLista dummy;
    ifstream f(nombrefichero);

    if (!f.is_open())
    {
        errorapertura = 1;
        return;
    }

    errorapertura = 0;
    f >> n >> m >> dirigido;

    LS.resize(n);
    if (dirigido == 1)
        LP.resize(n);

    for (unsigned k = 0; k < m; k++)
    {
        unsigned i, j;
        f >> i >> j >> dummy.c;

        dummy.j = j - 1;
        LS[i - 1].push_back(dummy);

        if (dirigido == 0 && i != j)
        {
            dummy.j = i - 1;
            LS[j - 1].push_back(dummy);
        }
    }

    if (dirigido == 1)
        ListaPredecesores();
}

unsigned GRAFO::Es_dirigido()
{
    return dirigido;
}

void GRAFO::Info_Grafo()
{
    cout << "Nodos: " << n << endl;
    cout << "Aristas: " << m << endl;
    cout << (dirigido ? "Dirigido" : "No dirigido") << endl;
}

void GRAFO::Mostrar_Listas(int l)
{
    vector<LA_nodo> *lista;

    if (l == 0) lista = &LS;
    else if (l == 1) lista = &LS;
    else lista = &LP;

    for (unsigned i = 0; i < n; i++)
    {
        cout << i + 1 << ": ";
        for (auto &e : (*lista)[i])
            cout << "(" << e.j + 1 << "," << e.c << ") ";
        cout << endl;
    }
}

//
void GRAFO::ListaPredecesores()
{
    for (unsigned i = 0; i < n; i++)
        LP[i].clear();

    for (unsigned i = 0; i < n; i++)
    {
        for (auto &e : LS[i])
        {
            ElementoLista aux;
            aux.j = i;
            aux.c = e.c;
            LP[e.j].push_back(aux);
        }
    }
}

void GRAFO::Prim()
{
    if (dirigido)
    {
        cout << "El grafo es dirigido" << endl;
        return;
    }

    vector<int> coste(n, maxint);
    vector<int> pred(n, -1);
    vector<bool> enM(n, false);

    int total = 0;

    int r;
    cout << "Introduce nodo inicial (1-" << n << "): ";
    cin >> r;
    r--; // pasar a índice interno

    coste[r] = 0;
    pred[r] = r;

    for (unsigned k = 0; k < n; k++)
    {
        int min = maxint, u = -1;

        // seleccionar nodo mínimo
        for (unsigned i = 0; i < n; i++)
        {
            if (!enM[i] && coste[i] < min)
            {
                min = coste[i];
                u = i;
            }
        }

        if (u == -1) break;

        enM[u] = true;

        if (u != r)
        {
            cout << pred[u] + 1 << " - " << u + 1
                 << " (coste " << coste[u] << ")" << endl;
            total += coste[u];
        }

        // actualizar vecinos
        for (auto &e : LS[u])
        {
            int v = e.j;
            int w = e.c;

            if (!enM[v] && w < coste[v])
            {
                coste[v] = w;
                pred[v] = u;
            }
        }
    }

    cout << "Coste total del arbol: " << total << endl;
}

GRAFO::GRAFO(char nombrefichero[], int &errorapertura)
{
    build(nombrefichero, errorapertura);
}

void GRAFO::actualizar(char nombrefichero[], int &errorapertura)
{
    destroy();
    build(nombrefichero, errorapertura);
}

GRAFO::~GRAFO()
{
    destroy();
}