#pragma once
#include<list>

class Pawn: public std::enable_shared_from_this<Pawn>{
    //any pawn in chess
public:
    enum Color {WHITE, BLACK}; //color of a pawn
    Pawn(const Color col, std::shared_ptr<Board::Square> sq)
        :_color(col), _square(sq), onBoard(true) {}
    Pawn(Pawn& p)
        :_color(p._color) {}
    virtual ~Pawn()=default;

    Color getColor() const //get color of a pawn
        {return _color;}
    std::shared_ptr<Board::Square> getSquare() const //get square on which pawn stands
        {return _square.lock();}

    void putOnSquare(std::shared_ptr<Board::Square> sq) //put pawn on a square
        {_square=sq;}

    virtual char show() const //sign representing given pawn
        {return 'o';}
    void move(std::shared_ptr<Board::Square> destination); //move pawn to destination square
    virtual std::list<std::shared_ptr<Board::Square>> possibleMoves(Board& b)=0; //list moves of a pawn
    void removeFromBoard() {onBoard=false; _square.reset();} //remove pawn from the board
    bool isOnBoard() const {return onBoard;} //is pawn on board
protected:
    const Color _color; //color of a pawn
    std::weak_ptr<Board::Square> _square; //square on which pawn stands
    bool onBoard;
};

std::ostream& operator<<(std::ostream& os, Pawn& pwn);

class King: public Pawn {
public:
    King(const Color col, std::shared_ptr<Board::Square> sq)
        :Pawn(col,sq) {}
    virtual char show() const override //sign representing given pawn
        {return 'K';}
    virtual std::list<std::shared_ptr<Board::Square>> possibleMoves(Board& b) override;
};
class Rook: public Pawn {
public:
    Rook(const Color col, std::shared_ptr<Board::Square> sq)
        :Pawn(col,sq) {}
    virtual char show() const override //sign representing given pawn
        {return 'R';}
    virtual std::list<std::shared_ptr<Board::Square>> possibleMoves(Board& b) override;
};
class Knight: public Pawn {
public:
    Knight(const Color col, std::shared_ptr<Board::Square> sq)
        :Pawn(col,sq) {}
    virtual char show() const override //sign representing given pawn
        {return 'k';}
    virtual std::list<std::shared_ptr<Board::Square>> possibleMoves(Board& b) override;
};