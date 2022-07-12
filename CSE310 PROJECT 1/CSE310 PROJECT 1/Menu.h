/*
    Author: Brandan Tyler Lasley
    Date: 2/19/2019
    Purpose: A menu to control the heap class.
*/
#pragma once
#include "Heap.h"

enum class Commands
{
    COMMAND_NONE,
    COMMAND_NEW_HEAP,
    COMMAND_READ_ARRAY,
    COMMAND_DISPLAY_HEAP,
    COMMAND_INSERT_ELEMENT,
    COMMAND_DELETE_ELEMENT,
    COMMNAD_DECREASE_KEY,

    MAX_COMMANDS
};

struct CommandParams
{
    CommandParams() : i(0), v(0), f(0), k(0), n(0) {}
    int         i;
    int         v;
    int         f;
    int         k;
    size_t      n;
};

class Menu
{
public:
    Menu();
    void    main_menu();
    void    process_command(const enum class Commands command, const struct CommandParams & args);
private:
    Heap _h;
    bool _exit;
};