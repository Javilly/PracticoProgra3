#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED
#include "Tablero.h"
#include <thread>
#include <mutex>

using namespace std;

class GameManager{
private:
    Tablero* tablero;
    Jugador* jugador1;
    Jugador* jugador2;
    Enemigo* enemigo1;
    Enemigo* enemigo2;
    mutex accesoTablero;

public:
    GameManager(){
        tablero = new Tablero();
    }
    void StartGame(){
        jugador1=new Jugador(tablero->obtenerSpawn(0));
        jugador2=new Jugador(tablero->obtenerSpawn(1));
        enemigo1=new Enemigo(tablero->obtenerSpawn(2));
        enemigo2=new Enemigo(tablero->obtenerSpawn(3));
        thread player1(PlayerCicle,jugador1);
        thread player2(PlayerCicle,jugador2);
        thread enemy1(EnemyCicle,enemigo1);
        thread enemy2(EnemyCicle,enemigo2);

        player1.join();
        player2.join();
        enemy1.join();
        enemy2.join();
    }

private:
    void PlayerCicle(Jugador* jugador){
        bool canMove;
        int contador;
        while(jugador->currentStatus!=outOfLifes && tablero->cantidadNumRes() > 0){
            if(jugador->currentStatus!=alive){
                accesoTablero.lock();
                tablero->tryToRevive(jugador);
                accesoTablero.unlock();
            }
            else{
                canMove=false;
                contador=0;
                jugador->GenerateMov();
                accesoTablero.lock();
                do{
                    if(tablero->compruebaCasillaVacia(jugador->getMov(contador),jugador->actualPos))
                        canMove=true;
                    else
                        contador++;

                }while(!canMove&& contador<4);
                    if(contador<4)
                        tablero->moverPersonaje(jugador,jugador->getMov(contador));

                    accesoTablero.unlock();
            }
        }

    }
    void EnemyCicle(Enemigo* enemigo){
        bool canMove;
        int contador;

        while(tablero->cantidadNumRes() > 0 && (jugador1->currentStatus!=outOfLifes || jugador2->currentStatus!=outOfLifes)){
            canMove=false;
            contador=0;
            enemigo->GenerateMov();
            accesoTablero.lock();
            do{
                if(tablero->compruebaCasillaVacia(enemigo->getMov(contador),enemigo->actualPos)){
                    canMove=true;
                }
                else
                if(tablero->DetectPlayer(enemigo->getMov(contador),enemigo->actualPos)){
                    canMove=true;
                }
                else
                    contador++;

            }while(!canMove&& contador<4);
                    if(contador<4)
                        tablero->moverPersonaje(enemigo,enemigo->getMov(contador));
            accesoTablero.unlock();
        }
        CheckWinner();
    }

    void CheckWinner(){
        if(tablero->cantidadNumRes()>0){
            std::cout<< "Los jugadores pierden";
        }
        else{
            if(jugador1->puntos>jugador2->puntos)
                std::cout<<"Gana el jugador 2 con " << jugador2->puntos << " puntos";
            else{
                std::cout<<"Gana el jugador 1 con " << jugador1->puntos << " puntos";
            }
        }
    }
};

#endif // GAMEMANAGER_H_INCLUDED
