#include <string>
#include <iostream>
#include <vector>
#include <sstream>

//temporary usage
//runs on the command line and accepts strings in quotes
//ex. g++ parser.cpp -o parser
//parser "This string! has ?punctuation."


int tokenizer(std::string*);
int stripPunc(std::string*);

int main (int argc, char* argv[])
{
	std::string commandString = argv[1];
	std::string* strptr = &commandString;
	std::cout << *strptr << std::endl;
	stripPunc(strptr);
	tokenizer(strptr);
}

//need to modify this only removes one instance of the punctuation

int stripPunc(std::string* inputString)
{
		std::size_t position; //position within string while using find()
		std::size_t strSize = inputString->size(); 
		std::string punctuation[3] = {"?",".","!"}; //punctuation to remove
		for(int i = 0; i < 3 ; i++)
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
		
		std::cout << *inputString << std::endl; //for command line testing. remove
}

int tokenizer(std::string* inputString)
{
    //http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
	std::string buffer;
	std::stringstream stream(*inputString);
	std::vector<std::string> tokens;

	while (stream >> buffer)
	{
		tokens.push_back(buffer);
	}

	for (int i = 0; i < tokens.size(); i++)
	{
		if(tokens[i] == "yeah")
		{
			std::cout << "Found it" <<std::endl;
		}
		std::cout << tokens[i] << std::endl;
	}
}

