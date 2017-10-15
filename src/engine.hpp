#ifndef ENGINE_H
#define ENGINE_H

#include "GameData.hpp"
#include "inventory.hpp"
#include "Response.hpp"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<exception>
#include<limits>

class Game{
public:
    Game();
    ~Game();

    void Run();

private:
    std::string playerName;

    std::vector<Data::Item*> itemsArray;                //Holds items long/short descriptions loaded from files
    std::vector<Data::Interaction*> interactionsArray;  //Holds interactions long/short descriptions loaded from files

    // Game State Variables
    int currentRoom;           // Holds the current room returned from parsed command
    bool roomsVisited[17][2];   // [#][0] Holds what rooms have been visited before ([#][1] = Room Destroyed or not)
    int items[8][2];            // [0-7] = item number [*][0... n-1 Room or -1 = in inventory] = Location  [*][1] =  item available 0 or 1.
    int interactions[34][2];    // [0-33] = Interaction Number [*][0 ... n-1] = Room Number Location [*][1] = interaction available 0 or 1

    bool moveLogicCheck(int currentRoom, int nextRoom) const;

    int startGame(); //Returns 1=New Game, 2=load Game

    //Initialization
    bool Initialize(int option);//Initialize all variables and return true if it's initialized correctly (option 1=New Game, 2=load Game)
    void loadDefault();         //Load all game state variables from a default file which is just like a save file, but holds default values and never changes
    void loadFromFile(const std::string& fileName);        //Load all game state variables from a save file

    bool saveGame() const;      //Save game state to a file

};


#endif // ENGINE_H
