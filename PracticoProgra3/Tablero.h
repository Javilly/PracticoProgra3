#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include "Jugador.h"
#include "Enemigo.h"


struct casillero{
int numero;
Jugador* ocup;
bool esPared;
};


class Tablero{

private:
    casillero tablero[9][9];
    int cantidadNumerosRestantes;
    Jugador jugador1;
    Jugador jugador2;

public:

    Tablero();
    casillero compruebaCasilla(pos);
    bool moverPersonaje(Personaje* personaje,movimiento mov);
    void respawnearJugador(Jugador* jugador);

};


#endif // TABLERO_H_INCLUDED
