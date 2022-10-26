//
// Created by meibel on 25/10/22.
//

#include <iostream>
#include <SFML/Graphics.hpp>

int main (int argc, char * args[]){

    bool gameOver=false;
    sf::RenderWindow *ventana1;
    ventana1 = new sf::RenderWindow (sf::VideoMode(800,600), "Prueba");

    while(!gameOver)
    {
        ventana1 ->display();


    }


    return 0;
}