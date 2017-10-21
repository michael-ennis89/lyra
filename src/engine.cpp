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
                std::cout << "Please enter new profile name(no whitespaces): ";
                std::cin>>playerName;
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
            std::cout << "LIST OF AVAILABLE PROFILES: " << std::endl;

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
            loadFromFile("data/" + playerName + "_save.data");
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
    bool movedRooms = true;     // Always starts out with true to load a room and printEntrance.
    bool moveLogic;
    std::string userCommand;    // Holds user commands
    Response *parsedResponse;   // Holds parsed response from parser
    Data::Room *userRoom;

    do{
         switch(currentRoom)
         {
         case 0:        // Harry's House
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("0.room");
                    printEntrance(userRoom);
                }
                printInteractions();
                printItems(-1);             // -1 = No items to ignore.
                printExit(userRoom);

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
        if (userCommand=="exit") {
            break;
        }

        parsedResponse = parseCommand(userCommand);

        if(parsedResponse->getCommand() == -1)
        {
            std::cout << "Invalid Command, Please Try Again." << std::endl;
            movedRooms = false;
        }

        if(parsedResponse->getCommand() == 1)               // Basic Command
        {
            if(parsedResponse->getOption() == 1)            // look Command
            {
                userRoom->printLong();
            }
            else if(parsedResponse->getOption() == 2)       // help Command
            {
                std::cout << "Available Commands" << std::endl;
                std::cout << "'look'                        -- Repeats room entrance. " << std::endl;
                std::cout << "'look at <interaction>'       -- Inspects bracketed words. " << std::endl;
                std::cout << "'take <item>'                 -- Places an item in your inventory. " << std::endl;
                std::cout << "'drop <item>'                 -- Drops an item from your inventory. " << std::endl;
                std::cout << "'inventory'                   -- Displays your current inventory. " << std::endl;
                std::cout << "'cast spell at <interaction>' -- Casts a spell at the interaction. " << std::endl;
                std::cout << "'go <location>'               -- Moves to the target location. " << std::endl;
            }
            else if(parsedResponse->getOption() == 3)       // inventory Command
            {
                std::cout << "Current Inventory" << std::endl;
                std::cout << "--------------------" << std::endl;
                if(items[0][0] == -1)
                    std::cout << "Golden <Snitch>" << std::endl;
                if(items[1][0] == -1)
                    std::cout << "<Necklace> Horcrux" << std::endl;
                if(items[2][0] == -1)
                    std::cout << "<Sword> of Gryffindor" << std::endl;
                if(items[3][0] == -1)
                    std::cout << "Draco Malfloy's <Wand>" << std::endl;
                if(items[4][0] == -1)
                    std::cout << "<Chalice> Horcrux" << std::endl;
                if(items[5][0] == -1)
                    std::cout << "Lost <Diadem> of Ravenclaw" << std::endl;
                if(items[6][0] == -1)
                    std::cout << "Snape's <Memories>" << std::endl;
                if(items[7][0] == -1)
                    std::cout << "Resurrection <stone>" << std::endl;

                std::cout << "--------------------" << std::endl;
            }
            else if(parsedResponse->getOption() == 4)       // save & quit game Command
            {

            }
        }

        if(parsedResponse->getCommand() == 2)               // Move Command
        {
            moveLogic = moveLogicCheck(parsedResponse->getRoom());

            if(moveLogic == true)
            {
                currentRoom = parsedResponse->getRoom();
                userRoom->printExitLong();
                delete userRoom;
                movedRooms = true;
            }
            else
            {
                std::cout << "Invalid Command, Please Try Again." << std::endl;
                movedRooms = false;
            }
        }
        /*
        if(parsedResponse->getCommand() == 3)               // Interaction Command
        {
            if(parsedResponse->getOption() == 1)
            {
                switch((int)*currentRoom)
                {
                case 0:        // Harry's House
                    {
                        if(parsedResponse->getInteraction() == 0)
                        {
                            interactionsArray[0].printLong();
                            interactions[0][1] = false;
                            interactions[1][1] = true;
                            movedRooms = false;
                        }
                        else if(parsedResponse->getInteraction() == 1)
                        {
                            interactionsArray[1].printLong();
                            interactions[1][1] = false;
                            roomsVisited[1][1] = true;          // Set Wesley House Available.
                        }
                        break;
                    }
                case 1:
                    {
                        break;
                    }
                }
            }
            else if(parsedResponse->getOption() == 2)
            {

            }
            else if(parsedResponse->getOption() == 3)
            {

            }
            else if(parsedResponse->getOption() == 4)
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

// Phase 1 logic check for moving rooms.
// Might add extra validation like needing items
bool Game::moveLogicCheck(int nextRoom) const
{
    if((nextRoom == (currentRoom+1)) && (roomsVisited[currentRoom+1][1] == true))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::loadDefault() {

}

void Game::loadFromFile(const std::string& fileName) {

}

bool Game::saveGame() const {
    //Save variables to a file named <playerName>.save

}

// function to print any items that are placed in a room by user.
// can disregard certain items to ensure long form is printed by switch
void Game::printItems(int disreguard)
{
    int i;
    for(i = 0; i < 8; i++)
    {
        if(i != disreguard)
        {
            if((items[i][0] == currentRoom) && (items[i][1] == true))
            {
                //itemsArray[i]->printShort();
                /*Change to short non interactive form*/
            }
        }
    }
}

// prints out all short interaction descriptions for the current room.
void Game::printInteractions()
{
    int i;
    for(i = 0; i < 39; i++)
    {
        if((interactions[i][0] == currentRoom) && (interactions[i][1] == true))
        {
            //interactionsArray[i]->printShort();
        }
    }
}


// prints out the short or long entrance of the current room.
void Game::printEntrance(Data::Room *userRoom)
{
    if(roomsVisited[currentRoom][0] == false)
    {
        userRoom->printLong();
    }
    else
    {
        userRoom->printShort();
    }
}

// prints out the short exit for the user room if available.
void Game::printExit(Data::Room *userRoom)
{
    if(roomsVisited[currentRoom+1][1] == true)
    {
        userRoom->printExitShort();
    }
}
