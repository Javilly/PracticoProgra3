#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include "Jugador.h"
#include "Enemigo.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


struct casillero{
int numero;
Personaje* ocup;
bool esPared;
};


class Tablero{

private:
    casillero tablero[9][9];
    int cantidadNumerosRestantes;
    pos spawns[4];
public:

    Tablero(){
        LeerTablero();
    }

    bool compruebaCasillaVacia(pos p){
        return (tablero[p.x][p.y].ocup == NULL && !tablero[p.x][p.y].esPared);
    }


    void moverPersonaje(Personaje* personaje,movimiento mov){
        pos personajePos = personaje->actualPos;
        tablero[personajePos.x][personajePos.y].ocup = NULL;
        switch (mov){
            case arriba:

                if(personajePos.y==0)
                    personajePos.y=8;
                else
                    personajePos.y-=1;
            break;

            case abajo:

                if(personajePos.y==8)
                    personajePos.y=0;
                else
                    personajePos.y+=1;
            break;

            case derecha:

                if(personajePos.x==8)
                    personajePos.x=0;
                else
                    personajePos.x+=1;
            break;

            case izquierda:

                if(personajePos.x==0)
                    personajePos.x=8;
                else
                    personajePos.x-=1;
            break;
        }
        personaje->ultimoMov=mov;
        personaje->actualPos=personajePos;
        tablero[personajePos.x][personajePos.y].ocup=personaje;
        if(personaje->isAPlayer){
            personaje->puntos+=tablero[personajePos.x][personajePos.y].numero;
            tablero[personajePos.x][personajePos.y].numero=0;
        }
    }

    void tryToRevive(Jugador* jugador){
        if(tablero[jugador->spawnPoint().x][jugador->spawnPoint().y].ocup == NULL){
            if(jugador->revive()){
                jugador->actualPos = jugador->spawnPoint();
                tablero[jugador->spawnPoint().x][jugador->spawnPoint().y].ocup = jugador;
            }
        }
        jugador->currentStatus = cantRevive;
    }


    pos obtenerSpawn(int spawnNum){ //0=player1 1=player 2 -- 2 y 3 enemigos
        return spawns[spawnNum];
    }


    void LeerTablero(){  //Tablero fake para pruebas
        int totalNum = 0;
        int numero= 0;
        for(int i = 0 ; i< 8 ; i++){
            for(int j = 0 ; j< 8 ; j++){
                tablero[i][j].numero = numero;
                if(numero == 0)
                    tablero[i][j].esPared=true;
                else
                {
                    tablero[i][j].esPared=false;
                    totalNum++;
                }


                numero++;
                if(numero == 10)
                    numero = -9;

            }
        }
        cantidadNumerosRestantes = totalNum;

        pos spawn1;
        pos spawn2;
        pos spawn3;
        pos spawn4;
        spawn1.x =1;
        spawn1.y =1;
        spawn2.x =2;
        spawn2.y =2;
        spawn3.x =8;
        spawn3.y =1;
        spawn4.x =7;
        spawn4.y =2;
        spawns[0] = spawn1;
        spawns[1] = spawn2;
        spawns[2] = spawn3;
        spawns[3] = spawn4;
        }

};


#endif // TABLERO_H_INCLUDED
