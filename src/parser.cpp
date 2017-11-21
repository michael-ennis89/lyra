#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "Response.hpp"
#include "parser.hpp"
#include <algorithm>

Response Parser::parse(std::string command)
{
	Response responseObj;
	Response* responsePtr = &responseObj;
	std::transform(command.begin(), command.end(), command.begin(), ::tolower);
	std::string* strPtr = &command;
	std::vector<std::string> tokens;
	std::vector<std::string>* tokensPtr = &tokens;
	std::vector<std::string> finalTokens;
	std::vector<std::string>* finalPtr = &finalTokens;
	Parser::stripPunc(strPtr);
	Parser::tokenizer(strPtr, tokensPtr);
	Parser::stripArticles(tokensPtr, finalPtr);
	Parser::evalCommand(finalPtr, responsePtr);
	Parser::evalOption(finalPtr, responsePtr);

	return responseObj;

}

void Parser::stripPunc(std::string* inputString)
{
		std::size_t position; //position within string while using find()
		std::size_t strSize = inputString->size();
		std::string punctuation[3] = {"?",".","!"}; //punctuation to remove
		for(int i = 0; i <3; i++)
		{
			do
			{
				position = inputString->find(punctuation[i]);
				if (position != std::string::npos) //if found replace with space
				{
					inputString->replace(position, 1, " ");
				}
			} while(position < strSize);

		}

		//std::cout << *inputString << std::endl; //for command line testing. remove
}

void Parser::tokenizer(std::string* inputString,	std::vector<std::string>* tokens)
{

    //http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
	std::string buffer;
	std::stringstream stream(*inputString);

	while (stream >> buffer)
	{
		tokens->push_back(buffer);
	}
}

void Parser::stripArticles(std::vector<std::string>* tokens, std::vector<std::string>* finalTokens)
{
		for(int i = 0; i < tokens->size(); i++)
		{
			if (tokens->at(i) != "the" && tokens->at(i) != "a" && tokens->at(i) != "an")
			{
				finalTokens->push_back(tokens->at(i));
				//std::cout << tokens->at(i) << std::endl;
			}
		}
}

void Parser::evalCommand(std::vector<std::string>*finalTokens, Response* responsePtr)
{
	int tokensSize = finalTokens->size();
	if (tokensSize <=0) //if no tokens, don't try to access them
	{return;}

	if(tokensSize >= 4)
	{
		if (finalTokens->at(0) == "cast" && finalTokens->at(1) == "spell" && finalTokens->at(2) == "at")
	{responsePtr->setCommand(5);}
	}

	//need to check for "look at" before checking for "look"
	else if (tokensSize >= 3)
	{
		if (finalTokens->at(0) == "look" && finalTokens->at(1) == "at")
		{responsePtr->setCommand(3);}
		else if (finalTokens->at(0) == "go" || finalTokens->at(0) == "move")
		{responsePtr->setCommand(2);}
	}
 
	else if (finalTokens->at(0) == "look" ||
			finalTokens->at(0) == "help" ||
			finalTokens->at(0) == "inventory" ||
			finalTokens->at(0) == "save")
	{responsePtr->setCommand(1);}

	else if (finalTokens->at(0) == "go" || finalTokens->at(0) == "move")
		{responsePtr->setCommand(2);}

	
	else if (finalTokens->at(0) == "take" || finalTokens->at(0) == "drop")
	{responsePtr->setCommand(4);}

}

void Parser::evalOption(std::vector<std::string>* finalTokens, Response* responsePtr)
{
	int tokensSize = finalTokens->size();
	if (tokensSize <=0) //if no tokens, don't try to access them
	{return;}
	if (responsePtr->getCommand() == 1) //basic command
	{
		if (finalTokens->at(0) == "look")
		{responsePtr->setOption(1);}

		else if (finalTokens->at(0) == "help")
		{responsePtr->setOption(2);}

		else if (finalTokens->at(0) == "inventory")
		{responsePtr->setOption(3);}

		else if (finalTokens->at(0) == "save")
		{responsePtr->setOption(4);}
	}

	else if (responsePtr->getCommand() == 2) //move command
	{
		if (tokensSize <=1) //if command is just "move"
		{return;}

		int index = 1;

		if (tokensSize >=2)
		{
			if (finalTokens->at(1) == "back") //"move back" or "go back"
			{responsePtr->setRoom(-2);}
			else if (finalTokens->at(1) == "to") //handles "move door" and "move to door"
			{index = 2;}
		}


		if(tokensSize >= index+2)
		{
			if(finalTokens->at(index) == "ravenclaw" && finalTokens->at(index+1) == "tower")
			{responsePtr->setRoom(12);}
			else if(finalTokens->at(index) == "great" && finalTokens->at(index+1) == "hall")
			{responsePtr->setRoom(15);}
			else if(finalTokens->at(index) == "enchanted" && finalTokens->at(index+1) == "forest")
			{responsePtr->setRoom(16);}
		}

		if(tokensSize >= index+3)
		{
			if(finalTokens->at(index) == "room" && finalTokens->at(index+1) == "of" && finalTokens->at(index+2) == "requirement")
			{responsePtr->setRoom(11);}

		}

		if(finalTokens->at(index) == "motorcycle")  //changed to motorcycle instead of the burrow
		{responsePtr->setRoom(1);}
		else if(finalTokens->at(index) == "away")        // added in addition to london diner
        {responsePtr->setRoom(2);}
        else if(finalTokens->at(index) == "safe")        // added in addition to safe house
        {responsePtr->setRoom(3);}
		else if(finalTokens->at(index) == "headquarters")
		{responsePtr->setRoom(4);}
		else if(finalTokens->at(index) == "fireplace")   // changed to fireplace instead of forest
		{responsePtr->setRoom(5);}
		else if(finalTokens->at(index) == "hollow")      // added in addition to godrics hallow
        {responsePtr->setRoom(6);}
		else if(finalTokens->at(index) == "forrest")
		{responsePtr->setRoom(7);}
		else if(finalTokens->at(index) == "beach")
		{responsePtr->setRoom(8);}
		else if(finalTokens->at(index) == "bank")
		{responsePtr->setRoom(9);}
		else if(finalTokens->at(index) == "dragon")
		{responsePtr->setRoom(10);}
		else if(finalTokens->at(index) == "tunnel")
		{responsePtr->setRoom(11);}
		else if(finalTokens->at(index) == "courtyard")
		{responsePtr->setRoom(13);}
		else if(finalTokens->at(index) == "boathouse")
		{responsePtr->setRoom(14);}
		else if(finalTokens->at(index) == "greathall")
		{responsePtr->setRoom(15);}
	}
	else if (responsePtr->getCommand() == 3) //interaction
	{
		if (tokensSize <=2)
		{return;}

		if (finalTokens->at(2) == "potion" || finalTokens->at(2) == "polyjuice")
		{responsePtr->setInteraction(0);}
		else if (finalTokens->at(2) == "clothes")
		{responsePtr->setInteraction(1);}
		else if (finalTokens->at(2) == "will")
		{responsePtr->setInteraction(2);}
		else if (finalTokens->at(2) == "wedding")
		{responsePtr->setInteraction(3);}
		else if (finalTokens->at(2) == "server")
		{responsePtr->setInteraction(4);}
		else if(tokensSize >= 4)
		{
			if (finalTokens->at(2) == "death" && finalTokens->at(3) == "eater")
			{responsePtr->setInteraction(5);}
		}
		else if (finalTokens->at(2) == "deatheater")
        {responsePtr->setInteraction(5);}
		else if (finalTokens->at(2) == "cupboard")
		{responsePtr->setInteraction(6);}
		else if (finalTokens->at(2) == "mundungus")
		{responsePtr->setInteraction(7);}
		else if (finalTokens->at(2) == "toilet")
		{responsePtr->setInteraction(8);}
		else if (finalTokens->at(2) == "elevator")
		{responsePtr->setInteraction(9);}
		//if (finalTokens->at(2) == "dolores")      // changed to spell interaction
		//{responsePtr->setInteraction(10);}
		else if (finalTokens->at(2) == "tent")
		{responsePtr->setInteraction(11);}
		else if (finalTokens->at(2) == "patronus")
		{responsePtr->setInteraction(12);}
		else if (finalTokens->at(2) == "lake")
		{responsePtr->setInteraction(13);}
		else if (finalTokens->at(2) == "horcrux")
		{responsePtr->setInteraction(14);}
		else if (finalTokens->at(2) == "cemetery") //was graveyard
		{responsePtr->setInteraction(15);}
		else if (finalTokens->at(2) == "house")
		{responsePtr->setInteraction(16);}
		else if (finalTokens->at(2) == "bathilda")
		{responsePtr->setInteraction(17);}
		else if (finalTokens->at(2) == "nagini")
		{responsePtr->setInteraction(18);}
		else if (finalTokens->at(2) == "doby")
		{responsePtr->setInteraction(19);}
		else if (finalTokens->at(2) == "draco")
		{responsePtr->setInteraction(20);}
		else if (finalTokens->at(2) == "grave")
		{responsePtr->setInteraction(21);}
		else if (finalTokens->at(2) == "griphook")
		{responsePtr->setInteraction(22);}
		else if (finalTokens->at(2) == "banker")
		{responsePtr->setInteraction(23);}
		else if (finalTokens->at(2) == "vault")
		{responsePtr->setInteraction(24);}
		else if (finalTokens->at(2) == "aberforth")
		{responsePtr->setInteraction(25);}
		else if (finalTokens->at(2) == "painting")
		{responsePtr->setInteraction(26);}
		else if (finalTokens->at(2) == "students")
		{responsePtr->setInteraction(27);}
		else if (finalTokens->at(2) == "ginney")
		{responsePtr->setInteraction(28);}
		else if (finalTokens->at(2) == "fire")
		{responsePtr->setInteraction(29);}
		else if (finalTokens->at(2) == "luna")
		{responsePtr->setInteraction(30);}
		else if (finalTokens->at(2) == "helena")
		{responsePtr->setInteraction(31);}
		else if (finalTokens->at(2) == "neville")
		{responsePtr->setInteraction(32);}
		else if (finalTokens->at(2) == "nagini")
		{responsePtr->setInteraction(33);}
		else if (finalTokens->at(2) == "voldemort") //possible typo both are interaction 32
		{responsePtr->setInteraction(34);}
		else if (finalTokens->at(2) == "hide")
		{responsePtr->setInteraction(35);}
		else if (finalTokens->at(2) == "snape")
		{responsePtr->setInteraction(36);}
		else if (finalTokens->at(2) == "pensive")
		{responsePtr->setInteraction(37);}
		else if (finalTokens->at(2) == "headmaster")
		{responsePtr->setInteraction(38);}
		else if (finalTokens->at(2) == "mcgonagall")
		{responsePtr->setInteraction(39);}
		else if (finalTokens->at(2) == "destiny")
		{responsePtr->setInteraction(40);}
		else if (finalTokens->at(2) == "light")
		{responsePtr->setInteraction(41);}

	}

	else if (responsePtr->getCommand() == 4) //item
	{
		if (tokensSize <=1)
		{return;}
		//set option for take or drop
		if (finalTokens->at(0) == "take")
		{responsePtr->setOption(1);}
		else if (finalTokens->at(0) == "drop")
		{responsePtr->setOption(2);}

		//set item number
		if(finalTokens->at(1) == "snitch")
		{responsePtr->setItem(0);}
		else if(finalTokens->at(1) == "necklace")
		{responsePtr->setItem(1);}
		else if(finalTokens->at(1) == "sword")
		{responsePtr->setItem(2);}
		else if(finalTokens->at(1) == "wand")
		{responsePtr->setItem(3);}
		else if(finalTokens->at(1) == "chalice")
		{responsePtr->setItem(4);}
		else if(finalTokens->at(1) == "diadem")
		{responsePtr->setItem(5);}
		else if(finalTokens->at(1) == "memories")
		{responsePtr->setItem(6);}
		else if(finalTokens->at(1) == "stone")
		{responsePtr->setItem(7);}
	}

	else if (responsePtr->getCommand() == 5) //spell
	{
		if (tokensSize <=3)
		{return;}
	
		if(finalTokens->at(3) == "death" && finalTokens->at(4) == "eater")
		{responsePtr->setInteraction(5);}

		else if(finalTokens->at(3) == "deatheater")
        {responsePtr->setInteraction(5);}     // added single word form of death eater.

        else if((finalTokens->at(3) == "dolores") || (finalTokens->at(3) == "Dolores"))     // changed dolores to a spell instead of a look at interaction
        {responsePtr->setInteraction(10);}

		else if(finalTokens->at(3) == "tent")
		{responsePtr->setInteraction(11);}
	}
}
