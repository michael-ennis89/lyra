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

void Data::Item::printPickup() const {
    printV(pickup_desc);
}
void Data::Item::printDrop() const {
    printV(drop_desc);
}

void Data::GameData::setState(const bool& isOk) {
    isGood=isOk;
}

bool Data::GameData::good() const {
    return isGood;
}

bool openFile(const std::string& fileName, std::ifstream& ifs) {
    ifs.open("data/" + fileName, std::ios_base::in);
    return ifs.good();
}

void Data::GameData::loadData(const std::string& fileName) {
    std::ifstream fileStream;
    setState(openFile(fileName, fileStream));

    if(good()) {
        std::getline(fileStream, short_desc);
        std::getline(fileStream, long_desc);
        fileStream.close();
    }

}

void Data::Room::loadData(const std::string& fileName) {
    std::ifstream fileStream;
    setState(openFile(fileName, fileStream));

    if(good()) {
        std::getline(fileStream, short_desc);
        std::getline(fileStream, long_desc);
        std::getline(fileStream, short_exit_desc);
        std::getline(fileStream, long_exit_desc);
        fileStream.close();
    }
}

void Data::Item::loadData(const std::string& fileName) {
    std::ifstream fileStream;
    setState(openFile(fileName, fileStream));

    if(good()) {
        std::getline(fileStream, short_desc);
        std::getline(fileStream, long_desc);
        std::getline(fileStream, pickup_desc);
        std::getline(fileStream, drop_desc);
        fileStream.close();
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


