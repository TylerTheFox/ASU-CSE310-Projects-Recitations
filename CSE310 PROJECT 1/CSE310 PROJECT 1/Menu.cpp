/*
    Author: Brandan Tyler Lasley
    Date: 2/19/2019
*/
#include "Menu.h"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

struct MenuOption
{
    MenuOption() : key(0) {}
    MenuOption(const char & k, const std::string & d) : key(k), description(d) {}
    char            key;
    std::string     description;
};

std::vector<struct MenuOption> _options =
{ 
    { 'C', "Create new heap (n)"        },
    { 'R', "Read minheap from disk ()"  },
    { 'W', "Display Heap (f)"           },
    { 'I', "Insert Element (f, k)"      },
    { 'D', "Delete Element (f)"         },
    { 'K', "Decrease key (i, v, f)"     },
    { 'S', "Quit/Stop ()"               },
};

Menu::Menu() : _exit(false)
{
    std::cout << "Author: Brandan Lasley\nID: 1214587374\nDate: 2/19/2019\nClass: CSE310\n\n";

    std::cout << "Main Menu:\n";
    for (const auto & m : _options)
        std::cout << m.key << " - " << m.description << '\n';
    std::cout << '\n';
}

void Menu::main_menu()
{
    /*
        Input validation & menu selection.
    */
    struct CommandParams    Args;
    char                    key = 0;

    std::cout << "Please Enter Key: ";

    while (!_exit)
    {
        scanf("%c", &key);
        switch (key)
        {
        case '\r': // Win32
        case '\n':
        case '\t':
        case ' ':
            continue; // Skip blank space.
            break;

        case 'C':
        case 'c':
            /*
                On reading C n, the program creates an empty heap with capacity equal ton, and waits for the next command.
            */
            scanf("%d", &Args.n);
            process_command(Commands::COMMAND_NEW_HEAP, Args);
            break;

        case 'R':
        case 'r':
            /*
                On reading R, the program reads in the array A from fileHEAPinput.txt,
                calls the linear time buildheap algorithm to build the min-heap based on A,
                and waits for the next command.
            */
            process_command(Commands::COMMAND_READ_ARRAY, Args);
            break;

        case 'W':
        case 'w':
            /*
                On reading W, the program writes the current heap information to the screen,
                and waits for the next command.  The output should be in the same format as in the
                fileHEAPinput.txt, proceededby the heap capacity.
            */
            process_command(Commands::COMMAND_DISPLAY_HEAP, Args);
            break;

        case 'I':
        case 'i':
            /*
                On reading I f k, the program inserts an element withkeyequal to k
                into the current heap with the corresponding flag set to f,
                and waits for the next command
            */
            scanf("%d", &Args.f); scanf("%d", &Args.k);
            process_command(Commands::COMMAND_INSERT_ELEMENT, Args);
            break;

        case 'D':
        case 'd':
            /*
                On reading D f, the program deletes the minimum element from the heap with the corresponding
                flag  set  to f,  and  prints  the key field  of  the  deleted  element  on  the  screen,  it
                waits  for  the  next command.
            */
            scanf("%d", &Args.f);
            process_command(Commands::COMMAND_DELETE_ELEMENT, Args);
            break;

        case 'K':
        case 'k':
            /*
                On reading K f i v,  the program decreases the key of
                element with index i to v with the corresponding
                flag set to f.
            */
            scanf("%d", &Args.i); scanf("%d", &Args.v); scanf("%d", &Args.f);
            process_command(Commands::COMMNAD_DECREASE_KEY, Args);
            break;

        case 'S':
        case 's':
            /*
                Stop Program
            */
            _exit = true;
            break;

        default:
            // Unknown key.
            std::cout << "Invalid Command\n";
        }

        // This is placed at the end so we can skip all the blank space.
        std::cout << "Please Enter Key: ";
    }
}

void Menu::process_command(const Commands command, const CommandParams & args)
{
    assert(command > Commands::COMMAND_NONE && command < Commands::MAX_COMMANDS);

    std::cout << "Executing command: ";
    switch (command)
    {
    case Commands::COMMAND_NEW_HEAP:
        std::cout << "COMMAND_NEW_HEAP n = " << args.n << '\n';
        _h.initialize(args.n);
        break;
    case Commands::COMMAND_READ_ARRAY:
        std::cout << "COMMAND_READ_ARRAY" << '\n';
        _h.buildHeap({}); // Todo read from file
        break;
    case Commands::COMMAND_DISPLAY_HEAP:
        std::cout << "COMMAND_DISPLAY_HEAP f= " << args.f << '\n';
        _h.printHeap();
        break;
    case Commands::COMMAND_INSERT_ELEMENT:
        std::cout << "COMMAND_INSERT_ELEMENT f = " << args.f << " k = " << args.k << '\n';
        _h.insert(args.f, args.k);
        break;
    case Commands::COMMAND_DELETE_ELEMENT:
        std::cout << "COMMAND_DELETE_ELEMENT f = " << args.f << '\n';
        _h.deleteMin(args.f);
        break;
    case Commands::COMMNAD_DECREASE_KEY:
        std::cout << "COMMAND_DELETE_ELEMENT i = " << args.n << " v = " << args.v << " f = " << args.f << '\n';
        _h.decreaseKey(args.n, args.v, args.f);
        break;
    default:
        assert(false); // How did we get here?
    }
}
