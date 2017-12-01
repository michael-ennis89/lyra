#ifndef ENGINE_HPP
#define ENGINE_HPP

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<exception>
#include<stdexcept>
#include<limits>

#include "GameData.hpp"
#include "Response.hpp"
#include "parser.hpp"

struct Player {
    std::string name;
    int saves=0;
};

class Game{
public:
    Game();
    ~Game();

    void Run();

private:
    Player player;

    std::string playerName;

    std::vector<Data::Item*> itemsArray;                //Holds items long/short descriptions loaded from files
    std::vector<Data::Interaction*> interactionsArray;  //Holds interactions long/short descriptions loaded from files

    // Game State Variables
    int currentRoom; // Holds the current room returned from parsed command
    int roomsVisited[17][2];   // [0-17] room number   [#][0] = Room visited 0 or 1                [#][1] = Room available 0 or 1)
    int items[8][2];            // [0-7] = item number  [#][0] = 0... n-1 Room or -1 is inventory   [#][1] =  item available 0 or 1.
    int interactions[42][2];    // [0-41] = Interaction [#][0] = 0... n-1 Room                      [#][1] = interaction available 0 or 1


    // Phase 1 Logic & Print Functions
    bool moveLogicCheck(int nextRoom) const;        // Checks if game logic is ok to move to next room.
    void printExit(Data::Room *userRoom);           // Prints the short exit if available.
    void printEntrance(Data::Room *userRoom);       // Prints the correct version of entrance description.
    void printInteractions();                       // prints all short description interactions available in room.
    void printItems(int disreguard);                // prints non-interaction short item descriptions. can pass item number to disregard.

    // Phase 2 Logic & Print Functions
    void printConnections();                                // Prints all the connections available in phase 2
    void printRoomData(Data::Room *userRoom, int choice);   // Prints out the selected room data in phase 2.
    bool moveLogicPhaseTwo(int nextRoom);                   // Checks if game logic is ok to move to a selected room in phase 2.
    void hardCodedDescriptions(int choice);                 // Extra descriptions not in data files. used for room destructions etc.
    int canMove = 0;                                        // decides whether to print moves available or not.
    int dontPrint = 0;                                      // replaces canMove;

    int startGame(); //Returns 1=New Game, 2=load Game

    //Initialization
    bool Initialize(int option);//Initialize all variables and return true if it's initialized correctly (option 1=New Game, 2=load Game)
    bool loadDefault();         //Load all game state variables from a default file which is just like a save file, but holds default values and never changes
    bool loadFromFile(const std::string& fileName, const bool& isDefault=false);        //Load all game state variables from a save file

    //Save
    bool saveGame(const std::string& saveName);      //Save game state to a file

	//Display ART
	void displayArt();
	void displayAvada();
	void displayStupefy();
	void displayImperio();
	void displayErecto();
	void displayExpelliarmus();
	void displayCredits();

};


#endif // ENGINE_HPP
