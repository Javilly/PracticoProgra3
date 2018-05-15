#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include "Jugador.h"
#include "Enemigo.h"

enum ocupante{
vacio=0,
jugador1,
jugador2,
enemigo,
pared
};

struct casillero{
int numero;
ocupante ocup;
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
    movimiento moverPersonaje(Personaje* personaje,movimiento mov);
    void respawnearJugador(Jugador* jugador);

};


#endif // TABLERO_H_INCLUDED
