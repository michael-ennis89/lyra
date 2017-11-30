#include<vector>
#include<string>
#include<fstream>
#include<iostream>

#include "../src/GameData.hpp"
#include "../src/engine.hpp"
#include "../src/Response.hpp"
#include "../src/parser.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif // defined

int main() {

    Game *myGame;
    myGame = new Game();
    myGame->Run();

    //Call destructor
    delete myGame;
    return 0;
}

