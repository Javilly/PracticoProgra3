#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include "Jugador.h"
#include "Enemigo.h"
#include "Vacio.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


struct casillero{
int numero = 0;
Personaje* ocup = new Vacio();
bool esPared = false;
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

    bool compruebaCasillaVacia(movimiento mov, pos actualPos){
        pos p = actualPos;
        switch (mov){
            case arriba:

                if(p.y==0)
                    p.y=8;
                else
                    p.y-=1;
            break;

            case abajo:

                if(p.y==8)
                    p.y=0;
                else
                    p.y+=1;
            break;

            case derecha:

                if(p.x==8)
                    p.x=0;
                else
                    p.x+=1;
            break;

            case izquierda:

                if(p.x==0)
                    p.x=8;
                else
                    p.x-=1;
            break;
        }
        return (tablero[p.x][p.y].ocup->vacio && !tablero[p.x][p.y].esPared);
    }

    int cantidadNumRes(){
        return cantidadNumerosRestantes;
    }

    void moverPersonaje(Personaje* personaje,movimiento mov){
        pos personajePos = personaje->actualPos;
        tablero[personajePos.x][personajePos.y].ocup= new Vacio();
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
            if(tablero[personajePos.x][personajePos.y].numero != 0){
                cantidadNumerosRestantes--;
                tablero[personajePos.x][personajePos.y].numero=0;
            }
        }
    }

    bool DetectPlayer(movimiento mov, pos actualPos){
        pos p = actualPos;
        switch (mov){
            case arriba:

                if(p.y==0)
                    p.y=8;
                else
                    p.y-=1;
            break;

            case abajo:

                if(p.y==8)
                    p.y=0;
                else
                    p.y+=1;
            break;

            case derecha:

                if(p.x==8)
                    p.x=0;
                else
                    p.x+=1;
            break;

            case izquierda:

                if(p.x==0)
                    p.x=8;
                else
                    p.x-=1;
            break;
        }

       if(tablero[p.x][p.y].ocup->isAPlayer){
         tablero[p.x][p.y].ocup->kill();
        return true;
       }

        return false;
    }

    void tryToRevive(Jugador* jugador){
        if(tablero[jugador->spawnPoint().x][jugador->spawnPoint().y].ocup->vacio){
            if(jugador->revive()){
                jugador->actualPos = jugador->spawnPoint();
                tablero[jugador->spawnPoint().x][jugador->spawnPoint().y].ocup = jugador;
            }
        }else
        {
            jugador->currentStatus = cantRevive;
        }

    }


    pos obtenerSpawn(int spawnNum){ //0=player1 1=player 2 -- 2 y 3 enemigos
        return spawns[spawnNum];
    }


    void LeerTablero(){  //Tablero fake para pruebas
        int totalNum = 0;
        int numero= 0;
        pos spawn1;
        pos spawn2;
        pos spawn3;
        pos spawn4;

        std::string str;
        std::ifstream file ("mapa.txt",std::ios::in);

        if (file) {
            while (!file.eof()) str.push_back(file.get());
        }

        std::cout << str << '\n';
        std::string delimiter = ", ";

        size_t index = 0;
        std::string token;

        int i = 0;
        int j = 0;
        int contador = 0;

        while ((index = str.find(delimiter)) != std::string::npos)
        {
            token = str.substr(0, index);
            std::cout << token << std::endl;

            if(contador <= 80){
                tablero[i][j].numero = std::stoi(token);
                if(std::stoi(token) == 0)
                    tablero[i][j].esPared=true;
                else
                {
                    tablero[i][j].esPared=false;
                    totalNum++;
                }
            }
            else if(contador == 81){
                spawn1.x = std::stoi(token);

            }
            else if(contador == 82){
                spawn1.y = std::stoi(token);
            }
            else if(contador == 83){
                spawn2.x = std::stoi(token);
            }
            else if(contador == 84){
                spawn2.y = std::stoi(token);
            }
            else if(contador == 85){
                spawn3.x = std::stoi(token);
            }
            else if(contador == 86){
                spawn3.y = std::stoi(token);
            }
            else if(contador == 87){
                spawn4.x = std::stoi(token);
            }
            contador++;
            str.erase(0, index + delimiter.length());
            i++;
            if(i = 8)
            {
                i = 0;
                j++;
            }
        }
        spawn4.y = std::stoi(str);
        cantidadNumerosRestantes = totalNum;
        spawns[0] = spawn1;
        spawns[1] = spawn2;
        spawns[2] = spawn3;
        spawns[3] = spawn4;

        /*
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
        */

        }

};


#endif // TABLERO_H_INCLUDED
