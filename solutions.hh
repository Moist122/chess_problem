#pragma once

#include<vector>
#include<unordered_map>
#include<map>
#include <tuple>
#include"problem.hh"
struct DFS{ //depth first search for a way to beat the king
    std::vector<char> route; //found route to king
    std::vector<char> found; //visited nodes
    DFS(Problem& problem) {
        std::unordered_map<char, bool> visited;
        for(char i='A';i<'Z';++i)
            visited[i] = false;
        std::vector<std::shared_ptr<Board::Square>> toVisit;
        std::unordered_map<char,std::vector<char>> routeToSquare;
        char current = problem.knight->getSquare()->getSymbol();
        routeToSquare[current].push_back(current);
        auto rookMoves = problem.rook->possibleMoves(problem.b);
        std::unordered_map<std::shared_ptr<Board::Square>,bool> rookDanger;
        for(auto mv: rookMoves)
            rookDanger[mv] = true;
        char target = problem.king->getSquare()->getSymbol();
        visited[current] = true;
        found.push_back(current);
        while(!visited[target]) {
            bool rookOnBoard = true;
            for(auto sq: routeToSquare[current])
                if(sq==problem.rook->getSquare()->getSymbol())  rookOnBoard = false;
            for(auto mv:problem.knight->possibleMoves(problem.b)) {
                char symbol = mv->getSymbol();
                if(!visited[symbol]&&\
                (!rookOnBoard||!rookDanger[mv])) {
                    toVisit.push_back(mv);
                routeToSquare[symbol] = routeToSquare[current];
                routeToSquare[symbol].push_back(symbol);}
            }
            while(visited[toVisit.back()->getSymbol()]) toVisit.pop_back();
            if(!toVisit.empty()) {
                problem.knight->move(toVisit.back());
                toVisit.pop_back();
            }
            else break;
            current = problem.knight->getSquare()->getSymbol();
            found.push_back(current);
            visited[current] = true;
        }
        route = routeToSquare[target];
    }
};

struct Astar{ //A* search for solution for a problem
    std::vector<char> route; //route to king found
    std::vector<std::tuple<char,int,int,int>> found; //found (square, f,g,h)
    std::map<std::shared_ptr<Board::Square>,int> f, g, h; //f g h values of nodes
    Astar(Problem& problem) {
        std::unordered_map<char, bool> visited;
        for(char i='A';i<'Z';++i)
            visited[i] = false;
        std::list<std::shared_ptr<Board::Square>> toVisit;
        std::unordered_map<char,std::vector<char>> routeToSquare;
        auto current = problem.knight->getSquare();
        routeToSquare[current->getSymbol()].push_back(current->getSymbol());
        auto rookMoves = problem.rook->possibleMoves(problem.b);
        std::unordered_map<std::shared_ptr<Board::Square>,bool> rookDanger;
        for(auto mv: rookMoves)
            rookDanger[mv] = true;
        auto target = problem.king->getSquare();
        visited[current->getSymbol()] = true;
        for(char i='A';i<'F';++i)
        for(char j='1';j<'6';++j){
            g[problem.b(i,j)] = 1000;
            h[problem.b(i,j)] = abs(i-target->getX())+abs(j-target->getY());
            f[problem.b(i,j)] = g[problem.b(i,j)] + h[problem.b(i,j)];
        }
        g[current] = 0;
        f[current] = g[current]+h[current];
        found.push_back(std::make_tuple(current->getSymbol(),f[current],g[current],h[current]));
        while(!visited[target->getSymbol()]) {
            bool rookOnBoard = true;
            for(auto sq: routeToSquare[current->getSymbol()])
                if(sq==problem.rook->getSquare()->getSymbol())  rookOnBoard = false;
            for(auto mv:problem.knight->possibleMoves(problem.b)) {
                char symbol = mv->getSymbol();
                if(visited[symbol]||(rookOnBoard&&rookDanger[mv])) continue;
                bool inList = false;
                for(auto vis: toVisit)
                    if(vis->getSymbol() == symbol) inList = true;
                if(!inList)
                    toVisit.push_back(mv);
                int newG = g[current] + 3;
                if(newG>=g[mv]) continue;
                routeToSquare[symbol] = routeToSquare[current->getSymbol()];
                routeToSquare[symbol].push_back(symbol);
                g[mv] = newG;
                f[mv] = g[mv] + h[mv];
                found.push_back(std::make_tuple(mv->getSymbol(),f[mv],g[mv],h[mv]));
            }
            if(!toVisit.empty()) {
                auto nextMv = toVisit.front();
                for(auto mv:toVisit){
                    if(!visited[mv->getSymbol()]) {
                        if(f[mv]<f[nextMv]) nextMv = mv;
                        else if(f[mv]==f[nextMv]&&mv->getSymbol()<nextMv->getSymbol())
                            nextMv = mv;
                    }
                }
                problem.knight->move(nextMv);
                toVisit.remove(nextMv);
            }
            else break;
            current = problem.knight->getSquare();
            visited[current->getSymbol()] = true;
        }
        route = routeToSquare[target->getSymbol()];
    }
};