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
    bool vacio;
    pos actualPos;
    movimiento pociblesMov[4];

    movimiento getMov(int index){
        return pociblesMov[index];
    }
    void kill(){
        currentStatus = dead;
    }

    void GenerateMov(){
        int random;
        srand(time (NULL));
        random = ((rand() % (4)));
        if(random == ultimoMov)
            pociblesMov[0]=movimiento((random+2)%4);

        do{
            srand(time (NULL));
            random = ((rand() % (4)));
        }while(random == ultimoMov || random== pociblesMov[0]);

        pociblesMov[1] = movimiento(random);
        pociblesMov[2] = movimiento((pociblesMov[0]+pociblesMov[1]+ultimoMov)%4);
        pociblesMov[3] = ultimoMov;

    }

};
#endif // PERSONAJE_H_INCLUDED
