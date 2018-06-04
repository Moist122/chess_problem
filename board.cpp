#include<cmath>
#include <algorithm>
#include <string>

#include "board.hh"
#include "square.hh"
#include "pawn.hh"

Board::Board() {
    char s='A';
    for(char i=board_size-1;i>=0;--i)
        for(char j=0;j<board_size;++j) {
            char x = 'A'+j;
            char y = '1'+i;
            _squares[i][j] = std::make_shared<Square>(x,y,s++);
        }
}

std::shared_ptr<Board::Square> Board::operator()(const char x, const char y) {
    if(comp(x_boundries[0],x,x_boundries[1])&&comp(y_boundries[0],y,y_boundries[1]))
        return _squares[y-'1'][x-'A'];
    return nullptr;
}
/*
bool Checkers::Board::areDiagonal(Checkers::Square* a, Checkers::Square* b)
    {return std::abs(a->getX()-b->getX())==std::abs(a->getY()-b->getY());}

char Checkers::Board::distance(Checkers::Square* a, Checkers::Square* b) {
    return std::max(std::abs(a->getX()-b->getX()),std::abs(a->getY()-b->getY()));}

char Checkers::Board::howManyPawnsBetween(Checkers::Square* a, Checkers::Square* b) {
    if(distance(a,b)<=1) return 0;
    char directionX= (b->getX()-a->getX()) / (distance(a,b));
    char directionY= (b->getY()-a->getY()) / (distance(a,b));
    char x=a->getX()+directionX;
    char y=a->getY()+directionY;
    char counter = 0;
    for(x,y;x!=b->getX()&&y!=b->getY();x+=directionX,y+=directionY)
        if((*this)(x,y)->isOccupied()) counter++;
    return counter;
}

Checkers::Pawn* Checkers::Board::pawnBetween(Checkers::Square* a, Checkers::Square* b) {
    char directionX= (b->getX()-a->getX()) / (distance(a,b));
    char directionY= (b->getY()-a->getY()) / (distance(a,b));
    char x=a->getX()+directionX;
    char y=a->getY()+directionY;
    for(x,y;x!=b->getX()&&y!=b->getY();x+=directionX,y+=directionY)
        if((*this)(x,y)->isOccupied()) return (*this)(x,y)->getPawn();
    return nullptr;
}*/

std::ostream& operator<<(std::ostream& os, Board& b) {
    os<<"  ";
    for(char i=x_boundries[0];i<=x_boundries[1];++i)
        os<<i<<' ';
    os<<"\n "<<std::string(2*board_size+1,'-')<<'\n';
    for(char y=y_boundries[1];y>=y_boundries[0];--y) {
        os<<y;
        for(char x=x_boundries[0];x<=x_boundries[1];++x)
            os<<'|'<<*b(x,y);
    os<<'|'<<y<<"\n "<<std::string(2*board_size+1,'-')<<'\n';
    }
    os<<"  ";
    for(char i=x_boundries[0];i<=x_boundries[1];++i)
        os<<i<<' ';
    return os<<std::endl;
}