
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
		static void tokenizer(std::string*,	std::vector<std::string>* tokens);
		static void stripPunc(std::string*);
		static void stripArticles(std::vector<std::string>*, std::vector<std::string>*);
		static void evalCommand(std::vector<std::string>* finalTokens, Response* responsePtr);
		static void evalOption(std::vector<std::string>* finalTokens, Response* responsePtr);

	public:
		Response parse(std::string command);
};

#endif
