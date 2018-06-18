#ifndef VACIO_H_INCLUDED
#define VACIO_H_INCLUDED

class Vacio:public Personaje{

public:
    Vacio(){
        this->vacio = true;
        this->isAPlayer = false;
    }
};

#endif // VACIO_H_INCLUDED
