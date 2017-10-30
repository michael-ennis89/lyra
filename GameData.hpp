#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>



    /*
    FILE FORMAT: Interaction
        Short Description Entrance
        Long Description Entrance


    FILE FORMAT: Room
        Short Description Entrance
        Long Description Entrance
        Short Description Exit
        Long Description Exit


    FILE FORMAT: Item
        Short Description Entrance
        Long Description Entrance
        Pickup Description
        Drop Description

    */



namespace Data{

class GameData {
public:
	void printLong() const;
	void printShort() const;

	//Check if the file has loaded data correctly
	bool good() const;

	virtual ~GameData() {}
protected:
	GameData() {};
	void setState(const bool& isOk);
	virtual void loadData(const std::string& fileName);
	std::string short_desc;
	std::string long_desc;
private:
	GameData(const GameData&);
	GameData& operator=(const GameData&);
	bool isGood;
};

class Room : public GameData {
public:
	Room(const std::string& fileName) { loadData(fileName); };
	void printExitShort() const;
	void printExitLong() const;
	void loadData(const std::string& fileName) override;
private:
	std::string short_exit_desc;
	std::string long_exit_desc;
};

class Item : public GameData {
public:
	Item(const std::string& fileName) { loadData(fileName); }
	void printPickup() const;
	void printDrop() const;
	void loadData(const std::string&) override;
private:
    std::string pickup_desc;
    std::string drop_desc;
};

class Interaction : public GameData {
public:
	Interaction(const std::string& fileName) { loadData(fileName); }
private:
};

std::vector<Data::Item*> getItems(const int& NumberOfItems);
std::vector<Data::Interaction*> getInteractions(const int& NumberOfInteractions);
std::string to_string(unsigned int num);
};

#endif // GAMEDATA_HPP
