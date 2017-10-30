#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "Response.hpp"
#include "parser.hpp"


Response Parser::parse(std::string command)
{
	Response responseObj;
	Response* responsePtr = &responseObj;
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
	if (finalTokens->at(0) == "look" ||
			finalTokens->at(0) == "help" ||
			finalTokens->at(0) == "inventory" ||
			finalTokens->at(0) == "save")
	{responsePtr->setCommand(1);}

	if (finalTokens->at(0) == "go")
	{responsePtr->setCommand(2);}

	if (finalTokens->at(0) == "look" && finalTokens->at(1) == "at")
	{responsePtr->setCommand(3);}

	if (finalTokens->at(0) == "take" || finalTokens->at(0) == "drop")
	{responsePtr->setCommand(4);}

	if (finalTokens->at(0) == "cast" && finalTokens->at(1) == "spell" && finalTokens->at(2) == "at")
	{responsePtr->setCommand(5);}

}

void Parser::evalOption(std::vector<std::string>* finalTokens, Response* responsePtr)
{
	if (responsePtr->getCommand() == 1) //basic command
	{
		if (finalTokens->at(0) == "look")
		{responsePtr->setOption(1);}
	
		if (finalTokens->at(0) == "help")
		{responsePtr->setOption(2);}

		if (finalTokens->at(0) == "inventory")
		{responsePtr->setOption(3);}

		if (finalTokens->at(0) == "save")
		{responsePtr->setOption(4);}
	}

	if (responsePtr->getCommand() == 2) //move command
	{
		int index = 1;
		if (finalTokens->at(1) == "to") //handles "move door" and "move to door"
		{index = 2;}
		if(finalTokens->size() >= index+2)
		{
			if(finalTokens->at(index) == "harry\'s" && finalTokens->at(index+1) == "house")
			{responsePtr->setRoom(0);}
			if(finalTokens->at(index) == "london" && finalTokens->at(index+1) == "diner")
			{responsePtr->setRoom(2);}
			if(finalTokens->at(index) == "safe" && finalTokens->at(index+1) == "house")
    		{responsePtr->setRoom(3);}
			if(finalTokens->at(index) == "godric\'s" && finalTokens->at(index+1) == "hallow")
			{responsePtr->setRoom(6);}
			if(finalTokens->at(index) == "malfloy" && finalTokens->at(index+1) == "manor")	
			{responsePtr->setRoom(7);}
			if(finalTokens->at(index) == "beach" && finalTokens->at(index+1) == "house")
			{responsePtr->setRoom(8);}
			if(finalTokens->at(index) == "gringot" && finalTokens->at(index+1) == "bank")
			{responsePtr->setRoom(9);}
			if(finalTokens->at(index) == "ravenclaw" && finalTokens->at(index+1) == "tower")
			{responsePtr->setRoom(12);}
			if(finalTokens->at(index) == "great" && finalTokens->at(index+1) == "hall")
			{responsePtr->setRoom(15);}
			if(finalTokens->at(index) == "enchanted" && finalTokens->at(index+1) == "forest")
			{responsePtr->setRoom(16);}
		}

		if(finalTokens->size() >= index+3)
		{
			if(finalTokens->at(index) == "room" && finalTokens->at(index+1) == "of" && finalTokens->at(index+2) == "requirement")
			{responsePtr->setRoom(11);}

		}

		if(finalTokens->at(index) == "burrow") //parser removes "the"
		{responsePtr->setRoom(1);}
		if(finalTokens->at(index) == "headquarters")
		{responsePtr->setRoom(4);}
		if(finalTokens->at(index) == "forest")
		{responsePtr->setRoom(5);}
		if(finalTokens->at(index) == "hogsmeade")
		{responsePtr->setRoom(10);}
		if(finalTokens->at(index) == "courtyard")
		{responsePtr->setRoom(13);}
		if(finalTokens->at(index) == "boathouse")
		{responsePtr->setRoom(14);}
		}

	if (responsePtr->getCommand() == 3) //interaction
	{
		if (finalTokens->at(2) == "potion")
		{responsePtr->setInteraction(0);}
		if (finalTokens->at(2) == "clothes")
		{responsePtr->setInteraction(1);}
		if (finalTokens->at(2) == "will")
		{responsePtr->setInteraction(2);}
		if (finalTokens->at(2) == "wedding")
		{responsePtr->setInteraction(3);}
		if (finalTokens->at(2) == "server")
		{responsePtr->setInteraction(4);}
		if(finalTokens->size() >= 4)
		{
			if (finalTokens->at(2) == "death" && finalTokens->at(3) == "eater")
			{responsePtr->setInteraction(5);}
		}
		if (finalTokens->at(2) == "cupboard")
		{responsePtr->setInteraction(6);}
		if (finalTokens->at(2) == "mundungus")
		{responsePtr->setInteraction(7);}
		if (finalTokens->at(2) == "toilet")
		{responsePtr->setInteraction(8);}
		if (finalTokens->at(2) == "elevator")
		{responsePtr->setInteraction(9);}
		if (finalTokens->at(2) == "dolores")
		{responsePtr->setInteraction(10);}
		if (finalTokens->at(2) == "tent")
		{responsePtr->setInteraction(11);}
		if (finalTokens->at(2) == "patronus")
		{responsePtr->setInteraction(12);}
		if (finalTokens->at(2) == "lake")
		{responsePtr->setInteraction(13);}
		if (finalTokens->at(2) == "horcrux")
		{responsePtr->setInteraction(14);}
		if (finalTokens->at(2) == "graveyard")
		{responsePtr->setInteraction(15);}
		if (finalTokens->at(2) == "house")
		{responsePtr->setInteraction(16);}
		if (finalTokens->at(2) == "bathilda")
		{responsePtr->setInteraction(17);}
		if (finalTokens->at(2) == "nagini")
		{responsePtr->setInteraction(18);}

	}

	if (responsePtr->getCommand() == 4) //item
	{
		//set option for take or drop
		if (finalTokens->at(0) == "take")
		{responsePtr->setOption(1);}
		if (finalTokens->at(0) == "drop")
		{responsePtr->setOption(2);}

		//set item number
		if(finalTokens->at(1) == "snitch")
		{responsePtr->setItem(0);}
		if(finalTokens->at(1) == "necklace")
		{responsePtr->setItem(1);}
		if(finalTokens->at(1) == "sword")
		{responsePtr->setItem(2);}
		if(finalTokens->at(1) == "wand")
		{responsePtr->setItem(3);}
		if(finalTokens->at(1) == "chalice")
		{responsePtr->setItem(4);}
		if(finalTokens->at(1) == "diadem")
		{responsePtr->setItem(5);}
		if(finalTokens->at(1) == "memories")
		{responsePtr->setItem(6);}
		if(finalTokens->at(1) == "stone")
		{responsePtr->setItem(7);}
	}

	if (responsePtr->getCommand() == 5) //spell
	{
		if(finalTokens->at(3) == "death" && finalTokens->at(4) == "eater")
		{responsePtr->setInteraction(5);}

		if(finalTokens->at(3) == "tent")
		{responsePtr->setInteraction(11);}

	}	
}