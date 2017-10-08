/*
    A class to represent a Room 
    
    must be compiled as C++11
    e.g
        $ g++ -std=c++11 -c Room.cpp
*/


#include "Room.hpp"
#include<iostream>
#include<fstream>
#include<string>

//Set the room description
void Room::set_desc(std::string& desc, bool is_long_desc){
    if(is_long_desc)
        this->long_desc = desc;
    else
        this->short_desc = desc;
}      

//Display the room description in the standard output
void Room::show_desc(bool show_long_desc){
    if(show_long_desc)
        std::cout<<this->long_desc;
    else
        std::cout<<this->short_desc;
}

//Save the content of a room object into a text file
//NB: sec_delimit is a section delimiter; hence, MUST NOT appear in the data
void Room::save(std::ofstream& ofs, const std::string& sec_delimit)
{
    ofs<<room_no<<std::endl;    //Write the room number
    ofs<<sec_delimit<<std::endl;
    
    ofs<<std::boolalpha<<this->is_visited<<std::endl;   //Write the room state
    ofs<<sec_delimit<<std::endl;

    //Write the features
    std::cout<<"size: "<<this->features.size()<<std::endl;
    for(auto it = this->features.begin(); it != this->features.end(); ++it)
    {
        ofs<<*it<<std::endl;
    }
    ofs<<sec_delimit<<std::endl;    
    
    //Write the long description.
    ofs<<this->short_desc<<std::endl;
    ofs<<sec_delimit<<std::endl;

    //Write the long description.
    ofs<<this->long_desc<<std::endl;
    ofs<<sec_delimit<<std::endl;

    //
    for(auto it = this->objects.begin(); it != this->objects.end(); ++it)
    {
        ofs<<*it<<std::endl;
    }

    ofs<<sec_delimit<<std::endl;
}

//Read the contents of an object from a text file
void Room::load(std::ifstream& ifs, const std::string& sec_delimit)
{
    std::string line, dummy;

    ifs>>this->room_no; //Read in the room
    ifs>>dummy; //Read the delimiter

    //Read the room state
    ifs>>std::boolalpha>>this->is_visited;    
    ifs>>dummy;
    ifs.ignore(1, '\n');
    
    //Read room features    
    this->features.clear();    
    while(std::getline(ifs, line)){
        if(line == sec_delimit)
            break;
        
        this->features.push_back(line);
    }

    //Read the short descriptions
    while(std::getline(ifs, line)){
        if(line == sec_delimit){
            this->short_desc.pop_back();    //Remove the extra new-line at the end 
            break;
        }
        this->short_desc.append(line + '\n');
    }
    
    //Read the long descriptions
    while(std::getline(ifs, line)){
        if(line == sec_delimit){
            this->long_desc.pop_back(); //Remove the extra new-line at end 
            break;
        }
        
        this->long_desc.append(line + '\n');
    }
    
    //Read room objects 
    this->objects.clear();     
    while(std::getline(ifs, line)){
        if(line == sec_delimit)
            break;
        this->objects.push_back(line);
    }
}
