#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED
#include "Tablero.h"

class GameManager{
private:
    Tablero* tablero;
    Jugador* jugador1;
    Jugador* jugador2;
    Enemigo* enemigo1;
    Enemigo* enemigo2;
public:
    GameManager(){
        tablero = new Tablero();
    }
    void StartGame(){
        jugador1=new Jugador(tablero->obtenerSpawn(0));
        jugador2=new Jugador(tablero->obtenerSpawn(1));
        enemigo1=new Enemigo(tablero->obtenerSpawn(2));
        enemigo2=new Enemigo(tablero->obtenerSpawn(3));
    }

private:
    bool GameCicle(Personaje* personaje){

    }
};

#endif // GAMEMANAGER_H_INCLUDED
