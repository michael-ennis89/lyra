#include "./src/engine.hpp"
#include "./src/Response.hpp"
#include "./src/parser.hpp"
#include "./src/GameData.hpp"

#include<vector>
#include<string>
#include<fstream>
#include<iostream>


int main() {

    /*
    Data::Room* my_room = new Data::Room("0.room");

    std::cout << "ROOM 0 Data: \n";
    my_room->printShort();
    my_room->printLong();
    my_room->printExitLong();
    my_room->printExitShort();

    std::cout << "\n";

    std::vector<Data::Item*> itemsArray = Data::getItems(3);

    std::cout << "Items Data: \n";
    for(Data::Item* e:itemsArray){
        if (e->good()){
            e->printShort();
            e->printLong();
        }
        delete e;
    }
    itemsArray.clear();
    std::cout << "\n";
    std::vector<Data::Interaction*> interactionsArray = Data::getInteractions(3);

    std::cout << "Interactions Data: \n";
    for(Data::Interaction* e:interactionsArray) {
        if(e->good()){
            e->printLong();
            e->printShort();
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

    char ch;
    std::cin >> ch;
    return 0;

}

