/*A class to represent a Room */

#ifndef __ROOM_H__ 
#define __ROOM_H__

#include<vector>
#include<string>
#include<fstream>

class Room {
    private:
        int room_no;
        bool is_visited;
        std::vector<std::string> features;   
        std::string long_desc;
        std::string short_desc;
        std::vector<std::string> objects;    //List of objects drop in the room
    
    public:
        Room(){
            this->is_visited = false;
        }
        Room(int no, std::vector<std::string>& features,
            std::string& long_desc, std::string& short_desc,
            std::vector<std::string>& objects){
                this->room_no = no;
                this->is_visited = false;
                this->features = features;
                this->long_desc = long_desc;
                this->short_desc = short_desc;
                this->objects = objects;
        }
        void set_desc(std::string& desc, bool is_long_desc);
        void show_desc(bool show_long_desc);
        void load(std::ifstream& ifs, const std::string& sec_delimit);
        void save(std::ofstream& os, const std::string& sec_delimit);
};

#endif
