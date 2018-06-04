#include "board.hh"
#include "square.hh"
#include "pawn.hh"

char Board::Square::show() const
        {return isOccupied() ? _pawn.lock()->show() : ' ';}
void Board::Square::removePawn() //remove pawn standing on a square
        {_pawn.reset();}
std::ostream& operator<<(std::ostream& os, Board::Square& sq) {
    return os<<sq.show();
}