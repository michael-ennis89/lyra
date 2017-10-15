#include "GameData.hpp"

void printV(const std::string& str) {
    std::cout << str << std::endl;
}
void Data::GameData::printLong() const {
    printV(long_desc);
}
void Data::GameData::printShort() const {
    printV(short_desc);
}

void Data::Room::printExitLong() const {
    printV(long_exit_desc);
}

void Data::Room::printExitShort() const {
    printV(short_exit_desc);
}

void Data::GameData::setState(const bool& isOk) {
    isGood=isOk;
}

bool Data::GameData::good() const {
    return isGood;
}

void Data::GameData::loadData(const std::string& fileName) {
    std::ifstream fileStream("data/" + fileName, std::ios_base::in);
    if(!fileStream.good()) {
        setState(false);
    } else {

        /*
        FILE FORMAT:
            Short Description Entrance
            Long Description Entrance
        */

        std::getline(fileStream, short_desc);
        std::getline(fileStream, long_desc);
        fileStream.close();
        setState(true);
    }
}

void Data::Room::loadData(const std::string& fileName) {
    std::ifstream fileStream("data/" + fileName, std::ios_base::in);
    if(!fileStream.good()) {
        setState(false);
    } else {

        /*
        FILE FORMAT:
            Short Description Entrance
            Long Description Entrance
            Short Description Exit
            Long Description Exit
        */
        std::getline(fileStream, short_desc);
        std::getline(fileStream, long_desc);
        std::getline(fileStream, short_exit_desc);
        std::getline(fileStream, long_exit_desc);

        fileStream.close();
        setState(true);
    }
}

std::string Data::to_string(unsigned int num) {
    std::string res = "";
    if(num==0) return "0";
    while(num){
        res+=char((num%10)+'0');
        num/=10;
    }

    std::reverse(res.begin(), res.end());
    return res;
}

std::vector<Data::Item*> Data::getItems(const int& NumberOfItems){
    std::vector<Data::Item*> items;

    for(size_t i=0; i<NumberOfItems; i++){
        Data::Item* item = new Data::Item(Data::to_string(i) + ".item");
		items.push_back(item);
    }

    return items;
}

std::vector<Data::Interaction*> Data::getInteractions(const int& NumberOfInteractions){
    std::vector<Data::Interaction*> interactions;

    for(size_t i=0; i<NumberOfInteractions; i++){
        Data::Interaction* interaction = new Data::Interaction(Data::to_string(i) + ".interaction");
        interactions.push_back(interaction);
    }

    return interactions;
}


