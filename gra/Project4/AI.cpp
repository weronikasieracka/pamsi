#include "AI.h"

Node::Node(int depth, Board board_, bool side_, bool color_, Move move_) {
    color = color_;
    board = board_;
    side = side_;
    move = move_;
    value = 0;
    if (depth == 0 || board.GameState(side) != 0) value = board.AnalyzeBoard(side, color);
    else {
        for (auto& m : board.AvailableMoves(side))
        {
            Board tmp(board);
            tmp.move(m);
            childs.emplace_back(depth - 1, tmp, !side, color, m);
        }
    }
}

Move AI::BestMove(int maxdepth, Board board, bool side) {
    auto root = std::make_unique<Node>(maxdepth, board, side, !side);
    minimax(*root, 0, true, -1000, 1000);
    return root->move;
}

int minimax(Node& node, int depth, bool isMaximizingPlayer, int alpha, int beta) {
    if (node.childs.size() == 0) return node.value;
    int value, bestVal;
    if (isMaximizingPlayer)
    {
        bestVal = -1000;
        for (auto& child : node.childs)
        {
            value = minimax(child, depth + 1, false, alpha, beta);
            bestVal = max(bestVal, value);
            if (bestVal == value && depth == 0) node.move = child.move;
            alpha = max(alpha, bestVal);
            //if (beta <= alpha) break;
        }
        return bestVal;

    }
    else {
        bestVal = 1000;
        for (auto& child : node.childs)
        {
            value = minimax(child, depth + 1, true, alpha, beta);
            bestVal = min(bestVal, value);
            if (bestVal == value && depth == 0) node.move = child.move;
            beta = min(beta, bestVal);
            //if (beta <= alpha) break;
            return bestVal;
        }
    }
}


int max(int a, int b) {return a < b ? b : a;}

int min(int a, int b) { return a < b ? a : b;}
