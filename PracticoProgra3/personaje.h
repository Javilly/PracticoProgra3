#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED
#include "string.h"
#include <iostream>
#include <time.h>
#include <windows.h>

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

protected:
    pos actualPos;
    std::string nombre;
    movimiento ultimoMov;

public:
    pos getPos(){
        return this->actualPos;
    }

    std::string getNombre(){
        return nombre;
    }

    void mover(){

    }



};
#endif // PERSONAJE_H_INCLUDED
