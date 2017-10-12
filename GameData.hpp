#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

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
	void loadData(const std::string& fileName);
private:
	std::string short_exit_desc;
	std::string long_exit_desc;
};

class Item : public GameData {
public:
	Item(const std::string& fileName) { loadData(fileName); }
private:
};

class Interaction : public GameData {
public:
	Interaction(const std::string& fileName) { loadData(fileName); }
private:
};

std::vector<Data::Item*> getItems(const int& NumberOfItems);
std::vector<Data::Interaction*> getInteractions(const int& NumberOfInteractions);
std::string to_string(int num);
};

#endif // GAMEDATA_H
