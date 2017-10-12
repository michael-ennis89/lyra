/*
    MUST be compiled as
        g++ -std=c++11 room_demo.cpp Room.cpp

*/
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include "GameData.hpp"

int main()
{


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

    delete my_room;
    char ch; std::cin>>ch;
    return 0;
}
