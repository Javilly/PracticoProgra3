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


    void LeerTablero()
    {  //Tablero fake para pruebas

        /*
        int totalNum = 0;

        std::string strTablero;
        std::string strSpawns12;
        std::string strSpawns34;
        std::ifstream file ("mapa.txt",std::ios::in);

        int contadorLeerArchivo = 0;
        if (file) {
            while (!file.eof())
            {
                if(contadorLeerArchivo < 238)
                {
                    strTablero.push_back(file.get());
                }else if(contadorLeerArchivo >= 238 && contadorLeerArchivo <= 248)
                {
                    strSpawns12.push_back(file.get());
                }
                else
                {
                    strSpawns34.push_back(file.get());
                }
                contadorLeerArchivo++;
            }
        }

        std::string delimiterTablero = ", ";
        std::string delimiterSpawns = " - ";
        size_t index = 0;
        std::string token;
        std::string token2;

        int i = 0;
        int j = 0;


        while ((index = strTablero.find(delimiterTablero)) != std::string::npos)
        {
            token = strTablero.substr(0, index);

            tablero[i][j].numero = std::stoi(token);

            if(std::stoi(token) == 0)
                    tablero[i][j].esPared=true;
            else
            {
                tablero[i][j].esPared=false;
                totalNum++;
            }
            strTablero.erase(0, index + delimiterTablero.length());
            i++;
            if(i ==  8)
            {
                i = 0;
                j++;

            }
        }
        tablero[i][j].numero = std::stoi(strTablero);

        std::string stringSpawn1;
        std::string stringSpawn2;
        std::string stringSpawn3;
        std::string stringSpawn4;


        pos spawn1;
        pos spawn2;
        pos spawn3;
        pos spawn4;

        while ((index = strSpawns12.find(delimiterSpawns)) != std::string::npos)
        {
            stringSpawn1 = strSpawns12.substr(0, index);

            strSpawns12.erase(0, index + delimiterSpawns.length());
        }
        stringSpawn2 = strSpawns12;


        while ((index = strSpawns34.find(delimiterSpawns)) != std::string::npos)
        {
            stringSpawn3 = strSpawns34.substr(0, index);

            strSpawns34.erase(0, index + delimiterSpawns.length());
        }
        stringSpawn4 = strSpawns34;


        while ((index = stringSpawn1.find(delimiterTablero)) != std::string::npos)
        {
            spawn1.x = std::stoi(stringSpawn1.substr(0, index));
            stringSpawn1.erase(0, index + delimiterTablero.length());
        }
        spawn1.y = std::stoi(stringSpawn1);


        while ((index = stringSpawn2.find(delimiterTablero)) != std::string::npos)
        {
            spawn2.x = std::stoi(stringSpawn2.substr(0, index));
            stringSpawn2.erase(0, index + delimiterTablero.length());
        }
        spawn2.y = std::stoi(stringSpawn2);


        while ((index = stringSpawn3.find(delimiterTablero)) != std::string::npos)
        {
            spawn3.x = std::stoi(stringSpawn3.substr(0, index));
            stringSpawn3.erase(0, index + delimiterTablero.length());
        }
        spawn3.y = std::stoi(stringSpawn3);


        while ((index = stringSpawn4.find(delimiterTablero)) != std::string::npos)
        {
            spawn4.x = std::stoi(stringSpawn4.substr(0, index));
            stringSpawn4.erase(0, index + delimiterTablero.length());
        }
        spawn4.y = std::stoi(stringSpawn4);


        cantidadNumerosRestantes = totalNum;
        spawns[0] = spawn1;
        spawns[1] = spawn2;
        spawns[2] = spawn3;
        spawns[3] = spawn4;



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

        FILE * tableroLayout;
        char buffer[20];
        int p, myNumber;
        int totalNum = 0;

        tableroLayout = fopen("mapa.txt", "r");
        std::string extractedNumber, currentLine;

        for (int i = 0; i < 9; i++)
        {
            fgets (buffer , 100 , tableroLayout);
            std::string currentLine = buffer;
            for (int j = 0; j < 9; j++)
            {
                p = currentLine.find(",");
                extractedNumber = currentLine.substr(0, p);
                currentLine = currentLine.substr(p + 1);
                myNumber = atoi(extractedNumber.c_str());

                tablero[i][j].numero = myNumber;

                if (myNumber == 0)
                {
                    tablero[i][j].esPared=true;
                }
                else
                {
                    tablero[i][j].esPared=false;
                    totalNum++;
                }
            }
        }

        cantidadNumerosRestantes = totalNum;

        fgets (buffer, 100, tableroLayout);
        currentLine = buffer;

        pos spawn1;
        pos spawn2;
        pos spawn3;
        pos spawn4;

        for (int i = 0; i < 2; i++)
        {
            p = currentLine.find(",");
            std::string extractedPos = currentLine.substr(0, p);
            currentLine = currentLine.substr(p + 1);
            p = extractedPos.find("-");

            if(i == 0){
                spawn1.x = atoi(extractedPos.substr(0, p).c_str());
                spawn1.y = atoi(extractedPos.substr(p + 1, 1).c_str());
            }else{
                spawn2.x = atoi(extractedPos.substr(0, p).c_str());
                spawn2.y = atoi(extractedPos.substr(p + 1, 1).c_str());
            }

        }

        fgets (buffer, 100, tableroLayout);
        currentLine = buffer;

        for (int i = 0; i < 2; i++)
        {
            p = currentLine.find(",");
            std::string extractedPos = currentLine.substr(0, p);
            currentLine = currentLine.substr(p + 1);
            p = extractedPos.find("-");

            if(i == 0){
                spawn3.x = atoi(extractedPos.substr(0, p).c_str());
                spawn3.y = atoi(extractedPos.substr(p + 1, 1).c_str());
            }else{
                spawn4.x = atoi(extractedPos.substr(0, p).c_str());
                spawn4.y = atoi(extractedPos.substr(p + 1, 1).c_str());
            }
        }

        spawns[0] = spawn1;
        spawns[1] = spawn2;
        spawns[2] = spawn3;
        spawns[3] = spawn4;
    }

    casillero ObtenerCasilla(int x, int y)
    {
        return tablero[x][y];
    }

};


#endif // TABLERO_H_INCLUDED
