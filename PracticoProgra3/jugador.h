#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED
#include "personaje.h"


class Jugador:public Personaje{
private:
    int life;
    pos posInicial;


public:


    Jugador(pos spawn){
        this->currentStatus = alive;
        this->puntos=0;
        this->life = 3;
        this->posInicial = spawn;
        this->actualPos = spawn;
        this->isAPlayer = true;
        this->vacio = false;
        this->ultimoMov = arriba;
    }
    pos spawnPoint(){
        return posInicial;
    }
    int VidasRestantes(){
        return this->life;
    }
    bool revive(){
        if(life > 0){
            life--;
            currentStatus = alive;
            return true;
        }
            currentStatus = outOfLifes;
            return false;
    }


};

#endif // JUGADOR_H_INCLUDED
