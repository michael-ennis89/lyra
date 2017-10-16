
#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "Response.hpp"

class Parser
{
	private:
		std::string commandString;
		std::string* strptr;
		std::vector<std::string> tokens;
		std::vector<std::string>* tokensptr;
		std::vector<std::string> finalTokens;
		std::vector<std::string>* finalptr;
		
		

	public:
		//Response Parse(std::string command, std::vector<std::string> inventory, std::vector<std::string> roomItems, std::vector<std::string> roomExits);
		int tokenizer(std::string*,	std::vector<std::string>* tokens);
		int stripPunc(std::string*);
		int stripArticles(std::vector<std::string>*, std::vector<std::string>*);
		//int evalTokens(std::vector<std::string>* finalTokens);
		void evalCommand(std::vector<std::string>* finalTokens, Response* responsePtr);
		int evalOption(std::vector<std::string>* finalTokens, Response* responsePtr,
			std::vector<std::string>* roomItems, std::vector<std::string>* roomExits,
			std::vector<std::string>* roomInteractions);

};

#endif
