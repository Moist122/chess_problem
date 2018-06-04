#pragma once

#include<vector>
#include <memory>

#include "board.hh"
#include "square.hh"
#include "pawn.hh"

struct Problem { //chess problem
    Board b; //chess board
    //used pawns
    std::shared_ptr<King> king;
    std::shared_ptr<Rook> rook;
    std::shared_ptr<Knight> knight;
public:
    Problem() //create problem
    :king(new King(Pawn::BLACK, b('C','4'))),
    rook(new Rook(Pawn::BLACK, b('A','5'))),
    knight(new Knight(Pawn::WHITE, b('C','1'))){
        b('C','4')->putPawn(king);
        b('A','5')->putPawn(rook);
        b('C','1')->putPawn(knight);
    }
    friend std::ostream& operator<<(std::ostream& os, Problem& p) {
        return os<<p.b;
    }
};

