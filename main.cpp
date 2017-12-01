#include "./src/engine.hpp"
#include "./src/Response.hpp"
#include "./src/parser.hpp"
#include "./src/GameData.hpp"

#include<vector>
#include<string>
#include<fstream>
#include<iostream>


int main() {

    Game *myGame;
    myGame = new Game();
    myGame->Run();

    //Call destructor
    delete myGame;

    return 0;

}

