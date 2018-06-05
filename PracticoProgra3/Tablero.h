#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include "Jugador.h"
#include "Enemigo.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


struct casillero{
int numero;
Jugador* ocup;
bool esPared;
};


class Tablero{

private:
    casillero tablero[9][9];
    int cantidadNumerosRestantes;

public:

    Tablero(){};
    casillero compruebaCasilla(pos);
    bool moverPersonaje(Personaje* personaje,movimiento mov);
    void respawnearJugador(Jugador* jugador);



    void LeerTablero()
    {
        vector<int> numbers;
        ifstream inputFile("mapa.txt");

        if (inputFile.good())
        {
            int current_number = 0;
            while (inputFile >> current_number){
            numbers.push_back(current_number);
        }


        inputFile.close();


        cout << "Numeros: " << endl;
        int contador = 0;

        int cantidadInicial = 0;

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                casillero casilleroActual;
                if(numbers[contador] == 0)
                {
                    casilleroActual.esPared = true;
                }
                else
                {
                    casilleroActual.esPared = false;
                    cantidadInicial++;
                }
                casilleroActual.numero = numbers[contador];
                tablero[i][j] = casilleroActual;
                cout << tablero[i][j].numero << " ";
                contador++;
            }
            cout << endl;
        }

        cout << endl;

        cantidadNumerosRestantes = cantidadInicial;
        }
    }
};


#endif // TABLERO_H_INCLUDED
