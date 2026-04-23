 /*
 *  Programa principal.
 *
 *
 *               Autor : Robert García García
 *               Cursos  : 2025-26
 */

#include <string.h>
#include "grafo.h"

void pressanykey()
{   
    char c;
    cout << endl;
    cout << "pulsa [c] para continuar: ";
    cin >> c;
}

void menu (unsigned dirigido, char &opcion)
// Expresión del menú según sea dirigido o no dirigido
{
    cout << "c. [c]argar grafo desde fichero" << endl;

    if (dirigido == 0) // NO dirigido
    {
        cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
        cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
        cout << "x. Componentes cone[x]as" << endl;
    }
    else // DIRIGIDO
    {
        cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
        cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
        cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
        cout << "f. Componentes [f]uertemente conexas" << endl;
    }

    cout << "q. Finalizar el programa" << endl;
    cout << "Introduce la letra de la accion a ejecutar  > ";
    cin >> opcion;
}

int main(int argc, char *argv[])
{
    int error_apertura;
    char nombrefichero[85], opcion;

    clrscr();

    // Carga inicial
    if (argc > 1)
    {
        cout << "Cargando datos desde el fichero dado como argumento" << endl;
        strcpy(nombrefichero, argv[1]);
    }
    else
    {
        cout << "Introduce el nombre completo del fichero de datos" << endl;
        cin >> nombrefichero;
    }

    GRAFO G(nombrefichero, error_apertura);

    if (error_apertura == 1)
    {
        cout << "Error en la apertura del fichero: revisa nombre y formato" << endl;
        pressanykey();
        clrscr();
    }
    else
    {
        cout << "Grafo cargado desde el fichero " << nombrefichero << endl;
        pressanykey();
        clrscr();

        do
        {
            menu(G.Es_dirigido(), opcion);

            switch (opcion)
            {
                case 'c':
                    clrscr();
                    cout << "Introduce el nombre completo del fichero de datos" << endl;
                    cin >> nombrefichero;

                    G.actualizar(nombrefichero, error_apertura);

                    if (error_apertura == 1)
                        cout << "Error en la apertura del fichero" << endl;
                    else
                        cout << "Fichero cargado correctamente" << endl;

                    pressanykey();
                    clrscr();
                    break;

                case 'i':
                    clrscr();
                    cout << "Grafo cargado desde " << nombrefichero << endl;
                    G.Info_Grafo();
                    pressanykey();
                    clrscr();
                    break;

                case 'a': // NO DIRIGIDO
                    clrscr();
                    G.Mostrar_Listas(0);
                    pressanykey();
                    clrscr();
                    break;

                case 's': // DIRIGIDO
                    clrscr();
                    G.Mostrar_Listas(1);
                    pressanykey();
                    clrscr();
                    break;

                case 'p': // DIRIGIDO
                    clrscr();
                    G.Mostrar_Listas(-1);
                    pressanykey();
                    clrscr();
                    break;

                case 'x': // COMPONENTES CONEXAS
                    clrscr();
                    G.ComponentesConexas();
                    pressanykey();
                    clrscr();
                    break;

                case 'f': // COMPONENTES FUERTEMENTE CONEXAS
                    clrscr();
                    G.ComponentesFuertementeConexas();
                    pressanykey();
                    clrscr();
                    break;
            }

        } while (opcion != 'q');
    }

    cout << "Fin del programa" << endl;
    return 0;
}
