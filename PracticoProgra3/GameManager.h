#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED
#include "Tablero.h"
#include <windows.h>
#include <stdio.h>
#include "conio.h"
#include <thread>
#include <mutex>

using namespace std;

mutex accesoTablero;


void CheckWinner(Tablero* tablero, Jugador* jugador1, Jugador* jugador2){
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

void PrintTablero(Tablero* tablero,Jugador* jugador1, Jugador* jugador2){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        while(tablero->cantidadNumRes() > 0 && (jugador1->currentStatus!=outOfLifes || jugador2->currentStatus!=outOfLifes)){
            accesoTablero.lock();
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {


                    if (tablero->ObtenerCasilla(i,j).esPared == true)
                    {
                       std::cout<< " X";
                    }
                    else
                    {
                        if(tablero->ObtenerCasilla(i,j).ocup->name == "Jugador1")
                            {
                            SetConsoleTextAttribute(hConsole, 3);

                            std::cout << " P";

                            SetConsoleTextAttribute(hConsole, 15);
                        }
                        else if(tablero->ObtenerCasilla(i,j).ocup->name == "Jugador2")
                        {
                            SetConsoleTextAttribute(hConsole, 5);

                            std::cout << " P";

                            SetConsoleTextAttribute(hConsole, 15);
                        }
                        else if(tablero->ObtenerCasilla(i,j).ocup->name == "Enemy")
                        {
                            SetConsoleTextAttribute(hConsole, 4);

                            std::cout << " E";

                            SetConsoleTextAttribute(hConsole, 15);
                        }
                        else if(tablero->ObtenerCasilla(i,j).numero != 0){
                            if (tablero->ObtenerCasilla(i,j).numero > 0)
                                std::cout << " ";

                            cout << tablero->ObtenerCasilla(i,j).numero;
                        }else{
                            std::cout << "  ";
                        }

                    }
                    std::cout << " ";
                }
                std::cout << "\n";
                std::cout << "";
            }
            accesoTablero.unlock();
        }
    }

void EnemyCicle(Enemigo* enemigo,Tablero* tablero,Jugador* jugador1, Jugador* jugador2){
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
    CheckWinner(tablero,jugador1,jugador2);
}
 void PlayerCicle(Jugador* jugador,Tablero* tablero){
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
        jugador1=new Jugador(tablero->obtenerSpawn(0),"Jugador1");
        jugador2=new Jugador(tablero->obtenerSpawn(1),"Jugador2");
        enemigo1=new Enemigo(tablero->obtenerSpawn(2));
        enemigo2=new Enemigo(tablero->obtenerSpawn(3));
        thread player1(PlayerCicle,jugador1,tablero);
        thread player2(PlayerCicle,jugador2,tablero);
        thread enemy1(EnemyCicle,enemigo1,tablero,jugador1,jugador2);
        thread enemy2(EnemyCicle,enemigo2,tablero,jugador1,jugador2);
        thread imprTablero(PrintTablero,tablero,jugador1,jugador2);

        player1.join();
        player2.join();
        enemy1.join();
        enemy2.join();
        imprTablero.join();
    }
};


#endif // GAMEMANAGER_H_INCLUDED
