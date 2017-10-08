/*
Class used inside command parser to identify and send the type of command the game engine
needs to execute as well as any other option that go with a command.

All unused variable set to -1 on initialization.
int command:
    -1 = invalid command
     1 = basic command
     2 = move command
     3 = interaction command

int option:
    Basic Command Options
        1 = look
        2 = help
        3 = inventory
        4 = save game & quit
    Move Command Options
        0 ... n-1 rooms number
    Interaction Command Options
        1 = look at <interaction or item>   >> Set Item Number or Interaction Number
        2 = take <item>                     >> Set Item Number
        3 = drop <item>                     >> Set Item Number
        4 = cast spell on <interaction>     >> Set Interaction Number

int item:
    0 ... n-1 Option Number

int interaction:
    0 ... n-1 Interaction Number

*/

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

class Response
{
private:
    int command;
    int option;
    int item;
    int interaction;

public:
    Response();
    Response(int command, int option, int item, int interaction);
    void setCommand(int command);
    void setOption(int option);
    void setItem(int item);
    void setInteraction(int interaction);
    int getCommand();
    int getOption();
    int getItem();
    int getInteraction();
};

#endif // RESPONSE_HPP

