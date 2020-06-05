#pragma once
#include <vector>
#include <cmath>

struct Coords {
    int x1, y1, x2, y2;
    Coords(int x1_, int y1_, int x2_, int y2_);
    bool operator!= (const Coords& B);
};

struct Move {
    std::vector<Coords> coords;
    Move() {}
    bool operator== (const Move& B);
    Move(int x1, int y1, int x2, int y2);
    Move(Coords c);
    void add(Coords c);
};


class Board {
public:
    /* Board - variables
    Empty - 0
    Black pawn - 1
    White pawn - 2
    Black King - 6
    White King - 7
    */
    int board[8][8];
    int Draw, blackPawns, blackKings, whitePawns, whiteKings;

    Board();
    int move(int x1, int y1, int x2, int y2, bool color);
    int move(Move m);
    int move(Coords m);

    std::vector<Move> AvailableMoves(int x, int y);
    std::vector<Move> AvailableMoves(bool color);
    std::vector<Move> Sequense(Move move, Board b);

    void capture(int x1, int y1, int x2, int y2);
    bool PossibleCapture(int x, int y);
    bool PossibleCapture(bool color);

    int AnalyzeBoard(bool color, bool side);
    int AnalyzeField(int x, int y);
    int GameState(bool color);
};
