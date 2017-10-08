#include "/data/Room.hpp"
#include "/data/Inventory.hpp"
#include "/data/Response.hpp"

#include <iostream>

// Function Prototypes
int startGame();
void newGame(bool *visit, int *items, int *interactions, int *current);
void savedGame(bool *visit, int *items, int *interactions, int *current);
bool moveLogicCheck(int currentRoom, int nextRoom);

int main(){

    // Temp Variables
    bool voldermortAlive = true;
    bool movedRooms;
    bool moveLogic;
    int initType;               // Holds what type of game to initialize
    std::string userCommand;    // Holds user commands
    Response *parsedResponse;   // Holds parsed response from parser

    // Game State Variables
    int *currentRoom;           // Holds the current room returned from parsed command
    bool roomsVisited[17];      // Holds what rooms have been visited before
    int items[8][2];            // [0-7] = item number [*][0... n-1 Room or -1 = in inventory] = Location  [*][1] =  item available 0 or 1.
    int interactions[34][2]     // [0-33] = Interaction Number [*][0 ... n-1] = Room Number Location [*][1] = interaction available 0 or 1


    initType = startGame();
    if(initType == 1)
    {
        newGame(roomsVisited, items, interactions, currentRoom);
    }
    else
    {
        savedGame(roomsVisited, items, interactions, currentRoom);
    }

    do{
         switch(currentRoom)
         {
         case 0:        // Harry's House
            {
                break;
            }
         case 1:        // Weasley's House
            {
                break;
            }
         case 2:        // London Diner
            {
                break;
            }
         case 3:        // Safe House
            {
                break;
            }
         case 4:        // HeadQuarters
            {
                break;
            }
         case 5:        // Forest
            {
                break;
            }
         case 6:        // Godric Hallow
            {
                break;
            }
         case 7:        // Malfloy Manor
            {
                break;
            }
         case 8:        // Beach House
            {
                break;
            }
         case 9:        // Gringot Bank
            {
                break;
            }
         case 10:       // Hogsmeade
            {
                break;
            }
         case 11:       //Room of Requirement
            {
                break;
            }
         case 12:       // Ravenclaw Tower
            {
                break;
            }
         case 13:       // Courtyard
            {
                break;
            }
         case 14:       // Boat House
            {
                break;
            }
         case 15:       // Great Hall
            {
                break;
            }
         case 16:       // Enchanted Forest
            {
                break;
            }
         }

         std::cout >> ">>";
         std::cin >> userCommand;
         parsedResponse = parseCommand(userCommand);

         if(parsedResponse->command == -1)
         {
             std::cout << "Invalid Command, Please Try Again." << std::endl;
             movedRooms = false;
         }

         if(parsedResponse->command == 1)               // Basic Command
         {
             if(parsedResponse->option == 1)            // look Command
             {

             }
             else if(parsedResponse->option == 2)       // help Command
             {

             }
             else if(parsedResponse->option == 3)       // inventory Command
             {

             }
             else if(parsedResponse->option == 4)       // save & quit game Command
             {

             }
             else
             {

             }
         }

         if(parsedResponse->command == 2)               // Move Command
         {
                moveLogic = moveLogicCheck(currentRoom, parsedResponse->room);

                if(moveLogic == true)
                {
                    currentRoom = parsedResponse->room;
                    movedRooms = true;
                }
                else
                {
                    std::cout << "Invalid Command, Please Try Again." << std::endl;
                    movedRooms = false;
                }
         }

         if(parsedResponse->command == 3)               // Interaction Command
         {
             if(parsedResponse->option == 1)            // look at <item or interaction>
             {
                 if((items[parsedResponse.item].location == currentRoom) && (items[parsedResponse.item].available == true))
                 {
                     //print item[parsedResponse.item].longDescription
                     movedRooms = false;
                 }
             }
             else if(parsedResponse->option == 2)
             {

             }
             else if(parsedResponse->option == 3)
             {

             }
             else if(parsedResponse->option == 4)
             {

             }
             else
             {

             }
         }




    }while (voldermortAlive == true)
return 0;
}

/*

*/
int startGame()
{
    int choice;
    do{
        std::cout << "1. Start New Game" << std::endl;
        std::cout << "2. Load Game" << std::endl;
        std::cin >> choice;
        if((choice != 1) || (choice != 2))
        {
            std::cout << "Invalid Choice, Please enter 1 or 2" << std::endl;
        }
    }while ((choice != 1) || (choice != 2));

}

/*
                newGame()
Description: Function to load a new game
*/
void newGame(bool *visit, int *items, int *interactions, int *current)
{

}

/*

*/
void savedGame(bool *visit, int *items, int *interactions, int *current)
{

}

/*

*/
bool moveLogicCheck(int currentRoom, int nextRoom)
{

}
