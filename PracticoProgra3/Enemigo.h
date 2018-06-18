#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED
#include "Personaje.h"

class Enemigo:public Personaje{

public:
    Enemigo(pos spawn){
        this->currentStatus = alive;
        this->isAPlayer = false;
        this->actualPos=spawn;
    }
};

#endif // ENEMIGO_H_INCLUDED
