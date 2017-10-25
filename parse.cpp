#include <iostream>
#include <string>
#include <sstream>

int main(){

    std::string *brokenUp;
    std::string contents;
    std::string command;
    int i = 0;
    int j = 0;
    int k = 0;

    // we will pass this in but would recommend making it all upper or all lower case..
    std::cout << "Enter a command:" << std::endl;
    getline( std::cin, command);

    // Cut the string up and put it into and array
    std::stringstream ss(command);
    brokenUp = new std::string[20];

    while(ss >> contents)
    {
        brokenUp[i] = contents;
        i++;
    }

    // Parse it for verbs first then nested loops inside to look for nouns.. Ignores any garbage pronouns, spaces, etc..
    for(j = 0; j < i; j++)
    {
        if((brokenUp[j] == "look") || (brokenUp[j] == "help") || (brokenUp[j] == "inventory") || (brokenUp[j] == "save"))
        {
            std::cout << "basic command, set command to 1" << std::endl;
            if(brokenUp[j] == "look")
            {
                std::cout << "set option number to 1" << std::endl;
                // delete dynamics
                // return parsed command.
                return 0;
            }
            else if(brokenUp[j] == "help")
            {
                std::cout << "set option number to 2" << std::endl;
                // delete dynamics
                // return parsed command.
                return 0;
            }
            else if(brokenUp[j] == "inventory")
            {
                std::cout << "set option number to 3" << std::endl;
                // delete dynamics
                // return parsed command.
                return 0;
            }
            else if(brokenUp[j] == "save")
            {
                std::cout << "set option to number 4" << std::endl;
                //delete dynamics
                //return parsed command.
                return 0;
            }

        }
        else if((brokenUp[j] == "move") || (brokenUp[j] == "go"))
        {
            std::cout << "move command, set command to 2" << std::endl;
            // parse rest of string..
            for(k = j + 1; k < i; k++)
            {
                if(brokenUp[k] == "back")
                {
                    std::cout << "move back, set command to -2" << std::endl;
                    // delete dynamics..
                    // return parsed response.
                    return 0;
                }
                else if(brokenUp[k] == "motorcycle")
                {
                    std::cout << "move weasely's house, set room to 1" << std::endl;
                    // delete dynamics..
                    // return parsed command.
                    return 0;
                }
                else if(brokenUp[k] == "away")
                {
                    std::cout << "move london diner, set room to 2" << std::endl;
                    // delete dynamics..
                    // return parsed command.
                    return 0;
                }
                else if(brokenUp[k] == "safe")
                {
                    std::cout << "move safe house, set room to 3" << std::endl;
                    // delete dynamics..
                    // return parsed command.
                    return 0;
                }
                else if(brokenUp[k] == "headquarters")
                {
                    std::cout << "move headquarters, set room to 4" << std::endl;
                    // delete dynamics..
                    // return parsed command.
                    return 0;
                }
                else if(brokenUp[k] == "fireplace")
                {
                    std::cout << "move forest, set room to 5" << std::endl;
                    // delete dynamics..
                    // return parsed command.
                    return 0;
                }
                else if(brokenUp[k] == "hallow")
                {
                    std::cout << "move godrics hallow, set room to 6" << std::endl;
                    // delete dynamics..
                    // return parsed command.
                    return 0;
                }
                else if(brokenUp[k] == "manor")
                {
                    std::cout << "move malfloy manor, set room to 7" << std::endl;
                    // delete dynamics..
                    // return parsed command.
                    return 0;
                }
            }
        }
        else if(brokenUp[j] == "inspect")
        {
            std::cout << "interaction command, set command to 3" << std::endl;
            for(k = j + 1; k < i; k++)
            {
                if(brokenUp[k] == "potion")
                {
                    std::cout << "potion interaction, set interaction to 0" << std::endl;
                    // delete dynamics..
                    // return parsed response.
                    return 0;
                }
                else if(brokenUp[k] == "clothes")
                {
                    std::cout << "clothes interaction, set interaction to 1" << std::endl;
                    // delete dynamics..
                    // return parsed response.
                    return 0;
                }
            }
        }
        else if((brokenUp[j] == "get") || (brokenUp[j] == "drop"))
        {
            std::cout << "item command, set command to 4." << std::endl;
            if((brokenUp[j] == "get") || (brokenUp[j] == "take"))
            {
                std::cout << "get item command, set option to 1" << std::endl;
                for(k = j+1; k < i; k++)
                {
                    if(brokenUp[k] == "snitch")
                    {
                        std::cout << "snitch item, set item number to 0" << std::endl;
                        // delete dynamics
                        // return parsed command.
                        return 0;
                    }
                    else if(brokenUp[k] == "necklace")
                    {
                        std::cout << "necklace item, set item to 1?" << std::endl;
                        // delete dynamic
                        // return parsed command.
                        return 0;
                    }
                }
            }
            else if(brokenUp[j] == "drop")
            {
                std::cout << "drop item command, set option to 2" << std::endl;
                for(k = j+1; k < i; k++)
                {
                    if(brokenUp[k] == "snitch")
                    {
                        std::cout << "snitch item, set item number to 0" << std::endl;
                        // delete dynamics
                        // return parsed command.
                        return 0;
                    }
                    else if(brokenUp[k] == "necklace")
                    {
                        std::cout << "necklace item, set item 1" << std::endl;
                        // delete dynamic
                        // return parsed command.
                        return 0;
                    }
                }
            }
        }
        else if((brokenUp[j] == "cast") || (brokenUp[j] == "spell"))
        {
            // cant remember what ones you can cast at yet..
            // loop delete return
            return 0;
        }
    }

    //Obviously bad command. or verb is good and noun isn't for example get necklaace "Mispelled necklace"
    // do a set of logic checks.
    /*
    if((myResponse->getCommand() == 4) && (myResponse->getItem() == -1))
    {
        myResponse->setCommand(-1);
        myResponse->setOption(-1);
        myResponse->setItem(-1);
        //delete dynamics
        //return response object.
        return 0;
    }
    */
    //else
    //{
        std::cout << "Spell check before you get someone killed." << std::endl;
    //}
    // Set all response variables to -1
    // delete dynamics..
    // Return Response Object
    return 0;
}
