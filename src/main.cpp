#include<vector>
#include<string>
#include<fstream>
#include<iostream>

#include "../src/GameData.hpp"
#include "../src/engine.hpp"
#include "../src/Response.hpp"
#include "../src/parser.hpp"

int main() {


    /*Data::Room* my_room = new Data::Room("0.room");

    std::cout << "ROOM 0 Data: \n";
    my_room->printShort();
    std::cout << "\n---\n";
    my_room->printLong();
    std::cout << "\n--------------------\n";
    my_room->printExitLong();
    std::cout << "\n---\n";
    my_room->printExitShort();
    std::cout << "\n--------------------\n";

    std::cout << "\n";

    std::vector<Data::Item*> itemsArray = Data::getItems(3);

    std::cout << "Items Data: \n";
    for(Data::Item* e:itemsArray){
        if (e->good()){
            e->printShort();
            std::cout << "\n---\n";
            e->printLong();
            std::cout << "\n--------------\n";
            e->printPickup();
            std::cout << "\n---\n";
            e->printDrop();
        }
        delete e;
    }
    itemsArray.clear();
    std::cout << "\n";

    std::vector<Data::Interaction*> interactionsArray = Data::getInteractions(3);

    std::cout << "\nInteractions Data: \n";
    for(Data::Interaction* e:interactionsArray) {
        if(e->good()){
            e->printLong();
            std::cout << "\n---\n";
            e->printShort();
            std::cout << "\n---\n";
        }
        delete e;
    }
    interactionsArray.clear();
    delete my_room;
    */

    Game *myGame;
    myGame = new Game();
    myGame->Run();

    //Call destructor
    delete myGame;

    char ch; std::cin>>ch;
    return 0;

}

