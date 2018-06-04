#include "board.hh"
#include "square.hh"
#include "pawn.hh"

std::ostream& operator<<(std::ostream& os, Pawn& pwn) {
    return os<<pwn.show();
}

std::list<std::shared_ptr<Board::Square>> King::possibleMoves(Board& b) {
    std::list<std::shared_ptr<Board::Square>> result;
    if(!isOnBoard()) return result;
    char x = _square.lock()->getX();
    char y = _square.lock()->getY();
    char mvs[][2]={{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};
    for(auto mv: mvs){
        if(b.onBoard(x+mv[0],y+mv[1]))
            result.push_back(b(x+mv[0],y+mv[1]));
    }
    return result;
}
std::list<std::shared_ptr<Board::Square>> Rook::possibleMoves(Board& b) {
    std::list<std::shared_ptr<Board::Square>> result;
    if(!isOnBoard()) return result;
    char x = _square.lock()->getX();
    char y = _square.lock()->getY();
    char mvs[][2]={{1,0},{0,-1},{-1,0},{0,1}};
    for(auto mv: mvs){
        for(int multiplier=1;multiplier<board_size;++multiplier) {
            if(b.onBoard(x+mv[0]*multiplier,y+mv[1]*multiplier))
                result.push_back(b(x+mv[0]*multiplier,y+mv[1]*multiplier));
            else break;
        }
    }
    return result;
}
std::list<std::shared_ptr<Board::Square>> Knight::possibleMoves(Board& b) {
    std::list<std::shared_ptr<Board::Square>> result;
    if(!isOnBoard()) return result;
    char x = _square.lock()->getX();
    char y = _square.lock()->getY();
    char mvs[][2]={{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1},{2,1},{1,2}};
    for(auto mv: mvs){
        if(b.onBoard(x+mv[0],y+mv[1]))
            result.push_back(b(x+mv[0],y+mv[1]));
    }
    return result;
}
void Pawn::move(std::shared_ptr<Board::Square> destination) {
    _square.lock()->removePawn();
    if(destination->isOccupied()){
        //destination->getPawn()->removeFromBoard();
        destination->removePawn();
    }
    putOnSquare(destination);
    destination->putPawn(shared_from_this());
}