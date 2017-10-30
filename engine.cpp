#include "engine.hpp"

bool getIntInput(int&);

Game::Game() {

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

    /*
    Each Case in the function follows this general flow:
    1: If the user just gets to the room it will allocate the room then call printEntrance() to print either long or short description.
    2: It will print all available interactions.
    3: It will print all items dropped in room by user that are non-native to room.
    4: It will print any items short descriptions native to the room.
    5: It will print the short exit if available.
    */
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
                printItems(-1);
                printExit(userRoom);
                break;
            }
         case 1:        // Weasley's House
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("1.room");
                    printEntrance(userRoom);
                }
                printInteractions();
                printItems(0);
                if((items[0][1] == true) && (items[0][0] == 1))
                {
                    itemsArray[0]->printShort();
                }
                printExit(userRoom);
                break;
            }
         case 2:        // London Diner
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("2.room");
                    printEntrance(userRoom);
                }
                printInteractions();
                printItems(-1);
                printExit(userRoom);
                break;
            }
         case 3:        // Safe House
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("3.room");
                    printEntrance(userRoom);
                }
                printInteractions();
                printItems(-1);
                printExit(userRoom);
                break;
            }
         case 4:        // HeadQuarters
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("4.room");
                    printEntrance(userRoom);
                }
                printInteractions();
                printItems(1);
                if((items[1][1] == true) && (items[1][0] == 4))
                {
                    itemsArray[1]->printShort();
                }
                printExit(userRoom);
                break;
            }
         case 5:        // Forest
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("5.room");
                    printEntrance(userRoom);
                }
                printInteractions();
                printItems(2);
                if((items[2][1] == true) && (items[2][0] == 5))
                {
                    itemsArray[2]->printShort();
                }
                printExit(userRoom);
                break;
            }
         case 6:        // Godric Hallow
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("6.room");
                    printEntrance(userRoom);
                }
                printInteractions();
                printItems(-1);
                printExit(userRoom);
                break;
            }
         case 7:        // Malfloy Manor
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("7.room");
                    printEntrance(userRoom);
                }
                printInteractions();
                printItems(3);
                if((items[3][1] == true) && (items[3][0] == 7))
                {
                    itemsArray[3]->printShort();
                }
                printExit(userRoom);
                break;
            }
         case 8:        // Beach House
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("8.room");
                    printEntrance(userRoom);
                }
                printInteractions();
                printItems(-1);
                printExit(userRoom);
                break;
            }
         case 9:        // Gringot Bank
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("9.room");
                    printEntrance(userRoom);
                }
                printInteractions();
                printItems(4);
                if((items[4][1] == true) && (items[4][0] == 9))
                {
                    itemsArray[4]->printShort();
                }
                printExit(userRoom);
                break;
            }
         case 10:       // Hogsmeade
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("10.room");
                    printEntrance(userRoom);
                }
                printInteractions();
                printItems(-1);
                printExit(userRoom);
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
        getline( std::cin, userCommand);

        // Pre parse command for exit
        if (userCommand=="exit") {
            std::cout << "Do you want to save first? Y/N " << std::endl;
            std::cin >> userCommand;
            if((userCommand == "y") || (userCommand == "Y"))
            {
                parsedResponse = new Response();
                parsedResponse->setCommand(4);
            }
            else if((userCommand == "n") || (userCommand == "N"))
            {
                // end game.
            }
            else
            {
                std::cout << "Invalid Command" << std::endl;
            }
        }

        //parsedResponse = parseCommand(userCommand);
        parsedResponse = new Response();

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
                std::cout << "'save'                        -- Saves the game" << std::endl;
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
            else if(parsedResponse->getOption() == 4)                       // save
            {
                std::string description;
                std::cout << "Please enter a description for your save." << std::endl;
                getline( std::cin, description);
            }
        }

        if(parsedResponse->getCommand() == 2)                               // Move Command
        {
            moveLogic = moveLogicCheck(parsedResponse->getRoom());

            if(moveLogic == true)
            {
                if(parsedResponse->getRoom() == -2)
                {
                    currentRoom = currentRoom -1;                           // If -2 and available, go back 1 room.
                }
                else
                {
                    currentRoom = parsedResponse->getRoom();                // Else set room to room requested.
                }

                userRoom->printExitLong();
                delete userRoom;                                            // Delete current room so can reallocate
                movedRooms = true;                                          // Room moved is true.
            }
            else
            {
                std::cout << "Invalid Command, Please Try Again." << std::endl;
                movedRooms = false;
            }
        }

        if(parsedResponse->getCommand() == 3)                               // Interaction Command
        {
                switch(currentRoom)
                {
                case 0:        // Harry's House
                    {
                        if(parsedResponse->getInteraction() == 0)           // If interaction 1 <potion>
                        {
                            interactionsArray[0]->printLong();               // Print long <potion>
                            interactions[0][1] = false;                     // Set <potion> availability to false.
                            interactions[1][1] = true;                      // Set <clothes> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 1)
                        {
                            interactionsArray[1]->printLong();               // Print Long <clothes>
                            interactions[1][1] = false;                     // Set <clothes> availability to false.
                            roomsVisited[1][1] = true;                      // Set Wesley House Available.
                        }
                        break;
                    }
                case 1:
                    {
                        if(parsedResponse->getInteraction() == 2)
                        {
                            interactionsArray[2]->printLong();               // Print long <will>
                            interactions[2][1] = false;                     // Set <will> availability to false.
                            items[0][1] = true;                             // Set <snitch> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 3)
                        {
                            interactionsArray[3]->printLong();               // Print long <wedding>
                            interactions[2][1] = false;                     // Set <wedding> availability to false.
                            roomsVisited[2][1] = true;                      // Set London Diner Available.
                        }
                        break;
                    }
                case 2:
                    {
                        if(parsedResponse->getInteraction() == 4)
                        {
                            interactionsArray[4]->printLong();               // Print long <server>
                            interactions[4][1] = false;                     // Set <server> availability to false.
                            interactions[5][1] = true;                      // Set <deatheater> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 5)
                        {
                            std::cout << "You need to cast a spell at the Death Eaters" << std::endl;
                        }
                        break;
                    }
                case 3:
                    {
                        if(parsedResponse->getInteraction() == 6)
                        {
                            interactionsArray[6]->printLong();               // Print long <cupboard>
                            interactions[6][1] = false;                     // Set <cupboard> availability to false.
                            interactions[7][1] = true;                      // Set <Mundungus> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 7)
                        {
                            interactionsArray[7]->printLong();               // Print long <Mundungus>
                            interactions[7][1] = false;                     // Set <Mundungus> availability to false.
                            roomsVisited[4][1] = true;                      // Set Headquarters to Available
                        }
                        break;
                    }
                case 4:
                    {
                        if(parsedResponse->getInteraction() == 8)
                        {
                            interactionsArray[8]->printLong();               // Print long <toilet>
                            interactions[8][1] = false;                     // Set <toilet> availability to false.
                            interactions[9][1] = true;                      // Set <elevator> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 9)
                        {
                            interactionsArray[9]->printLong();               // Print long <elevator>
                            interactions[9][1] = false;                     // Set <elevator> availability to false.
                            interactions[10][1] = true;                     // Set <dolores> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 10)
                        {
                            interactionsArray[10]->printLong();              // Print long <dolores>
                            interactions[10][1] = false;                    // Set <dolores> availability to false.
                            items[1][1] = true;                             // Set Necklace available.
                        }
                        break;
                    }
                case 5:
                    {
                        if(parsedResponse->getInteraction() == 11)
                        {
                            std::cout << "You need to cast a spell to set the tent up." << std::endl;
                        }
                        else if(parsedResponse->getInteraction() == 12)
                        {
                            interactionsArray[12]->printLong();              // Print long <patronus>
                            interactions[12][1] = false;                    // Set <patronus> availability to false.
                            interactions[13][1] = true;                     // Set <lake> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 13)
                        {
                            interactionsArray[12]->printLong();              // Print long <lake>
                            interactions[13][1] = false;                    // Set <lake> availability to false.
                            items[2][1] = true;                             // Set <sword> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 14)
                        {
                            if(items[2][0] == -1)
                            {
                                interactionsArray[14]->printLong();              // Print long <horcrux>
                                interactions[14][1] = false;                    // Set <horcrux> availability to false.
                                roomsVisited[6][1] = true;                      // Set Godrics Hallow to Available
                            }
                            else
                            {
                                std::cout << "You need the <Sword> of Gryffindor to defeat Voldermort's Horcrux." << std::endl;
                            }

                        }
                        break;
                    }
                case 6:
                    {
                        break;
                    }
                case 7:
                    {
                        break;
                    }
                case 8:
                    {
                        break;
                    }
                case 9:
                    {
                        break;
                    }
                case 10:
                    {
                        break;
                    }
                }

                movedRooms = false;
        }

        if(parsedResponse->getCommand() == 4)                               // Item Command
        {
                if(parsedResponse->getOption() ==1)                         // Get Item Command
                {
                    int currentItem = parsedResponse->getItem();
                    switch(currentItem)
                    {
                    case 0:
                        {
                            // If <snitch> is in default room, is available, and user is in room 1.
                            if((items[0][0] == 1) && (items[0][1] == true) && (currentRoom == 1))
                            {
                                itemsArray[0]->printLong();                  // Print long
                                items[0][0] = -1;                           // Place <snitch> in inventory.
                                interactions[3][1] = true;                  // Set wedding interaction available.
                            }
                            // Else if <snitch> is in current room and available.
                            else if((items[0][0] == currentRoom) && (items[0][1] == true))
                            {
                                items[0][0] = -1;                           // Place in inventory
                                std::cout << "You picked up the Golden <snitch>." << std::endl;
                            }
                            else if(items[0][0] == -1)
                            {
                                std::cout << "The Golden <snitch> is already in your inventory." << std::endl;
                            }
                        }
                    case 1:
                        {
                            // If <necklace> is in default room, is available, and user is in room 4.
                            if((items[1][0] == 4) && (items[1][1] == true) && (currentRoom == 4))
                            {
                                itemsArray[1]->printLong();                  // Print long
                                items[1][0] = -1;                           // Place <necklace> in inventory.
                                roomsVisited[5][1] = true;                  // Set Forest to Available
                            }
                            // Else if <snitch> is in current room and available.
                            else if((items[1][0] == currentRoom) && (items[1][1] == true))
                            {
                                items[1][0] = -1;                           // Place in inventory
                                std::cout << "You picked up the <necklace>." << std::endl;
                            }
                            else if(items[1][0] == -1)
                            {
                                std::cout << "The <necklace> is already in your inventory." << std::endl;
                            }
                        }
                    case 2:
                        {
                            // If <sword> is in default room, is available, and user is in room 5.
                            if((items[2][0] == 5) && (items[2][1] == true) && (currentRoom == 5))
                            {
                                itemsArray[2]->printLong();                  // Print long
                                items[2][0] = -1;                           // Place <sword> in inventory.
                                interactions[14][1] = true;                 // Set <horcrux> availability to true.
                            }
                            // Else if <snitch> is in current room and available.
                            else if((items[2][0] == currentRoom) && (items[2][1] == true))
                            {
                                items[2][0] = -1;                           // Place in inventory
                                std::cout << "You picked up the <Sword> of Gryffindor." << std::endl;
                            }
                            else if(items[2][0] == -1)
                            {
                                std::cout << "The <Sword> of Gryffindor is already in your inventory." << std::endl;
                            }
                        }
                    }

                    movedRooms = false;
                }
                else if(parsedResponse->getOption() == 2)                   // Drop Item Command
                {
                    if(items[parsedResponse->getItem()][0] == -1)           // If item current location is in the inventory
                    {
                        items[parsedResponse->getItem()][0] = currentRoom;  // Items new current location is the current room.

                        if(parsedResponse->getItem() == 0)                  // Print what item they dropped.
                            std::cout << "You dropped the Golden <snitch>." << std::endl;
                        else if(parsedResponse->getItem() == 1)
                            std::cout << "You dropped the <Necklace> Horcrux." << std::endl;
                        else if(parsedResponse->getItem() == 2)
                            std::cout << "You dropped the <Sword> of Gryffindor." << std::endl;
                        else if(parsedResponse->getItem() == 3)
                            std::cout << "You dropped Draco Malfloy's <wand>." << std::endl;
                        else if(parsedResponse->getItem() == 4)
                            std::cout << "You dropped the <chalice> Horcrux." << std::endl;
                        else if(parsedResponse->getItem() == 5)
                            std::cout << "You dropped the <Diadem> of Ravenclaw" << std::endl;
                        else if(parsedResponse->getItem() == 6)
                            std::cout << "You dropped Snape's <memories>." << std::endl;
                        else if(parsedResponse->getItem() == 7)
                            std::cout << "You dropped the Resurrection <Stone>." << std::endl;
                    }
                    else
                    {
                        std::cout << "This item is not in your inventory." << std::endl;
                    }
                    movedRooms = false;
                }
        }

        if(parsedResponse->getCommand() == 5)                               // Spell Command
        {
            int spellTarget = parsedResponse->getInteraction();
            switch(spellTarget)
            {
            case 5:
                {
                    interactionsArray[5]->printLong();               // Print long <deatheater>
                    interactions[5][1] = false;                     // Set <deatheater> availability to false.
                    roomsVisited[3][1] = true;                      // Set Safe House available.
                    movedRooms = false;
                    break;
                }
            case 11:
                {
                    interactionsArray[11]->printLong();              // Print long <tent>
                    interactions[11][1] = false;                    // Set <tent> availability to false.
                    interactions[12][1] = true;                     // Set <patronus> availability to true.
                    movedRooms = false;
                }
            }
        }

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
// Checks if nextRoom is either current room +1 or -1.
// Checks if nexRoom is available and returns true if both conditions are satisfied.
// False otherwise.
bool Game::moveLogicCheck(int nextRoom) const
{
    if((nextRoom == (currentRoom+1)) && (roomsVisited[currentRoom+1][1] == true))
    {
        return true;
    }
    else if((nextRoom == (currentRoom-1)) && (roomsVisited[currentRoom-1][1] == true))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::loadDefault() {

    std::ifstream fileStream("data/default.dat", std::ios_base::in);

    if (!fileStream.is_open()) {
        std::ofstream OFS("data/default.dat", std::ios_base::out);
        OFS<<"0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1\r\n";
        OFS<<"1 0 4 0 5 0 7 0 9 0 11 0 14 0 16 0\r\n";
        OFS<<"0 1 1 0 2 1 3 0 4 1 5 0 6 1 7 0 8 1 9 0 10 0 11 1 12 0 13 0 14 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
        OFS.close();
        fileStream.open("data/default.dat");
        if(!fileStream.is_open()) {
            return;
        }
    }




    // hard coded variable initialization until init from file is implemented.
    int i = 0;
    // set all rooms unavailable and not visited at start.
    for (i = 0; i < 16; i++)
    {
        int a;
        bool b;

        fileStream >> a >> b;
        roomsVisited[i][0] = a;
        roomsVisited[i][1] = b;
    }

    // set rooms numbers for items
    for(i = 0; i < 8; i++)
    {
        int a;
        bool b;
        fileStream>>a>>b;
        items[i][0] = a;
        items[i][1] = b;
    }


    for(i=0; i<39; i++){
        int a;
        bool b;
        fileStream >> a >> b;
        interactions[i][0] = a;
        interactions[i][1] = b;
    }


    fileStream.close();
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
