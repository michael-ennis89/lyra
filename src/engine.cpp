
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

std::vector<Player> getProfiles(bool displayProfiles=false) {
    std::vector<Player> res;

    std::ifstream fileStream("data/profiles.data");

    if(!fileStream.good()) {
        std::cout << "File profiles.data is missing from data directory!\n";
        return {};
    }
    int cnt = 0;
        Player playerDisplay;
    while(fileStream>>playerDisplay.name){
        if(displayProfiles)
        std::cout << (++cnt) << ". " << playerDisplay.name << std::endl;

        res.push_back(playerDisplay);
    }

    return res;
}

void createProfile(const Player& playerName, bool editAllProfilesFile = true) {

    std::ofstream profileFile("profiles/" + playerName.name + ".profile", std::ios_base::out | std::ios_base::trunc);
    profileFile << playerName.name << " " << playerName.saves;
    profileFile.close();

	if (editAllProfilesFile) {
		std::ofstream AllProfilesFile("data/profiles.data", std::ios_base::out | std::ios_base::app);
		AllProfilesFile << playerName.name << "\r\n";

		AllProfilesFile.close();
	}
}

bool Game::Initialize(int option) {
    try{

        //Initialize all interactions and items
        itemsArray=Data::getItems(8);
        interactionsArray=Data::getInteractions(42);

        //Get profiles from file.
        std::vector<Player> profiles;
        profiles = getProfiles(false);

        if (option==1) {
            //NEW GAME
            //Load data from a default file
            bool brk = true;
            while(true) {

                std::cout << "Please enter new profile name: ";
                std::string pName;
                getline(std::cin, pName);
                pName.erase(std::remove(pName.begin(),pName.end(),' '),pName.end());
                player.name = pName;
                //std::cin.get();
                //std::cin.sync();

                //std::cin.ignore(std::string, '\n');
                brk=true;
                for(const char& c:player.name) {
                    if(std::isalpha(c)==false && std::isdigit(c)==false){
                        brk=false;
                        break;
                    }
                }

                if(brk) {
                    //Check if it is a duplicate
                    for(const Player& p: profiles) {
                        if (p.name==player.name) {
                            std::cout << "Profile " << p.name << " already exists!" << std::endl;
                            brk=false;
                            break;
                        }
                    }
                    if(brk)
                    break;
                }
            }

            createProfile(player); //Create a file in profiles for a new player

            std::cout << "Hello " << player.name << ". Welcome to the Horcrux!" << std::endl;
            std::cout << "For a list of commands type 'help'" << std::endl;
            std::cout << std::endl;



            return loadDefault();
        } else if (option==2) {
            LOAD_GAME:
            std::cout << "\nLIST OF AVAILABLE PROFILES: " << std::endl;
            profiles = getProfiles(true);
            //LOAD GAME
            //Load from a save file

            //Display all available save files
            std::string inputName = "";

            std::cout << profiles.size()+1 << ". <--- Go Back" << std::endl;
            if (profiles.empty()) {
                std::cout << "File profiles.data is either missing or there are no profiles yet!" << std::endl;
                return Initialize(startGame());
            }

            int choice = 0;
            while(true) {
                std::cout << "Enter a profile number: ";
                if(getIntInput(choice)==true) {

                    if (choice ==  (int)profiles.size()+1) {
                        return Initialize(startGame());
                    }
                    if(choice>0 && choice <=  (int)profiles.size()) {
                        player=profiles[choice-1];
                        std::cout << "Selected profile: " << player.name;
                        break;
                    } else {
                        std::cout << "Input was out of bounds, please enter a number between 1 and " << profiles.size() << std::endl;
                    }
                } else {
                    std::cout << "Bad input! Please enter a valid number" << std::endl;
                }
            }


            //Read from a .profile file
            std::ifstream profileFileStream("profiles/" + player.name + ".profile", std::ios_base::in);

            if(!profileFileStream.is_open()) {
                std::ofstream profileOFS("profiles/" + player.name + ".profile", std::ios_base::out);
                profileOFS<<player.name << " 0";
                player.saves = 0;
                profileOFS.close();
            }else{
                profileFileStream>>player.name>>player.saves;
                profileFileStream.close();
            }


            //GET SAVE FILENAME BY playerName.
            std::string saveFileName = "";

            //Check for existing save files for selected profile

            std::ifstream iStreamFiles;
            int foundFiles = 0;
            std::vector<std::string> saveFiles;

            std::cout<<std::endl<<std::endl;
            std::cout << "Available saved games for " << player.name << ": " <<std::endl;

            for(int i=0; foundFiles<player.saves && i<20; i++){
                saveFileName = "saved/" + player.name + "_" + Data::to_string(i) + ".save";
                iStreamFiles.open(saveFileName);

                if(iStreamFiles.is_open()) {
                    std::string title = "";
                    std::getline(iStreamFiles, title);
                    std::cout << ++foundFiles << ". " << title << std::endl;
                    saveFiles.push_back(saveFileName);
                    iStreamFiles.close();
                }
            }

            std::cout << foundFiles+1 << ". <--- Go Back" << std::endl;


            std::cout << "\nSelect the file to load a game from: ";

            if (foundFiles>0) {

                while(true) {

                    int input = 0;
                    if(getIntInput(input)==true) {
                        if (input == foundFiles+1) {
                            goto LOAD_GAME;
                        }
                        if (input>0 && input<foundFiles+1) {
                            saveFileName=saveFiles[input-1];
                            std::cout << "Selected: " << saveFiles[input-1] << std::endl;
                            break;
                        }

                    }

                }

            } else {

                std::cout << "No save files for this profile!" << std::endl;
                return loadDefault();
            }


            //TODO
            return loadFromFile(saveFileName);
        }

    } catch (std::exception& ex) {
        std::cout << "An error occured: " << ex.what() << std::endl;
        return false;
    }

    return true;
}

void Game::Run(){
    displayArt();
    displayCredits();

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
    Parser myParser;

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
                    roomsVisited[0][0] = true;
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
                    roomsVisited[1][0] = true;
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
                    roomsVisited[2][0] = true;
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
                    roomsVisited[3][0] = true;
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
                    roomsVisited[4][0] = true;
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
                    roomsVisited[5][0] = true;
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
                    roomsVisited[6][0] = true;
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
                    roomsVisited[7][0] = true;
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
                    roomsVisited[8][0] = true;
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
                    roomsVisited[9][0] = true;
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
                    roomsVisited[10][0] = true;
                }
                printInteractions();
                printItems(-1);
                printExit(userRoom);
                break;
            }
         case 11:       //Room of Requirement
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("11.room");
                    if(interactions[27][1] == true)         // if students interaction available.
                    {
                        printRoomData(userRoom, 1);         // print regular long entrance
                    }
                    else if(items[5][1] == true)            // if ready for some fire
                    {
                        hardCodedDescriptions(0);           // print hard coded long entrance
                    }
                    else if(items[5][1] == false)
                    {
                        printRoomData(userRoom, 0);         // print short entrance.
                    }
                    roomsVisited[11][0] = true;
                }
                printInteractions();
                printItems(5);                              // Dont print diadem pickup
                if((items[5][1] == true) && (items[5][0] == 11))    // print short diadem description
                {
                    itemsArray[5]->printShort();
                }
                printConnections();
                break;
            }
         case 12:       // Ravenclaw Tower
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("12.room");
                    if(interactions[30][1] == true)         // If luna interaction is available.
                    {
                        printRoomData(userRoom, 1);         // print regular long entrance
                    }
                    else if(interactions[30][1] == false)   // if here when your not suppose to be
                    {
                        printRoomData(userRoom, 0);         // print short entrance.
                    }
                    roomsVisited[12][0] = true;
                }
                printInteractions();
                printItems(-1);                             // print all pickups
                printConnections();
                break;
            }
         case 13:       // Courtyard
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("13.room");
                    if(interactions[32][1] == true)         // if ready to kill voldemort
                    {
                        printRoomData(userRoom, 1);         // print regular long entrance.
                    }
                    else if(interactions[32][1] == false)
                    {
                        printRoomData(userRoom, 0);         // print short entrance.
                    }
                    roomsVisited[13][0] = true;
                }
                printInteractions();
                printItems(-1);
                printConnections();
                break;
            }
         case 14:       // Boat House
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("14.room");
                    if(interactions[35][1] == true)         // if hide interaction available
                    {
                        printRoomData(userRoom, 1);         // print regular long entrance.
                    }
                    else if(interactions[35][1] == false)
                    {
                        printRoomData(userRoom, 0);         // print short entrance.
                    }
                    roomsVisited[14][0] = true;
                }
                printInteractions();
                printItems(6);                              // Dont print memories pickup
                if((items[6][1] == true) && (items[6][0] == 14))    // print short memories description
                {
                    itemsArray[6]->printShort();
                }
                printConnections();
                break;
            }
         case 15:       // Great Hall
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("15.room");
                    if(interactions[38][1] == true)         // if headmaster interaction available.
                    {
                        printRoomData(userRoom, 1);         // print regular long entrance.
                    }
                    else if(interactions[38][1] == false)
                    {
                        printRoomData(userRoom, 0);         // print short entrance.
                    }
                    roomsVisited[15][0] = true;
                }
                printInteractions();
                printItems(-1);
                printConnections();
                break;
            }
         case 16:       // Enchanted Forest
            {
                if(movedRooms == true)
                {
                    userRoom = new Data::Room("16.room");
                    if(items[7][1] == true)         // if ready to die
                    {
                        printRoomData(userRoom, 1);         // print regular long entrance.
                    }
                    else if(items[7][1] == false)
                    {
                        printRoomData(userRoom, 0);         // print short entrance.
                    }
                    roomsVisited[16][0] = true;
                }
                printInteractions();
                printItems(7);                              // Dont print stone pickup
                if((items[7][1] == true) && (items[7][0] == 16))    // print short stone description
                {
                    itemsArray[7]->printShort();
                }
                printConnections();
                break;
            }
         }
        std::cout << ">> " << std::endl;
        std::cin.clear();
        std::getline(std::cin, userCommand);
        //parsedResponse = parseCommand(userCommand);
        Response testResponse = myParser.parse(userCommand);
        parsedResponse = &testResponse;

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
                std::cout << std::endl;
                std::cout << "Current Inventory" << std::endl;
                std::cout << "----------------------------------------" << std::endl;
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

                std::cout << "----------------------------------------" << std::endl;
                std::cout << std::endl;
            }
            else if(parsedResponse->getOption() == 4)                       // save
            {
                std::string description;
                std::cout << std::endl;
                std::cout << "Please enter a description for your save." << std::endl;
                getline(std::cin, description);
                bool checkSave;
                checkSave = saveGame(description);
                if(checkSave == true)
                {
                    std::cout << "Game Saved" << std::endl;
                    voldermortAlive = false;
                    std::cout << std::endl;
                }
                else
                {
                    std::cout << "Error Saving Game" << std::endl;
                }

            }
        }

        if(parsedResponse->getCommand() == 2)                               // Move Command
        {
            if(currentRoom <= 10)
            {

                moveLogic = moveLogicCheck(parsedResponse->getRoom());
                if((parsedResponse->getRoom() == -2) && ((currentRoom >= 1) && (currentRoom <= 10)))
                {
                    currentRoom = currentRoom -1;
                    delete userRoom;
                    movedRooms = true;
                }
                else if(moveLogic == true)
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
                    std::cout << std::endl;
                    delete userRoom;                                            // Delete current room so can reallocate
                    movedRooms = true;                                          // Room moved is true.
                }
                else
                {
                    std::cout << "Invalid Command, Please Try Again." << std::endl;
                    movedRooms = false;
                }
            }
            else if(currentRoom >= 11)
            {
                moveLogic = moveLogicPhaseTwo(parsedResponse->getRoom());
                if(moveLogic == true)
                {
                    if((currentRoom == 11) && (roomsVisited[11][1] == 1))       // If Room of Requirement not Destroyed.
                    {
                        currentRoom = parsedResponse->getRoom();                // Go to requested room.
                        printRoomData(userRoom, 3);                             // Print current room's long exit.
                    }
                    else if((currentRoom == 11) && (roomsVisited[11][1] == 0))  // If Room of Requirement destroyed.
                    {
                        currentRoom = parsedResponse->getRoom();                // Go to requested room.
                        hardCodedDescriptions(1);                               // Hard coded room of req exit.
                    }
                    else
                    {
                        currentRoom = parsedResponse->getRoom();                // Go to requested room.
                        if(currentRoom != 13 || currentRoom != 16)              // Exits called in hard code based on intractions.
                        {
                            printRoomData(userRoom, 3);                         // Print current room's long exit.
                        }

                    }

                    std::cout << std::endl;
                    delete userRoom;
                    movedRooms = true;
                }
                else
                {
                    std::cout << "Invalid Command, Please Try Again." << std::endl;
                    movedRooms = false;
                }
            }

        }

        if(parsedResponse->getCommand() == 3)                               // Interaction Command
        {
                switch(currentRoom)
                {
                case 0:        // Harry's House
                    {
                        if((parsedResponse->getInteraction() == 0) && (interactions[0][1] == 1)) // If interaction 1 <potion>
                        {
                            interactionsArray[0]->printLong();               // Print long <potion>
                            interactions[0][1] = 0;                         // Set <potion> availability to false.
                            interactions[1][1] = 1;                         // Set <clothes> availability to true.
                        }
                        else if((parsedResponse->getInteraction() == 1) && (interactions[1][1] == 1))
                        {
                            interactionsArray[1]->printLong();               // Print Long <clothes>
                            interactions[1][1] = 0;                         // Set <clothes> availability to false.
                            roomsVisited[1][1] = 1;                         // Set Wesley House Available.
                        }
                        movedRooms = false;
                        break;
                    }
                case 1:
                    {
                        if(parsedResponse->getInteraction() == 2 && (interactions[2][1] == 1))
                        {
                            interactionsArray[2]->printLong();               // Print long <will>
                            interactions[2][1] = false;                     // Set <will> availability to false.
                            items[0][1] = true;                             // Set <snitch> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 3 && (interactions[3][1] == 1))
                        {
                            interactionsArray[3]->printLong();               // Print long <wedding>
                            interactions[2][1] = false;                     // Set <wedding> availability to false.
                            roomsVisited[2][1] = true;                      // Set London Diner Available.
                        }
                        movedRooms = false;
                        break;
                    }
                case 2:
                    {
                        if(parsedResponse->getInteraction() == 4 && (interactions[4][1] == 1))
                        {
                            interactionsArray[4]->printLong();               // Print long <server>
                            interactions[4][1] = false;                     // Set <server> availability to false.
                            interactions[5][1] = true;                      // Set <deatheater> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 5 && (interactions[5][1] == 1))
                        {
                            std::cout << "You need to cast a spell at the Death Eaters" << std::endl;
                        }
                        movedRooms = false;
                        break;
                    }
                case 3:
                    {
                        if(parsedResponse->getInteraction() == 6 && (interactions[6][1] == 1))
                        {
                            interactionsArray[6]->printLong();               // Print long <cupboard>
                            interactions[6][1] = false;                     // Set <cupboard> availability to false.
                            interactions[7][1] = true;                      // Set <Mundungus> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 7 && (interactions[7][1] == 1))
                        {
                            interactionsArray[7]->printLong();               // Print long <Mundungus>
                            interactions[7][1] = false;                     // Set <Mundungus> availability to false.
                            roomsVisited[4][1] = true;                      // Set Headquarters to Available
                        }
                        movedRooms = false;
                        break;
                    }
                case 4:
                    {
                        if(parsedResponse->getInteraction() == 8 && (interactions[8][1] == 1))
                        {
                            interactionsArray[8]->printLong();               // Print long <toilet>
                            interactions[8][1] = false;                     // Set <toilet> availability to false.
                            interactions[9][1] = true;                      // Set <elevator> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 9 && (interactions[9][1] == 1))
                        {
                            interactionsArray[9]->printLong();               // Print long <elevator>
                            interactions[9][1] = false;                     // Set <elevator> availability to false.
                            interactions[10][1] = true;                     // Set <dolores> availability to true.
                        }
                        movedRooms = false;
                        break;
                    }
                case 5:
                    {
                        if(parsedResponse->getInteraction() == 11 && (interactions[11][1] == true))
                        {
                            std::cout << "You need to cast a spell to set the tent up." << std::endl;
                        }
                        else if(parsedResponse->getInteraction() == 12 && (interactions[12][1] == 1))
                        {
                            interactionsArray[12]->printLong();              // Print long <patronus>
                            interactions[12][1] = false;                    // Set <patronus> availability to false.
                            interactions[13][1] = true;                     // Set <lake> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 13 && (interactions[13][1] == 1))
                        {
                            interactionsArray[13]->printLong();              // Print long <lake>
                            interactions[13][1] = false;                    // Set <lake> availability to false.
                            items[2][1] = true;                             // Set <sword> availability to true.
                        }
                        else if(parsedResponse->getInteraction() == 14 && (interactions[14][1] == 1))
                        {
                            if((items[1][0] == -1) && (items[2][0] == -1))
                            {
                                interactionsArray[14]->printLong();              // Print long <horcrux>
                                interactions[14][1] = false;                    // Set <horcrux> availability to false.
                                roomsVisited[6][1] = true;                      // Set Godrics Hallow to Available
                                items[1][0] = -3;                               // destroy necklace.
                            }
                            else
                            {
                                if(items[2][0] != -1)
                                    std::cout << "You need the <Sword> of Gryffindor to defeat Voldermort's Horcrux." << std::endl;
                                if(items[3][0] != -1)
                                    std::cout << "You need the necklace Horcrux." << std::endl;
                            }

                        }
                        movedRooms = false;
                        break;
                    }
                case 6:
                    {
                        if(parsedResponse->getInteraction() == 15 && (interactions[15][1] == 1))
                        {
                            interactionsArray[15]->printLong();         // print long cemetery
                        }
                        else if(parsedResponse->getInteraction() == 16 && (interactions[16][1] == 1))
                        {
                            interactionsArray[16]->printLong();         // print long house
                        }
                        else if(parsedResponse->getInteraction() == 17 && (interactions[17][1] == 1))
                        {
                            interactionsArray[17]->printLong();         // print long bathilda
                            interactions[17][1] = false;                // set bathilda false
                            interactions[15][1] = false;                // set temp false while in house
                            interactions[16][1] = false;                // set temp false while in house
                            interactions[18][1] = true;                 // set nagini available
                        }
                        movedRooms = false;
                        break;
                    }
                case 7:
                    {
                        if(parsedResponse->getInteraction() == 19 && (interactions[19][1] == 1))
                        {
                            interactionsArray[19]->printLong();         // print long Dobby
                            interactions[19][1] = false;                // set Dobby unavailable
                            interactions[20][1] = true;                 // set Draco to available.
                        }
                        movedRooms = false;
                        break;
                    }
                case 8:
                    {
                        if(parsedResponse->getInteraction() == 21 && (interactions[21][1] == 1))
                        {
                            interactionsArray[21]->printLong();         // print long grave
                            interactions[21][1] = false;                // set grave unavailable
                            interactions[22][1] = true;                  // set griphook available.
                        }
                        else if(parsedResponse->getInteraction() == 22 && (interactions[22][1] == 1))
                        {
                            interactionsArray[22]->printLong();         // print long griphook
                            interactions[22][1] = false;                // set grip hook unavailable.
                            roomsVisited[9][1] = true;                  // set gringots to available.
                        }
                        movedRooms = false;
                        break;
                    }
                case 9:
                    {
                        if(parsedResponse->getInteraction() == 23 && (interactions[23][1] == 1))
                        {
                            std::cout << "You need to cast a spell at the <Banker>" << std::endl;
                        }
                        else if(parsedResponse->getInteraction() == 24 && (interactions[24][1] == 1))
                        {
                            interactionsArray[24]->printLong();         // print long vault.
                            interactions[24][1] = false;                // set vault unavailable.
                            items[4][1] = true;                         // set Chalice Available.

                        }
                        movedRooms = false;
                        break;
                    }
                case 10:
                    {
                        if(parsedResponse->getInteraction() == 25 && (interactions[25][1] == 1))
                        {
                            interactionsArray[25]->printLong();         // print long aberforth
                            interactions[25][1] = false;                // set aberforth unavailable
                            interactions[26][1] = true;                   // set picture available.
                        }
                        else if(parsedResponse->getInteraction() == 26 && (interactions[26][1] == 1))
                        {
                            interactionsArray[26]->printLong();         // print long painting.
                            interactions[26][1] = false;                // set painting unavailable.
                            roomsVisited[11][1] = true;                 // set Room of Requirement available..
                            interactions[27][1] = true;                 // set students available.
                        }
                        movedRooms = false;
                        break;
                    }
                case 11:
                    {
                        if((parsedResponse->getInteraction() == 27) && (interactions[27][1] == 1))
                        {
                            interactionsArray[27]->printLong();         // print long students
                            interactions[28][1] = true;                 // set ginney available
                            interactions[27][1] = false;                 // set students unavailable.
                        }
                        else if((parsedResponse->getInteraction() == 28) && (interactions[28][1] == 1))
                        {
                            interactionsArray[28]->printLong();         // print long ginney
                            interactions[38][1] = true;                 // set headmaster to true
                            interactions[28][1] = false;                 // set ginney to false
                            canMove = 1;                                // print exit connections.
                        }
                        else if((parsedResponse->getInteraction() == 29) && (interactions[29][1] == 1))
                        {
                            if(items[5][0] == -1)
                            {
                                interactionsArray[29]->printLong();     // print long fire.
                                items[5][0] = -3;                       // destroy diadem.
                                interactions[35][1] = true;             // set hide available.
                                interactions[29][1] = false;            // set fire unavailable.
                                canMove = 1;                            // print connections.
                            }
                            else
                            {
                                std::cout << "You need the Ravenclaw <Diadem> in your inventory>" << std::endl;
                            }
                        }
                        movedRooms = false;
                        break;
                    }
                case 12:
                    {
                        if((parsedResponse->getInteraction() == 30) && (interactions[30][1] == 1))
                        {
                            interactionsArray[30]->printLong();         // print long luna
                            interactions[31][1] = true;                 // set helena true
                            interactions[30][1] = false;                // set luna false
                            canMove = 0;                                // dont print connections.
                        }
                        else if((parsedResponse->getInteraction() == 31) && (interactions[31][1] == 1))
                        {
                            interactionsArray[31]->printLong();         // print long helena
                            interactions[31][1] = false;                // set helena false.
                            items[5][1] = true;                         // set diadem available.
                            canMove = 1;                                // print connections.
                        }
                        movedRooms = false;
                        break;
                    }
                case 13:
                    {
                        if((parsedResponse->getInteraction() == 32) && (interactions[32][1] == 1))
                        {
                            interactionsArray[32]->printLong();         // print long neville.
                            interactions[33][1] = true;                 // set nagini available.
                            interactions[32][1] = false;                // set neville false.
                        }
                        else if((parsedResponse->getInteraction() == 33) && (interactions[33][1] == 1))
                        {
                            interactionsArray[33]->printLong();         // print long nagini
                            interactions[34][1] = true;                 // set voldemort true.
                            interactions[33][1] = false;                // set nagini false
                        }
                        movedRooms = false;
                        break;
                    }
                case 14:
                    {
                        if((parsedResponse->getInteraction() == 35) && (interactions[35][1] == 1))
                        {
                            interactionsArray[35]->printLong();         // print long hide.
                            interactions[36][1] = true;                 // set snape available.
                            interactions[35][1] = false;                // set hide unavailable.
                            canMove = 0;                                // dont print connections.
                        }
                        else if((parsedResponse->getInteraction() == 36) && (interactions[36][1] == 1))
                        {
                            interactionsArray[36]->printLong();         // print long snape
                            interactions[36][1] = false;                // set snape unavailable.
                            items[6][1] = true;                         // set diadem available.
                        }
                        else if((parsedResponse->getInteraction() == 37) && (interactions[37][1] == 1))
                        {
                            interactionsArray[37]->printLong();         // print long pensive
                            items[7][1] = true;                         // set resurrection stone available.
                            interactions[37][1] = false;                // set pensive unavailable.
                            canMove = 1;                                // print connections
                        }
                        movedRooms = false;
                        break;
                    }
                case 15:
                    {
                        if((parsedResponse->getInteraction() == 38) && (interactions[38][1] == 1))
                        {
                            interactionsArray[38]->printLong();         // print long headmaster
                            interactions[39][1] = true;                 // set mcgonogall true
                            interactions[38][1] = false;                // set headmaster false.
                            canMove = 0;                                // dont print connections
                        }
                        else if((parsedResponse->getInteraction() == 39) && (interactions[39][1] == 1))
                        {
                            interactionsArray[39]->printLong();         // print long mcgonogal
                            interactions[30][1] = true;                 // set luna to true.
                            interactions[39][1] = false;                // set mcgonogall to false.
                            canMove = 1;                                // print connections
                        }
                        movedRooms = false;
                        break;
                    }
                case 16:
                    {
                        if((parsedResponse->getInteraction() == 40) && (interactions[40][1] == 1))
                        {
                            interactionsArray[40]->printLong();         // print long destiny.
                            std::cout << std::endl;
                            displayAvada();
                            interactions[41][1] = true;                 // set light available.
                            interactions[40][1] = false;                // set destiny false.
                            movedRooms = false;
                            canMove = 0;                                // dont print connections
                            dontPrint = 1;
                        }
                        else if((parsedResponse->getInteraction() == 41) && (interactions[41][1] = 1))
                        {
                            interactionsArray[41]->printLong();         // print long light
                            interactions[32][1] = true;                 // set neville available.
                            items[7][0] = -3;                           // destroy stone.
                            printRoomData(userRoom, 3);                 // print long exit
                            currentRoom = 13;
                            movedRooms = true;
                        }
                        break;
                    }
                }
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
                            break;
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
                            break;
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
                            break;
                        }
                    case 3:
                        {
                            // if Dracos wand is in default room, is available, and user is in room 7
                            if((items[3][0] == 7) && (items[3][1] == true) && (currentRoom == 7))
                            {
                                itemsArray[3]->printLong();                 // print long
                                items[3][0] = -1;                           // put wand in inventory
                                roomsVisited[8][1] = true;                  // Set beach house to available.
                            }
                            else if((items[3][0] == currentRoom) && (items[3][1] == true))
                            {
                                items[3][0] = -1;
                                std::cout << "You picked up Draco's <Wand>." << std::endl;
                            }
                            else if(items[3][0] == -1)
                            {
                                std::cout << "Draco's <Wand> is already in your inventory." << std::endl;
                            }
                            break;

                        }
                    case 4:
                        {
                            if((items[4][0] == 9) && (items[4][1] == true) && (currentRoom == 9))
                            {
                                itemsArray[4]->printLong();                 // print long chalice
                                items[4][0] = -1;                           // put chalice in inventory.
                                roomsVisited[10][1] = true;                 // set hogsmeade to available.
                            }
                            else if((items[4][0] == currentRoom) && (items[4][1] == true))
                            {
                                items[4][0] = -1;                           // put item in inventory
                                std::cout << "You picked up the <Chalice> Horcrux." << std::endl;
                            }
                            else if(items[4][0] == -1)
                            {
                                std::cout << " The <Chalice> Horcrux is already in your inventory." << std::endl;
                            }
                            break;
                        }
                    case 5:
                        {
                            if((items[5][0] == 11) && (items[5][1] == true) && (currentRoom == 11))
                            {
                                itemsArray[5]->printLong();                 // print long diadem.
                                items[5][0] = -1;                           // place diadem in inventory
                                interactions[29][1] = true;                 // set fire available.
                                canMove = 0;                                // dont print connections.
                            }
                            else if((items[5][0] == currentRoom) && (items[5][1] == true))
                            {
                                items[5][0] = -1;
                                std::cout << "You picked up the <Diadem> Horcrux." << std::endl;
                            }
                            else if(items[5][0] == -1)
                            {
                                std::cout << "The <Diadem> Horcrux is already in your inventory." << std::endl;
                            }
                            break;
                        }
                    case 6:
                        {
                            if((items[6][0] == 14) && (items[6][1] == true) && (currentRoom == 14))
                            {
                                itemsArray[6]->printLong();                 // print long diadem.
                                items[6][0] = -1;                           // place diadem in inventory
                                interactions[37][1] = true;                 // set pensive available.
                            }
                            else if((items[5][0] == currentRoom) && (items[5][1] == true))
                            {
                                items[5][0] = -1;
                                std::cout << "You picked up the vial of Snape's <Memories>." << std::endl;
                            }
                            else if(items[5][0] == -1)
                            {
                                std::cout << "The vial of Snape's Memories is already in your inventory." << std::endl;
                            }
                            break;
                        }
                    case 7:
                        {
                            if((items[7][0] == 16) && (items[7][1] == true) && (currentRoom == 16))
                            {
                                if(items[0][0] == -1)
                                {
                                    itemsArray[7]->printLong();                 // print long stone.
                                    items[7][0] = -1;                           // place stone in inventory
                                    items[0][0] = -3;                           // destroy snitch.
                                    interactions[40][1] = true;                 // set destiny available.
                                }
                                else
                                {
                                    std::cout << "You need the Golden <Snitch> in your inventory to continue." << std::endl;
                                }

                            }
                            else if((items[5][0] == currentRoom) && (items[5][1] == true))
                            {
                                items[5][0] = -1;
                                std::cout << "You picked up The Resurrection <Stone>." << std::endl;
                            }
                            else if(items[5][0] == -1)
                            {
                                std::cout << "The Resurrection <Stone> is already in your inventory." << std::endl;
                            }
                            break;
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
                            std::cout << "You dropped Draco Malfloy's <Wand>." << std::endl;
                        else if(parsedResponse->getItem() == 4)
                            std::cout << "You dropped the <Chalice> Horcrux." << std::endl;
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
                    displayStupefy();
                    interactionsArray[5]->printLong();               // Print long <deatheater>
                    interactions[5][1] = false;                     // Set <deatheater> availability to false.
                    roomsVisited[3][1] = true;                      // Set Safe House available.
                    movedRooms = false;
                    break;
                }
            case 10:
                {
                    displayStupefy();
                    interactionsArray[10]->printLong();              // Print long <dolores>
                    interactions[10][1] = false;                    // Set <dolores> availability to false.
                    items[1][1] = true;                             // Set Necklace available.
                    break;
                }
            case 11:
                {
                    displayErecto();
                    interactionsArray[11]->printLong();              // Print long <tent>
                    interactions[11][1] = false;                    // Set <tent> availability to false.
                    interactions[12][1] = true;                     // Set <patronus> availability to true.
                    movedRooms = false;
                    break;
                }
            case 18:
                {
                    interactionsArray[18]->printLong();             // print long nagini
                    interactions[18][1] = false;                    // set nagini unavailable.
                    interactions[15][1] = true;                     // open up temp closed cemetery
                    interactions[16][1] = true;                     // open up temp closed childhood house
                    roomsVisited[7][1] = true;                      // Set malfloy manor to open.
                    break;
                }
            case 20:
                {
                    displayExpelliarmus();
                    interactionsArray[20]->printLong();             // print long Draco disarm
                    interactions[20][1] = false;                    // set draco disarm available to false
                    items[3][1] = true;                             // set wand to available.
                    break;
                }
            case 23:
                {
                    displayImperio();
                    interactionsArray[23]->printLong();             // print long banker.
                    interactions[23][1] = false;                    // set banker unavailable.
                    interactions[24][1] = true;                     // set vault available.
                    break;
                }
            case 34:
                {
                    displayExpelliarmus();
                    interactionsArray[34]->printLong();         // print long voldemort
                    std::cout << std::endl;
                    printRoomData(userRoom, 3);                 // print conclusion
                    displayCredits();
                    voldermortAlive = false;                    // kill voldemort.
                    break;
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

bool Game::loadDefault() {
    return loadFromFile("", true);
}

bool Game::loadFromFile(const std::string& fileName, const bool& isDefault) {

//If isDefault==true load default.dat file
std::ifstream fileStream("data/default.dat", std::ios_base::in);


    if(isDefault==false) {
        fileStream.close();
        fileStream.open(fileName, std::ios_base::in);
        std::cout << fileName << std::endl;
    }




    if (!fileStream.is_open()) {

        if(isDefault==true) {
            //Unable to open default.dat file, probably because it doesn't exist.
            //Create a brand new default.dat file:
            std::ofstream OFS("data/default.dat", std::ios_base::out | std::ios_base::trunc);
            OFS<<"0\r\n";
            OFS<<"0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1\r\n";
            OFS<<"1 0 4 0 5 0 7 0 9 0 11 0 14 0 16 0\r\n";
            //OFS<<"0 1 0 0 2 1 3 0 4 1 5 0 6 1 7 0 8 1 9 0 10 0 11 1 12 0 13 0 14 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0"; // Doesn't make sense but might need to revert back.
            OFS<<"0 1 0 0 1 1 1 0 2 1 2 0 3 1 3 0 4 1 4 0 4 0 5 1 5 0 5 0 5 0 6 1 6 1 6 1 6 0 7 1 7 0 8 1 8 0 9 1 9 0 10 1 10 0 11 0 11 0 11 0 12 0 12 0 13 0 13 0 13 0 14 0 14 0 14 0 15 0 15 0 16 0 16 0";
            OFS.close();

            //Open newly created default.dat
            fileStream.open("data/default.dat");
            if(!fileStream.is_open()) {
                return false;
            }
        } else {
            return false;
        }
    }

    if(isDefault==false) {
        //Skip saveName which is the in the first line inside a file
        std::string eatVal = "";
        std::getline(fileStream, eatVal);
    }
    int i = 0;

    fileStream>>currentRoom;

    //Read rooms
    for (i = 0; i < 17; i++)
    {
        int a;
        int b;

        fileStream >> a >> b;
        roomsVisited[i][0] = a;
        roomsVisited[i][1] = b;
    }

    //Read items
    for(i = 0; i < 8; i++)
    {
        int a;
        bool b;
        fileStream>>a>>b;
        items[i][0] = a;
        items[i][1] = b;
    }

    //Read interactions
    for(i=0; i < 42; i++){
        int a;
        bool b;
        fileStream >> a >> b;
        interactions[i][0] = a;
        interactions[i][1] = b;
    }


    fileStream.close();

    return true;
}

bool Game::saveGame(const std::string& saveName) {
    //Save variables to a file named <playerName>.save

    if(player.name=="") return false; //game not initialized yet

    std::ofstream saveFile("saved/" + player.name + "_" + Data::to_string(player.saves) + ".save",std::ios_base::out);


    if(!saveFile.is_open()) return false;

    int i = 0;
    //Store saveName
    saveFile << saveName << "\r\n";

    //Store current Room
    saveFile << currentRoom << "\r\n";

    //Read rooms
    for (i = 0; i < 17; i++)
    {
        saveFile << roomsVisited[i][0] << " " << roomsVisited[i][1] << " ";
    }


    saveFile << "\r\n";

    //Read items
    for(i = 0; i < 8; i++)
    {
        saveFile << items[i][0] << " " << items[i][1] << " ";
    }

    saveFile << "\r\n";

    //Read interactions
    for(i=0; i < 42; i++){
        saveFile << interactions[i][0] << " " << interactions[i][1] << " ";
    }


    saveFile.close();

    if (player.saves>=19) {
        player.saves=20;

    } else {
        player.saves=(player.saves%20)+1;
    }

    //Create a profile -> ReCreate a player profile file
    //Overwrite the file with a new one with updated "player.saves" variables
    createProfile(player, false);

    return true;
}

// Phase 1 logic check for moving rooms.
// Checks if nextRoom is either current room +1 or -1.
// Checks if nexRoom is available and returns true if both conditions are satisfied.
// False otherwise.
bool Game::moveLogicCheck(int nextRoom) const
{
    bool checker = true;
    if((nextRoom == 11) && (currentRoom == 10) && (roomsVisited[11][1] == true))
    {
        if(items[0][0] != -1)
        {
            std::cout << "You must possess the Golden <Snitch> in your inventory before traveling to Hogwarts." << std::endl;
            checker = false;
        }
        if(items[3][0] != -1)
        {
            std::cout << "You must possess Draco's <Wand> in your inventory before traveling to Hogwarts." << std::endl;
            checker = false;
        }
        if(items[4][0] != -1)
        {
            std::cout << "You must posses the Chalice Horcrux in your inventory before traveling to Hogwarts." << std::endl;
            checker = false;
        }

        if(checker == false)
        {
            return false;
        }
        else
        {
            return true;
        }

    }
    else if(currentRoom >= 11)
    {
        return false;
    }
    else if((nextRoom == (currentRoom+1)) && (roomsVisited[currentRoom+1][1] == true))
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

// function to print any items that are placed in a room by user.
// can disregard certain items to ensure long form is printed by switch
// used in phase 1 and phase 2
void Game::printItems(int disreguard)
{
    int i;
    //for(i = 0; i < 8; i++)
    std::cout << std::endl;
    for(i = 0; i < 8; i++)     // set to 3 because only 3 items right now.
    {
        if(i != disreguard)
        {
            if((items[i][0] == currentRoom) && (items[i][1] == true))
            {
                itemsArray[i]->printPickup();
                /*Change to short non interactive form*/
            }
        }

    }

}

// prints out all short interaction descriptions for the current room.
// used in both phase 1 and phase 2.
void Game::printInteractions()
{
    int i;
    std::cout << std::endl;
    for(i = 0; i < 42; i++)
    {
        if((interactions[i][0] == currentRoom) && (interactions[i][1] == 1))
        {
            interactionsArray[i]->printShort();
            if((interactions[34][0] == currentRoom) && (interactions[34][1] == 1))
            {
                displayAvada();
            }
        }

    }

}


// prints out the short or long entrance of the current room.
void Game::printEntrance(Data::Room *userRoom)
{
    if(roomsVisited[currentRoom][0] == 0)
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
    if(roomsVisited[currentRoom+1][1] == 1)
    {
        userRoom->printExitShort();
    }
}

//PHASE 2 FUNCTIONS FOR LOGIC AND PRINTING.

// Function that overrides the print short descriptions exits in the room data files.
// Need function because only 1 room is loaded at a time; however, there are multiple
//  rooms the user is able to go to.
// Print interactions function used in both phase 1 and phase 2
// Print items function used in both phase 1 and phase 2
void Game::printConnections()
{
    if(dontPrint != 1)
    {
        std::cout << "You look around Hogwarts and  can go to:" << std::endl;
        if((roomsVisited[11][1] == 1) && (currentRoom != 11))
            std::cout << "The Room of Requirement";
        if((roomsVisited[12][1] == 1) && (currentRoom != 12))
            std::cout << ", Ravenclaw Quarter";
        if((roomsVisited[13][1] == 1) && (currentRoom != 13))
            std::cout << ", the Courtyard";
        if((roomsVisited[14][1] == 1) && (currentRoom != 14))
            std::cout << ", the Boathouse";
        if((roomsVisited[15][1] == 1) && (currentRoom != 15))
            std::cout << ", the Great Hall";
        if((roomsVisited[16][1] == 1) && (currentRoom != 16))
            std::cout << ", the Enchanted Forest";
        std::cout << "." << std::endl;
    }

}

void Game::printRoomData(Data::Room *userRoom, int choice)
{
    if(choice == 0)         //print short entrance
    {
        userRoom->printShort();
    }
    else if(choice == 1)    // print long entrance
    {
        userRoom->printLong();
    }
    else if(choice == 2)    // print short exit, Not used because all rooms would need to be loaded for it to work.
    {
        userRoom->printExitShort();
    }
    else if(choice == 3)    // print long exit
    {
        userRoom->printExitLong();
    }
}

bool Game::moveLogicPhaseTwo(int nextRoom)
{
    if(nextRoom == -2)
    {
        std::cout << "Please select a Room to visit." << std::endl;
        return false;
    }
    else if(dontPrint == 1)
    {
        return false;
    }
    else if((nextRoom <= 16) && (nextRoom >= 11))
    {
        return true;
    }
    return false;
}

void Game::hardCodedDescriptions(int choice)
{
    if(choice == 0) // Room of Requirement New Hardcoded entrance after 31.Interaction completed.
    {
        std::cout << "You meet back up with Ron and Hermione. They inform you that they destroyed the chalice" << std::endl;
        std::cout << "Horcrux however, you could already feel it inside you earlier. You head to the Room of" << std::endl;
        std::cout << "Requirement and begin to look around for the diadem." << std::endl;
    }
    else if(choice == 1) // Room of Requirement New Hardcoded exit after 29.Interaction completed.
    {
        std::cout << "You leave the Room of Requirement, still on fire, you are unable to return." << std::endl;
    }
}



//ART

void outputAllLines(const std::string& fileName) {
	std::ifstream artFile(fileName, std::ios_base::in);
	std::string line = "";
	while (std::getline(artFile, line)) {
		std::cout << line << std::endl;
	}
	artFile.close(); //No need to do closing here, because it will go out of scope. But, good practice
}

void Game::displayArt(){
    outputAllLines("data/ART.txt");
}
void Game::displayAvada(){
    outputAllLines("data/AVADA.txt");
}
void Game::displayStupefy(){
    outputAllLines("data/STUPEFY.txt");
}
void Game::displayImperio(){
    outputAllLines("data/IMPERIO.txt");
}
void Game::displayErecto(){
    outputAllLines("data/ERECTO.txt");
}
void Game::displayExpelliarmus(){
    outputAllLines("data/EXPELIARMUS.txt");
}
void Game::displayCredits(){
    outputAllLines("data/CREDITS.txt");
}



