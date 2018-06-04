#pragma once

class Pawn;

class Board::Square {
    //square as a part of the board
public:
    Square(const char x, const char y, const char s)
        :coordinate_x(x), coordinate_y(y), symbol(s) {}
    
    bool isOccupied() const //check if there is a pawn on a square
        {return _pawn.use_count();}
    std::shared_ptr<Pawn> getPawn() const //get pawn standing on a square
        {return _pawn.lock();}
    const char getX() const //get x coordinate of a square A-...
        {return coordinate_x;}
    const char getY() const //get y coordinate of a square 1-...
        {return coordinate_y;}
    const char getSymbol() const //get y coordinate of a square 1-...
        {return symbol;}
    
    void putPawn(std::shared_ptr<Pawn> p) //put pawn on a square
        {_pawn = p;}
    void removePawn(); //remove pawn standing on a square

    char show() const;
private:
    const char coordinate_x; //first coordinate of a square
    const char coordinate_y; //second coordinate of a square
    const char symbol; //letter symbol on 5x5 board
    std::weak_ptr<Pawn> _pawn; //pawn stending on a square (nullptr if square is empty)
};

std::ostream& operator<<(std::ostream& os, Board::Square& sq);