#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED
#include "string.h"
#include <iostream>
#include <time.h>
#include <windows.h>

enum estadoJugador{
    alive,
    cantRevive,
    outOfLifes,
    dead
};
struct pos{
int x;
int y;
};
enum movimiento{
arriba,
derecha,
abajo,
izquierda
};

class Personaje{
public:
    estadoJugador currentStatus;
    movimiento ultimoMov;
    int puntos;
    bool isAPlayer;
    pos actualPos;
};
#endif // PERSONAJE_H_INCLUDED
