#pragma once
#include <memory>
#include <iostream>

#include "comparators.hh"

constexpr char board_size=5; //board is square board_size x board_size
constexpr char x_boundries[]={'A','A'+board_size-1}; //boundries of x coordinates on board
constexpr char y_boundries[]={'1','1'+board_size-1}; //boundries of y coordinates on board
constexpr char x_graphic_array = 2*board_size+6; //size of char array representing board graphicly
constexpr char y_graphic_array = 2*board_size+3;

class Board {
    //board as an array of squares with coordinates
public:
    Board();
    class Square;

    std::shared_ptr<Square> operator()(const char x, const char y);
        //get square with coordinates x y
    bool onBoard(char x, char y) const //check if coordinates represent a square
        {return comp(x_boundries[0],x,x_boundries[1])&&comp(y_boundries[0],y,y_boundries[1]);}
    //bool areDiagonal(Square* a, Square* b); //check if squares are diagonal
    //char distance(Square* a, Square* b); //check distance between diagonal squares
    //Pawn* pawnBetween(Square* a, Square* b); //get pawn between 2 squares
    //char howManyPawnsBetween(Square* a,Square* b);
        //count pawns between 2 squares (exluding these squares)

    friend std::ostream& operator<<(std::ostream& os, Board& b); //show board

private:
    std::shared_ptr<Square> _squares[board_size][board_size]; //array of squares forming a board
    Between comp; // to check if coordinates are part of the board
};