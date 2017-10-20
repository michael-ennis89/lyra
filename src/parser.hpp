
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

	public:
		static Response parse(std::string command, std::vector<std::string> inventory, std::vector<std::string> roomItems, std::vector<std::string> roomExits, std::vector<std::string> roomInteractions);
		static void tokenizer(std::string*,	std::vector<std::string>* tokens);
		static void stripPunc(std::string*);
		static void stripArticles(std::vector<std::string>*, std::vector<std::string>*);
		static void evalCommand(std::vector<std::string>* finalTokens, Response* responsePtr);
		static void evalOption(std::vector<std::string>* finalTokens, Response* responsePtr,
			std::vector<std::string>* roomItems, std::vector<std::string>* roomExits,
			std::vector<std::string>* roomInteractions);

};

#endif
