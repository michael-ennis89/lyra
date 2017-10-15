#include "engine.hpp"

bool getIntInput(int&);

Game::Game() {
    currentRoom = 0;
}

Game::~Game() {
    for(Data::Item* e:itemsArray){
        delete e;
    }
    itemsArray.clear();
    for(Data::Interaction* e:interactionsArray) {
        delete e;
    }
    interactionsArray.clear();
    std::cout << "Game closed!\n";
}

std::vector<std::string> getProfiles(bool displayProfiles=false) {
    std::vector<std::string> res;

    std::ifstream fileStream("data/profiles.data");

    if(!fileStream.good()) {
        std::cout << "File profiles.data is missing from data directory!\n";
        return {};
    }
    int cnt = 0;
    std::string inputName="";
    while(fileStream>>inputName){
        if(displayProfiles)
        std::cout << (++cnt) << ". " << inputName << std::endl;
        res.push_back(inputName);
    }

    return res;
}


bool Game::Initialize(int option) {
    try{

        //Initialize all interactions and items
        itemsArray=Data::getItems(3);
        interactionsArray=Data::getInteractions(3);


        if (option==1) {
            //NEW GAME
            //Load data from a default file
            bool brk = true;
            while(true) {
                std::cout << "Please enter new profile name: ";
                std::cin>>playerName;
                std::cin.get();
                std::cin.get();
                std::cin.sync();
                //std::cin.ignore(std::string, '\n');
                brk=true;
                for(const char& c:playerName) {
                    if(std::isalpha(c)==false && std::isdigit(c)==false){
                        brk=false;
                        break;
                    }
                }
                if(brk)
                break;
            }

            std::cout << "Hello " << playerName << ". Welcome to the Horcrux!" << std::endl;

            loadDefault();
        }else if (option==2) {
            //LOAD GAME
            //Load from a save file

            //Display all available save files
            //Select a profile first
            std::cout << "LISTING AVAILABLE PROFILES: " << std::endl;


            std::vector<std::string> profiles;
            std::string inputName = "";

            profiles = getProfiles(true);
            if (profiles.empty()) {
                std::cout << "File profiles.data is either missing or there is no profiles yet!" << std::endl;
                return Initialize(startGame());
            }

            int choice = 0;
            while(true) {
                std::cout << "Enter a profile number: ";
                if(getIntInput(choice)==true) {
                    if(choice>0 && choice<=profiles.size()) {
                        playerName=profiles[choice-1];
                        std::cout << "Selected profile: " << playerName;
                        break;
                    } else {
                        std::cout << "Input was out of bounds, please enter a number between 1 and " << profiles.size() << std::endl;
                    }
                } else {
                    std::cout << "Bad input! Please enter a valid number" << std::endl;
                }
            }


            //GET SAVE FILENAME BY playerName.

            //TODO


        }

    } catch (std::exception& ex) {
        std::cout << "An error occured: " << ex.what() << std::endl;
        return false;
    }

    return true;
}
void Game::Run(){

    if (Initialize(startGame()) == false) {
        std::cout << "Unable to start a game!\n";
        return;
    }

    // Temp Variables
    bool voldermortAlive = true;
    bool movedRooms;
    bool moveLogic;
    std::string userCommand;    // Holds user commands
    Response *parsedResponse;   // Holds parsed response from parser

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

         std::cout << ">>";
         std::cin >> userCommand;
         // parsedResponse = parseCommand(userCommand); TODO

         /*if(parsedResponse->command == -1)
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
        */



    }while (voldermortAlive == true);
}

/*

*/
int Game::startGame()
{
    int choice;
    do{
        std::cout << "1. Start New Game" << std::endl;
        std::cout << "2. Load Game" << std::endl;
        getIntInput(choice); //std::cin >> choice;

        if((choice != 1) && (choice != 2))
        {
            std::cout << "Invalid Choice, Please enter 1 or 2" << std::endl;
        }
    }while ((choice != 1) && (choice != 2));
    return choice;
}

//Does integer input with error-handling
bool getIntInput(int& var) {
    bool res=true;
    std::cin>>var;
    if(!std::cin) {
        std::cin.clear();
        var=0;
        res = false;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return res;
}

bool Game::moveLogicCheck(int currentRoom, int nextRoom) const
{
    return false;
}

void Game::loadDefault() {

}

void Game::loadFromFile(const std::string& fileName) {

}

bool Game::saveGame() const {
    //Save variables to a file named <playerName>.save

}
