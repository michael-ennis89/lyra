/*
Class used inside command parser to identify and send the type of command the game engine
needs to execute as well as any other option that go with a command.

All unused variable set to -1 on initialization.
int command:
    -1 = invalid command
     1 = basic command
     2 = move command
     3 = interaction command
     4 = item command
     5 = spell command

    Basic Command Options
        1 = look                            >> Set option number
        2 = help                            >> Set option number
        3 = inventory                       >> Set option number
        4 = save game & quit                >> Set option number
    Move Command Options
        N/A, Set room Number
    Interaction Command Options
        Look at <interaction>               >> Set Interaction Number
    Item Command Options
        Take <item>                         >> Set Item Number && Set Option to 1
        Drop <item>                         >> Set Item Number && Set Option to 2
    Spell Command Options
        Cast spell on <interaction>         >> Set Interaction Number

int option:
    1 ... 4   Option Number
int item:
    0 ... n-1 Item Number

int interaction:
    0 ... n-1 Interaction Number

int room:
    0 ... n-1 Room Number
    -2        Previous Room

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
    int room;

public:
    Response();
    Response(int command, int option, int item, int room, int interaction);
    void setCommand(int command);
    void setOption(int option);
    void setItem(int item);
    void setRoom(int room);
    void setInteraction(int interaction);
    int getCommand();
    int getOption();
    int getItem();
    int getRoom();
    int getInteraction();
};

#endif // RESPONSE_HPP

