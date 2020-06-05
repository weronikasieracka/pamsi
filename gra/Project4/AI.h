#pragma once
#include <vector>
#include <memory>
#include "board.h"

class Node {
public:
    Board board;
    Move move;
    std::vector< Node > childs{};
    bool color;
    bool side;
    int value;

    Node(int depth, Board board_, bool side_, bool color_, Move move_ = Move(0, 0, 0, 0));
};

class AI {
    AI() {}
public:
    static Move BestMove(int maxdepth, Board board, bool side);
};

int max(int a, int b);
int min(int a, int b);
int minimax(Node& node, int depth, bool isMaximizingPlayer, int alpha, int beta);
