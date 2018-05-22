#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED
#include "personaje.h"
class Jugador:protected Personaje{
private:
    int vidas;
    pos posInicial;

public:
    Jugador(pos spawn, int numeroDeJugador){
        this->vidas = 3;
        this->posInicial = spawn;
        this->actualPos = spawn;
        this->nombre = "Jugador" + numeroDeJugador;
    }

};

#endif // JUGADOR_H_INCLUDED
