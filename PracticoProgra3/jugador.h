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

    bool revive(){
        if(life > 0){
            life--;
            currentStatus = alive;
            return true;
        }
            currentStatus = cantRevive;
            return false;
    }


};

#endif // JUGADOR_H_INCLUDED
