#include<iostream>
#include<memory>

#include "board.hh"
#include "square.hh"
#include "pawn.hh"
#include "problem.hh"
#include "solutions.hh"

using namespace std;

int main() {
    Problem p;
    cout<<p<<endl<<"DFS:\n";
    DFS dfs(p);
    cout<<"Visited:\n";
    for(auto c: dfs.found)
        cout<<c<<endl;
    cout<<endl;
    cout<<"Route to king:\n";
    for(auto c: dfs.route)
        cout<<c;
    cout<<endl;

    Problem p2;
    cout<<p2<<"A*\n";
    Astar as(p2);
    cout<<"Found:\n";
    for(auto c: as.found)
        cout<<get<0>(c)<<" f="<<get<1>(c)<<" g="<<get<2>(c)<<" h="<<get<3>(c)<<endl;
    cout<<endl;
    cout<<"Route to king:\n";
    for(auto c: as.route)
        cout<<c;
    cout<<endl;
    return 0;
}