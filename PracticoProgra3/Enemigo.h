#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED
#include "Personaje.h"

class Enemigo:public Personaje{

public:
    Enemigo(pos spawn){
        this->vacio = false;
        this->currentStatus = alive;
        this->isAPlayer = false;
        this->actualPos=spawn;
        this->ultimoMov = arriba;
    }
};

#endif // ENEMIGO_H_INCLUDED
