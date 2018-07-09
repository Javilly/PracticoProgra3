#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED
#include "Tablero.h"
#include <thread>
#include <mutex>



class GameManager{
private:
    Tablero* tablero;
    Jugador* jugador1;
    Jugador* jugador2;
    Enemigo* enemigo1;
    Enemigo* enemigo2;
    //mutex accesoTablero;

public:
    GameManager(){
        tablero = new Tablero();
    }
    void StartGame(){
        bool canMove;
        int contador;

        jugador1=new Jugador(tablero->obtenerSpawn(0), "Jugador1");
        jugador2=new Jugador(tablero->obtenerSpawn(1), "Jugador1");
        enemigo1=new Enemigo(tablero->obtenerSpawn(2));
        enemigo2=new Enemigo(tablero->obtenerSpawn(3));

        while(tablero->cantidadNumRes() > 0 && (jugador1->currentStatus!=outOfLifes || jugador2->currentStatus!=outOfLifes)){
            if(jugador1->currentStatus!=outOfLifes){
                if(jugador1->currentStatus!=alive){
                    tablero->tryToRevive(jugador1);
                }
                else{
                    canMove=false;
                    contador=0;
                    jugador1->GenerateMov();
                    do{
                        if(tablero->compruebaCasillaVacia(jugador1->getMov(contador),jugador1->actualPos))
                            canMove=true;
                        else
                            contador++;

                    }while(!canMove&& contador<4);
                        if(contador<4)
                            tablero->moverPersonaje(jugador1,jugador1->getMov(contador));


                }
            }
            if(jugador2->currentStatus!=outOfLifes){
                if(jugador2->currentStatus!=alive){
                    tablero->tryToRevive(jugador2);
                }
                else{
                    canMove=false;
                    contador=0;
                    jugador2->GenerateMov();

                    do{
                        if(tablero->compruebaCasillaVacia(jugador2->getMov(contador),jugador2->actualPos))
                            canMove=true;
                        else
                            contador++;

                    }while(!canMove&& contador<4);
                        if(contador<4)
                            tablero->moverPersonaje(jugador2,jugador2->getMov(contador));

                }
            }
            canMove=false;
            contador=0;
            enemigo1->GenerateMov();

            do{
                if(tablero->compruebaCasillaVacia(enemigo1->getMov(contador),enemigo1->actualPos)){
                    canMove=true;
                }
                else
                if(tablero->DetectPlayer(enemigo1->getMov(contador),enemigo1->actualPos)){
                    canMove=true;
                }
                else
                    contador++;

            }while(!canMove&& contador<4);
                    if(contador<4)
                        tablero->moverPersonaje(enemigo1,enemigo1->getMov(contador));

            canMove=false;
            contador=0;
            enemigo2->GenerateMov();
            do{
                 if(tablero->compruebaCasillaVacia(enemigo2->getMov(contador),enemigo2->actualPos)){
                    canMove=true;
                }
                else
                if(tablero->DetectPlayer(enemigo2->getMov(contador),enemigo2->actualPos)){
                    canMove=true;
                }
                else
                    contador++;

            }while(!canMove&& contador<4);

                if(contador<4)
                    tablero->moverPersonaje(enemigo2,enemigo2->getMov(contador));


            /*
            std::cout<<"Pj1 "<< jugador1->actualPos.x <<","<< jugador1->actualPos.y<<"Puntos : "<< jugador1->puntos << " Vidas restantes : " << jugador1->VidasRestantes() <<std::endl;
            std::cout<<"Pj2 "<< jugador2->actualPos.x <<","<< jugador2->actualPos.y<<"Puntos : "<< jugador2->puntos << " Vidas restantes : " << jugador2->VidasRestantes() <<std::endl;
            std::cout<<"Enm1 "<< enemigo1->actualPos.x <<","<< enemigo1->actualPos.y<<std::endl;
            std::cout<<"Enm2 "<< enemigo2->actualPos.x <<","<< enemigo2->actualPos.y<<std::endl;
            */

            PrintTablero();

        }


        CheckWinner();
    }

private:

    void CheckWinner(){
        if(tablero->cantidadNumRes()>0){
            std::cout<< "Los jugadores pierden";
        }
        else{
            if(jugador1->puntos<jugador2->puntos)
                std::cout<<"Gana el jugador 2 con " << jugador2->puntos << " puntos";
            else{
                std::cout<<"Gana el jugador 1 con " << jugador1->puntos << " puntos";
            }
        }
    }



    void PrintTablero(){
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                std::cout << " ";

                if (talbero->ObtenerCasilla(i,j),esPared.esPared == true)
                {
                    if(talbero->ObtenerCasilla(i,j),esPared.ocupante.name == "Jugador1")
                        {
                        SetConsoleTextAttribute(hConsole, 3);

                        std::cout << "T";

                        SetConsoleTextAttribute(hConsole, 15);
                    }
                    else if(talbero->ObtenerCasilla(i,j),esPared.ocupante.name == "Jugador2")
                    {
                        SetConsoleTextAttribute(hConsole, 5);

                        std::cout << "T";

                        SetConsoleTextAttribute(hConsole, 15);
                    }
                    else
                    {
                        SetConsoleTextAttribute(hConsole, 4);

                        std::cout << "T";

                        SetConsoleTextAttribute(hConsole, 15);
                    }
                    std::cout << " ";
                }
                else
                {
                    if(cout << talbero->ObtenerCasilla(i,j),esPared.numero != 0){
                        cout << talbero->ObtenerCasilla(i,j),esPared.numero;
                    }else{
                        std::cout << "█";
                    }

                }
            }
            std::cout << "\n";
            std::cout << "";
        }
    }
};

#endif // GAMEMANAGER_H_INCLUDED
