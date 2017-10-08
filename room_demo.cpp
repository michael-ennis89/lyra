/*
    MUST be compiled as 
        g++ -std=c++11 room_demo.cpp Room.cpp

*/
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include "Room.hpp"

using namespace std;

int main()
{
    Room room;
    string line, delimit("#@");
    
    ifstream ifs("test_room.txt");
    room.load(ifs, delimit);

    ofstream ofs("out_room.txt");
    room.save(ofs, delimit);
    
    return 0;
}
