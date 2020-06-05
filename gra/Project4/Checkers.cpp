#include "Checkers.h"

Checkers::Checkers() {
    side = true;
    player = true;

    window.create(sf::VideoMode(Size, Size), "Checkers Game");

    textures[0].loadFromFile("Board.png");
    sprites[0].setTexture(textures[0]);

    textures[1].loadFromFile("Black_Pawn.png");
    sprites[1].setTexture(textures[1]);

    textures[2].loadFromFile("Black_King.png");
    sprites[2].setTexture(textures[2]);

    textures[3].loadFromFile("White_Pawn.png");
    sprites[3].setTexture(textures[3]);

    textures[4].loadFromFile("White_King.png");
    sprites[4].setTexture(textures[4]);

    textures[5].loadFromFile("Start.png");
    sprites[5].setTexture(textures[5]);

    textures[6].loadFromFile("Won_White.png");
    sprites[6].setTexture(textures[6]);

    textures[7].loadFromFile("Won_Black.png");
    sprites[7].setTexture(textures[7]);

    textures[8].loadFromFile("Draw.png");
    sprites[8].setTexture(textures[8]);
}

bool Checkers::Start()
{
    sprites[5].setPosition(150, 150);
    draw();
    window.draw(sprites[5]);
    window.display();
    sf::Event event;
    while (true)
        if (window.pollEvent(event))
            switch (event.type)
            {
            case sf::Event::Closed:
                return 0;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space) return 1;
            }
}

void Checkers::Play() {
    if (Start())
        while (window.isOpen()) {
            draw();
            window.display();
            if (player) {
                playerMove();

            }
            else
            {
                playerMove();
               // AIMove();
            }
            side = !side;
            player = !player;
            if (End(board.GameState(player))) return;
        }
}


int Checkers::End(int state)
{
    switch (state)
    {
    case 0:
        return 0;
    case -1:
    {
        sprites[8].setPosition(150, 150);
        draw();
        window.draw(sprites[8]);
    }
        break;
    case 1:
    {
        sprites[6].setPosition(150, 150);
        draw();
        window.draw(sprites[6]);
    }
        break;
    case 2:
    {
        sprites[7].setPosition(150, 150);
        draw();
        window.draw(sprites[7]);
    }
        break;
    } 
    window.display();
    sf::Event event;
    while (true)
        if (window.pollEvent(event))
            if (event.type == sf::Event::Closed) return 1;
}

void Checkers::playerMove()
{
    int first, second, Result=0;
    while (Result != 1) {
        if (Result == 0)
        {
            first = mouse();
            if (first == -1) return;
        }
        do
        {
            second = mouse();
            if (second == -1) return;
        }
        while (second == first);
       
        Result = board.move(first / 10, first % 10, second / 10, second % 10, side);
        if (Result == 2)
        {
            first = second;
            draw();
            window.display();
        }
    }
}
void Checkers::AIMove()
{
    auto move = AI::BestMove(7, board,false);
    for (auto& coords : move.coords)
    {
        board.move(coords);
        draw();
        window.display();
    }
}

void Checkers::draw()
{
    window.clear();
    window.draw(sprites[0]);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            switch (board.board[i][j])
            {
            case 1:
            {
                sprites[1].setPosition(j * 100, i * 100);
                window.draw(sprites[1]);
            }
            break;
            case 6:
            {
                sprites[2].setPosition(j * 100, i * 100);
                window.draw(sprites[2]);
            }
            break;
            case 2:
            {
                sprites[3].setPosition(j * 100, i * 100);
                window.draw(sprites[3]);
            }
            break;
            case 7:
            {
                sprites[4].setPosition(j * 100, i * 100);
                window.draw(sprites[4]);
            }
            break;
            }
}

bool Checkers::Events()
{
    sf::Event event;
    while (window.pollEvent(event))
        if (event.type == sf::Event::Closed)
        {
            window.close();
            return true;
        }
    return false;
}

int Checkers::mouse()
{
    sf::Vector2i position;
    while (true)
    {
        if (Events()) return -1;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            position = sf::Mouse::getPosition(window);
            if (position.x > 0 && position.x < 800 && position.y > 0 && position.y < 800) return (position.y - position.y % 100) / 10 + (position.x / 100);
        }
    }
}

