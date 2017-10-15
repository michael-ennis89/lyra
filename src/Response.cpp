#include "Response.hpp"

Response::Response()
{
    setCommand(-1);
    setOption(-1);
    setItem(-1);
    setInteraction(-1);
}

Response::Response(int command, int option, int item, int interaction)
{
    this -> command = command;
    this -> option = option;
    this -> item = item;
    this -> interaction = interaction;
}

void Response::setCommand(int command)
{
    this -> command = command;
}

void Response::setOption(int option)
{
    this -> option = option;
}

void Response::setItem(int item)
{
    this -> item = item;
}

void Response::setInteraction(int interaction)
{
    this ->interaction = interaction;
}

int Response::getCommand()
{
    return command;
}

int Response::getOption()
{
    return option;
}

int Response::getItem()
{
    return item;
}

int Response::getInteraction()
{
    return interaction;
}
