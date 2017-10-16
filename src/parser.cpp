#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "Response.hpp"
#include "parser.hpp"

//Parser::Parser()
//{
//	//instantiate a response object for the class to use??? 
//}


//Response Parse(std::string command, std::vector<std::string> inventory,
//	std::vector<std::string> roomItems, std::vector<std::string> roomExits)
//{
//	Response responseObj;
	//Response* responsePtr;
	//std::string* strptr = &command;
	//std::vector<std::string> tokens;
	//std::vector<std::string>* tokensptr = &tokens;
	//std::vector<std::string> finalTokens;
	//std::vector<std::string>* finalptr = &finalTokens;

	//std::vector<std::string>* inventoryPtr= &inventory;
	//std::vector<std::string>* roomItemsPtr= &roomItems;
	//std::vector<std::string>* roomExitsPtr= &roomExits;

	//stripPunc(strptr);
	//tokenizer(strptr, tokensptr);
	//stripArticles(tokensptr, finalptr);



//	return responseObj;
//}

int Parser::stripPunc(std::string* inputString)
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

int Parser::tokenizer(std::string* inputString,	std::vector<std::string>* tokens)
{

    //http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
	std::string buffer;
	std::stringstream stream(*inputString);

	while (stream >> buffer)
	{
		tokens->push_back(buffer);
	}
}

int Parser::stripArticles(std::vector<std::string>* tokens, std::vector<std::string>* finalTokens)
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

void Parser::evalCommand(std::vector<std::string>* finalTokens, Response* responsePtr)
{
	if (finalTokens->at(0) == "look" ||
			finalTokens->at(0) == "help" ||
			finalTokens->at(0) == "inventory" ||
			finalTokens->at(0) == "save")
	{responsePtr->setCommand(1);}

	if (finalTokens->at(0) == "move")
	{responsePtr->setCommand(2);}

	if (finalTokens->at(0) == "look" && finalTokens->at(1) == "at")
	{responsePtr->setCommand(3);}

	if (finalTokens->at(0) == "take" || finalTokens->at(0) == "drop" || finalTokens->at(0) == "cast")
	{responsePtr->setCommand(3);}


}

int Parser::evalOption(std::vector<std::string>* finalTokens, Response* responsePtr,
	std::vector<std::string>* roomItems, std::vector<std::string>* roomExits,
	std::vector<std::string>* roomInteractions)
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

		for (int i = 0; i < roomExits->size();i++)
		{
			if (finalTokens->at(index) == roomExits->at(i))
			{responsePtr->setOption(i);}
		}
	
	}

	if (responsePtr->getCommand() == 3)
	{
		for (int i = 0; i < roomItems->size();i++)
		{
			if (finalTokens->at(1) == roomItems->at(i))
			{responsePtr->setOption(i);}
		}
	}
}
