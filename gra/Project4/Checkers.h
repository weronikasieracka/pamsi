#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "board.h"
#include "AI.h"

const int Size = 800;

class Checkers {
    sf::RenderWindow window;
    sf::Texture textures[9];
    sf::Sprite sprites[9];

    Board board;
    bool player;
    bool side;
public:
    Checkers();
    void Play();
    bool Start();
    int End(int state);

    bool Events();
    int mouse();
    void draw();

    void playerMove();
    void AIMove();
    
};

