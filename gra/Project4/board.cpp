#include "board.h"

Board::Board()
{
    Draw = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (i % 2 != j % 2)
                if (i < 3) board[i][j] = 1;
                else if (i > 4) board[i][j] = 2;
                else board[i][j] = 0;
            else board[i][j] = 0;
}

int Board::move(int x1, int y1, int x2, int y2, bool color)
{
    if ((color && (board[x1][y1] == 1 || board[x1][y1] == 6)) || (!color && (board[x1][y1] == 2 || board[x1][y1] == 7))) return 0;
    bool captured = false;
    for (auto& move : AvailableMoves(x1, y1))
    {
        if (move == Move(x1, y1, x2, y2))
        {
            if (PossibleCapture(color))
            {
                capture(x1, y1, x2, y2);
                captured = true;
            }
            board[x2][y2] = board[x1][y1];
            board[x1][y1] = 0;
            if (captured && PossibleCapture(x2, y2)) return 2;
                else if ((!color && x2 == 7) || (color && x2 == 0)) board[x2][y2] = color ? 7 : 6;
            return 1;
        }
    }
    return 0;
}

int Board::move(Coords c)
{
    bool color = (board[c.x1][c.y1] == 1 || board[c.x1][c.y1] == 6) ? 0 : 1;
    return move(c.x1, c.y1, c.x2, c.y2, color);
}

int Board::move(Move m)
{
    bool color = (board[m.coords[0].x1][m.coords[0].y1] == 1 || board[m.coords[0].x1][m.coords[0].y1] == 6) ? 0 : 1;
    int i = 0;
    while (move(m.coords[i]) == 2)  i++;
    return 1;
}

void Board::capture(int x1, int y1, int x2, int y2)
{
    int a = (x1 < x2) ? 1 : -1;
    int b = (y1 < y2) ? 1 : -1;
    for (int i = x1 + a, j = y1 + b; i != x2, j != y2; i += a, j += b)
        board[i][j] = 0;
}

bool Board::PossibleCapture(int x, int y)
{
    bool color = (board[x][y] == 1 || board[x][y] == 6) ? 0 : 1;
    if (board[x][y] == 1 || board[x][y] == 2)
        for (int a : {-1, 1})
            for (int b : {-1, 1})
            {
                int i = x + a;
                int j = y + b;
                if (i + a >= 0 && i + a < 8 && j + b >= 0 && j + b < 8)
                {
                    if (color) {if ((board[i][j] == 1 || board[i][j] == 6) && board[i + a][j + b] == 0) return true;}
                        else  if ((board[i][j] == 2 || board[i][j] == 7) && board[i + a][j + b] == 0) return true;
                }
            }
    else if (board[x][y] == 6 || board[x][y] == 7)
        for (int a : {-1, 1})
            for (int b : {-1, 1})
            {
                int i = x + a;
                int j = y + b;
                while (i + a < 8 && i + a >= 0 && j + b < 8 && j + b >= 0)
                {
                    if (color)
                    {
                        if (board[i][j] == 2 || board[i][j] == 7) break;
                        if (board[i][j] == 1 || board[i][j] == 6)
                        {
                            if (board[i + a][j + b] == 0) return true;
                                else break;
                        }
                    }
                    else 
                    {
                        if (board[i][j] == 1 || board[i][j] == 6) break;
                        if (board[i][j] == 2 || board[i][j] == 7)
                        {
                            if (board[i + a][j + b] == 0)  return true;
                                else break;
                        }
                    }
                    i += a;
                    j += b;
                }
            }
    return false;
}

bool Board::PossibleCapture(bool color)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (color) {if ((board[i][j] == 2 || board[i][j] == 7) && PossibleCapture(i, j)) return true; }
                else if ((board[i][j] == 1 || board[i][j] == 6) && PossibleCapture(i, j))  return true;
    return false;
}

std::vector< Move > Board::AvailableMoves(bool color)
{
    std::vector< Move > moves;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (color)
            {
                if (board[i][j] == 2 || board[i][j] == 7)
                {
                    auto tmp = AvailableMoves(i, j);
                    for (auto& m : tmp)
                    {
                        auto tmp2 = Sequense(m, *this);
                        moves.insert(moves.end(), tmp2.begin(), tmp2.end());
                    }
                }
            }
            else if (board[i][j] == 1 || board[i][j] == 6)
            {
                auto tmp = AvailableMoves(i, j);
                for (auto& m : tmp)
                {
                    auto tmp2 = Sequense(m, *this);
                    moves.insert(moves.end(), tmp2.begin(), tmp2.end());
                }
            }
    return moves;
}

std::vector< Move > Board::AvailableMoves(int x, int y)
{
    bool color;
    std::vector< Move > moves;
    if (board[x][y] == 0) return moves;
    if (board[x][y] == 1 || board[x][y] == 6) color = 0;
         else color = 1;
    if (PossibleCapture(color) != PossibleCapture(x, y)) return moves;
    if (board[x][y] == 1 || board[x][y] == 2)
    {
        if (!PossibleCapture(x, y))
        {
            int xdir = color ? -1 : 1;
            if (y < 7 && board[x + xdir][y + 1] == 0) moves.push_back(Move(x, y, x + xdir, y + 1));
            if (y > 0 && board[x + xdir][y - 1] == 0) moves.push_back(Move(x, y, x + xdir, y - 1));
        }
        else
            for (int a : {-1, 1}) 
                for (int b : {-1, 1})
                {
                    int i = x + a;
                    int j = y + b;
                    if (i + a < 8 && i + a >= 0 && j + b < 8 && j + b >= 0)
                    {
                        if (color) {if ((board[i][j] == 1 || board[i][j] == 6) && board[i + a][j + b] == 0) moves.push_back(Move(x, y, i + a, j + b));}
                             else if ((board[i][j] == 2 || board[i][j] == 7) && board[i + a][j + b] == 0) moves.push_back(Move(x, y, i + a, j + b));
                    }
                }
    }
    else {
        bool captured = PossibleCapture(x, y);
        for (int a : {-1, 1})
            for (int b : {-1, 1})
            {
                int i = x + a;
                int j = y + b;
                while (i >= 0 && j >= 0 && i <= 7 && j <= 7)
                {
                    if (board[i][j] == 0) {if (!captured)  moves.push_back(Move(x, y, i, j));}
                    else if (color) {
                        if (board[i][j] == 2 || board[i][j] == 7) break;
                          else if ((board[i][j] == 1 || board[i][j] == 6) && captured)
                          {
                            while (true)
                            {
                                i += a;
                                j += b;
                                if (i >= 0 && j >= 0 && i <= 7 && j <= 7)
                                {
                                    if (board[i][j] == 0)  moves.push_back(Move(x, y, i, j));
                                    else break;
                                }
                                else break;
                            }
                            break;
                          }
                         else break;
                    }
                    else {
                        if (board[i][j] == 1 || board[i][j] == 6) break;
                        if ((board[i][j] == 2 || board[i][j] == 7) && captured)
                        {
                            while (true)
                            {
                                i += a;
                                j += b;
                                if (i >= 0 && j >= 0 && i <= 7 && j <= 7)
                                {
                                    if (board[i][j] == 0) moves.push_back(Move(x, y, i, j));
                                    else break;
                                }
                                else break;
                            }
                            break;
                        }
                        else  break;
                    }
                    i += a;
                    j += b;
                }
            }
    }
    return moves;
}

std::vector< Move > Board::Sequense(Move move, Board b)
{
    std::vector< Move > moves;
    if (b.move(move.coords[0]) == 1) moves.emplace_back(move.coords[0]);
    else
    {
        for (auto& m : b.AvailableMoves(move.coords[0].x2, move.coords[0].y2))
        {
            std::vector< Move > tmp = Sequense(m, b);
            moves.insert(moves.end(), tmp.begin(), tmp.end());
        }
        for (auto& m : moves)
            m.add(move.coords[0]);
        return moves;
    }
}


int Board::AnalyzeBoard(bool color, bool side)
{
    switch (GameState(color))
    {
    case -1:
        return 0;
    case 0:
        break;
    case 1:
        return side ? -1000 : 1000;
    case 2:
        return side ? 1000 : -1000;
    }
    int white = 0, black = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j] == 1 || board[i][j] == 6) black += AnalyzeField(i, j);
            else if (board[i][j] != 0) white += AnalyzeField(i, j);
    if (side) return white - black;
    else return black - white;
}

int Board::AnalyzeField(int x, int y)
{
    int score = 0;
    switch (board[x][y]) {
    case 0:
        break;
    case 1:
    {
        score += 10;
        if (y < 2 || y > 5) {
            score++;
            if (y < 1 || y > 6) score++;
        }
        score += 15;
    }
    break;
    case 2:
    {
        score += 10;
        if (y < 2 || y > 5) {
            score++;
            if (y < 1 || y > 6) score++;
        }
        score += 15;
    }
    break;
    case 6:
    {
        score += 20;
        if (y < 2 || y > 5) {
            score++;
            if (y < 1 || y > 6) score++;
        }
        score += 15;
    }
    break;
    case 7:
    {
        score += 20;
        if (y < 2 || y > 5) {
            score++;
            if (y < 1 || y > 6) score++;
        }
        score += 15;
    }
    break;
    }
    return score;
}


int Board::GameState(bool color)
{
    int blackPawns_=0, blackKings_ = 0, whitePawns_=0, whiteKings_=0;
    bool blackMoves=false, whiteMoves=false;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            switch (board[i][j])
            {
            case 0:
                break;
            case 1:
            {
                blackPawns_++;
                if (!blackMoves && AvailableMoves(i, j).size() != 0) blackMoves = true;
            }
                break;
            case 2:
            {
                whitePawns_++;
                if (!whiteMoves && AvailableMoves(i, j).size() != 0) whiteMoves = true;
            }
                break;
            case 6:
            {
                blackKings_++;
                if (!blackMoves && AvailableMoves(i, j).size() != 0) blackMoves = true;
            }
                break;
            case 7:
            {
                whiteKings_++;
                if (!whiteMoves && AvailableMoves(i, j).size() != 0) whiteMoves = true;
            }
                break;
            }
    if ((whitePawns_ || whiteKings_) && (blackPawns_ || blackKings_) && ((color && whiteMoves) || (!color && blackMoves))) {
        if (whiteKings_ && blackKings_ && whitePawns_ == whitePawns && blackPawns_ == blackPawns && whiteKings_ == whiteKings && blackKings_ == blackKings)
        {
            if (++Draw == 30) return -1;
                else Draw = 0;
        }
        whitePawns = whitePawns_;
        blackPawns = blackPawns_;
        whiteKings = whiteKings_;
        blackKings = blackKings_;
        return 0;
    }
    else if ((!whitePawns_ && !whiteKings_) || (color && !whiteMoves)) return 2;
         else if ((!blackPawns_ && !blackKings_) || (!color && !blackMoves)) return 1;
}

Move::Move(int x1, int y1, int x2, int y2) { coords.emplace_back(x1, y1, x2, y2); }
Move::Move(Coords c) { coords.push_back(c); }
void Move::add(Coords c) { coords.insert(coords.begin(), c); }
bool Move::operator== (const Move& Board)
{
    if (this->coords.size() != Board.coords.size()) return false;
    else for (int i = 0; i < coords.size(); i++)
        if (this->coords[i] != Board.coords[i])
            return false;
    return true;
}

Coords::Coords(int x12, int y12, int x22, int y22) { x1 = x12; y1 = y12; x2 = x22; y2 = y22; }
bool Coords::operator!= (const Coords& Board)
{
    if (this->x1 != Board.x1 || this->y1 != Board.y1 || this->x2 != Board.x2 || this->y2 != Board.y2) return true;
    return false;
}

