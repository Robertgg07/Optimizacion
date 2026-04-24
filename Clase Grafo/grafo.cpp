 /*
 *  GRAFO.CPP - Implementación Clase Grafo
 *
 *
 *  Autor    : Robert García García
 *  Cursos   : 2025-26
 */

#include "grafo.h"

void GRAFO :: destroy()
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

void GRAFO :: build(char nombrefichero[85], int &errorapertura)
{
    ElementoLista dummy;
    ifstream textfile;
    textfile.open(nombrefichero);

    if (textfile.is_open())
    {
        errorapertura = 0;

        unsigned i, j, k;

        textfile >> n >> m >> dirigido;

        LS.resize(n);

        if (dirigido == 1)
            LP.resize(n);

        for (k = 0; k < m; k++)
        {
            textfile >> i >> j >> dummy.c;

            dummy.j = j - 1;
            LS[i - 1].push_back(dummy);

            if (dirigido == 0)
            {
                if (i != j)
                {
                    dummy.j = i - 1;
                    LS[j - 1].push_back(dummy);
                }
            }
        }

        textfile.close();

        if (dirigido == 1)
            ListaPredecesores();
    }
    else
    {
        errorapertura = 1;
    }
}

GRAFO::~GRAFO()
{
    destroy();
}

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
{
    build(nombrefichero, errorapertura);
}

void GRAFO::actualizar(char nombrefichero[85], int &errorapertura)
{
    destroy();
    build(nombrefichero, errorapertura);
}

unsigned GRAFO::Es_dirigido()
{
    return dirigido;
}

void GRAFO::Info_Grafo()
{
    cout << "Numero de nodos: " << n << endl;
    cout << "Numero de aristas: " << m << endl;

    if (dirigido == 1)
        cout << "Tipo: Grafo dirigido" << endl;
    else
        cout << "Tipo: Grafo no dirigido" << endl;
}

void Mostrar_Lista(vector<LA_nodo> L)
{
    for (unsigned i = 0; i < L.size(); i++)
    {
        cout << i + 1 << ": ";

        for (unsigned j = 0; j < L[i].size(); j++)
        {
            cout << "(" << L[i][j].j + 1 << "," << L[i][j].c << ") ";
        }

        cout << endl;
    }
}

void GRAFO::Mostrar_Listas(int l)
{
    if (dirigido == 0)
    {
        cout << "Lista de adyacencia:" << endl;
        Mostrar_Lista(LS);
    }
    else
    {
        if (l == 1)
        {
            cout << "Lista de sucesores:" << endl;
            Mostrar_Lista(LS);
        }
        else if (l == -1)
        {
            cout << "Lista de predecesores:" << endl;
            Mostrar_Lista(LP);
        }
    }
}

void GRAFO::ListaPredecesores()
{
    LP.clear();
    LP.resize(n);

    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < LS[i].size(); j++)
        {
            ElementoLista dummy;

            dummy.j = i;
            dummy.c = LS[i][j].c;

            LP[LS[i][j].j].push_back(dummy);
        }
    }
}


// DFS para componentes conexas
void GRAFO::dfs_cc(unsigned i, vector<bool> &visitado)
{
    visitado[i] = true;
    cout << i + 1;

    // Se recorren los sucesores
    for (unsigned j = 0; j < LS[i].size(); j++)
    {
        if (!visitado[LS[i][j].j])
        {
            cout << ", ";
            dfs_cc(LS[i][j].j, visitado);
        }
    }

    //Al ser dirigido
    if (dirigido == 1)
    {
        for (unsigned j = 0; j < LP[i].size(); j++)
        {
            if (!visitado[LP[i][j].j])
            {
                cout << ", ";
                dfs_cc(LP[i][j].j, visitado);
            }
        }
    }
}

// Componentes conexas
void GRAFO::ComponentesConexas()
{
    vector<bool> visitado(n, false);
    unsigned comp = 0;

    for (unsigned i = 0; i < n; i++)
    {
        if (!visitado[i])
        {
            comp++;
            cout << "Componente conexa " << comp << ": { ";

            dfs_cc(i, visitado);

            cout << " }" << endl;
        }
    }
}

// DFS postorden
void GRAFO::dfs_postnum(unsigned i, vector<bool> &visitado, vector<unsigned> &postnum, unsigned &ind)
{
    visitado[i] = true;

    for (unsigned j = 0; j < LS[i].size(); j++)
    {
        if (!visitado[LS[i][j].j])
            dfs_postnum(LS[i][j].j, visitado, postnum, ind);
    }

    postnum[ind--] = i;
}

//DFS_CFC
void GRAFO::dfs_cfc(unsigned i, vector<bool> &visitado)
{
    visitado[i] = true;
    cout << i + 1;

    for (unsigned j = 0; j < LP[i].size(); j++)
    {
        if (!visitado[LP[i][j].j])
        {
            cout << ", ";
            dfs_cfc(LP[i][j].j, visitado);
        }
    }
}

// Componentes fuertemente conexas
void GRAFO::ComponentesFuertementeConexas()
{
    if (dirigido == 0)
    {
        cout << "El grafo no es dirigido" << endl;
        return;
    }

    vector<bool> visitado(n, false);
    vector<unsigned> postnum(n);
    unsigned ind = n - 1;

    for (unsigned i = 0; i < n; i++)
    {
        if (!visitado[i])
            dfs_postnum(i, visitado, postnum, ind);
    }

    fill(visitado.begin(), visitado.end(), false);

    unsigned comp = 0;

    for (unsigned i = 0; i < n; i++)
    {
        if (!visitado[postnum[i]])
        {
            comp++;
            cout << "Componente fuertemente conexa " << comp << ": { ";
            dfs_cfc(postnum[i], visitado);
            cout << " }" << endl;
        }
    }
}
// Buscar representante del conjunto
int buscar(vector<int> &padre, int i)
{
    if (padre[i] != i)
        padre[i] = buscar(padre, padre[i]);
    return padre[i];
}

// Unir dos conjuntos
void unir(vector<int> &padre, int a, int b)
{
    a = buscar(padre, a);
    b = buscar(padre, b);
    padre[a] = b;
}

void GRAFO::Sollin()
{
    if (dirigido == 1)
    {
        cout << "El grafo es dirigido, no se puede aplicar Sollin" << endl;
        return;
    }

    vector<int> padre(n);
    vector<int> mejor(n);

    // inicializar cada nodo como propia componente
    for (unsigned i = 0; i < n; i++)
        padre[i] = i;

    int num_componentes = n;
    int coste_total = 0;

    while (num_componentes > 1)
    {
        // reiniciar mejores aristas
        for (unsigned i = 0; i < n; i++)
            mejor[i] = -1;

        // buscar mejor arista para cada componente
        for (unsigned i = 0; i < n; i++)
        {
            for (unsigned k = 0; k < LS[i].size(); k++)
            {
                unsigned j = LS[i][k].j;
                int coste = LS[i][k].c;

                int comp_i = buscar(padre, i);
                int comp_j = buscar(padre, j);

                if (comp_i == comp_j) continue;

                // guardar mejor arista
                if (mejor[comp_i] == -1 || coste < LS[mejor[comp_i]][0].c)
                    mejor[comp_i] = i;

                if (mejor[comp_j] == -1 || coste < LS[mejor[comp_j]][0].c)
                    mejor[comp_j] = j;
            }
        }

        // unir componentes
        for (unsigned i = 0; i < n; i++)
        {
            if (mejor[i] != -1)
            {
                unsigned u = mejor[i];

                for (unsigned k = 0; k < LS[u].size(); k++)
                {
                    unsigned j = LS[u][k].j;
                    int coste = LS[u][k].c;

                    int comp_u = buscar(padre, u);
                    int comp_j = buscar(padre, j);

                    if (comp_u != comp_j)
                    {
                        // añadir arista al MST
                        cout << u + 1 << " - " << j + 1
                             << " (coste " << coste << ")" << endl;

                        coste_total += coste;

                        unir(padre, comp_u, comp_j);
                        num_componentes--;

                        break; // solo una arista por componente
                    }
                }
            }
        }
    }

    cout << "Coste total: " << coste_total << endl;
}
// Añadir criterio de parada si el grafo no es conexo