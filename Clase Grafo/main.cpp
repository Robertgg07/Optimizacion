 /*
 *  Programa principal.
 *
 *
 *               Autor : Robert García García
 *               Cursos  : 2025-26
 */

#include <iostream>
#include <cstring>
#include "grafo.h"

using namespace std;

void menu(unsigned dirigido, char &opcion)
{
    cout << "c. [c]argar grafo desde fichero" << endl;
    cout << "i. Mostrar [i]nformacion basica del grafo" << endl;

    if (!dirigido)
    {
        cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
        cout << "r. Bosque de Prim de Coste Mínimo\n" << endl;
    }
    else
    {
        cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
        cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
    }

    cout << "q. Finalizar el programa" << endl;
    cout << "Introduce la letra de la accion a ejecutar  > ";
    cin >> opcion;
}

int main()
{
    int error;
    char fichero[85], opcion;

    cout << "Introduzca el nombre del fichero con el grafo: ";
    cin >> fichero;

    GRAFO G(fichero, error);

    if (error)
    {
        cout << "Introduzca el nombre correctamente del fichero con el grafo: \n";
        return 0;
    }

    do
    {
        menu(G.Es_dirigido(), opcion);

        switch (opcion)
        {
        case 'i': G.Info_Grafo(); break;
        case 'a': G.Mostrar_Listas(0); break;
        case 's': G.Mostrar_Listas(1); break;
        case 'p': G.Mostrar_Listas(-1); break;
        case 'r': G.Prim(); break;
        }

    } while (opcion != 'q');

    return 0;
}