#ifndef ENGINE_H
#define ENGINE_H

#include "GameData.hpp"
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
    int currentRoom; // Holds the current room returned from parsed command
    bool roomsVisited[17][2];   // [0-17] room number   [#][0] = Room visited 0 or 1                [#][1] = Room available 0 or 1)
    int items[8][2];            // [0-7] = item number  [#][0] = 0... n-1 Room or -1 is inventory   [#][1] =  item available 0 or 1.
    int interactions[34][2];    // [0-33] = Interaction [#][0] = 0... n-1 Room                      [#][1] = interaction available 0 or 1

    // Phase 1 Logic & Print Functions
    bool moveLogicCheck(int nextRoom) const;        // Checks if game logic is ok to move to next room.
    void printExit(Data::Room *userRoom);           // Prints the short exit if available.
    void printEntrance(Data::Room *userRoom);       // Prints the correct version of entrance description.
    void printInteractions();                       // prints all short description interactions available in room.
    void printItems(int disreguard);                // prints non-interaction short item descriptions. can pass item number to disregard.

    int startGame(); //Returns 1=New Game, 2=load Game

    //Initialization
    bool Initialize(int option);//Initialize all variables and return true if it's initialized correctly (option 1=New Game, 2=load Game)
    void loadDefault();         //Load all game state variables from a default file which is just like a save file, but holds default values and never changes
    void loadFromFile(const std::string& fileName);        //Load all game state variables from a save file

    //Save
    bool saveGame() const;      //Save game state to a file

};


#endif // ENGINE_H
