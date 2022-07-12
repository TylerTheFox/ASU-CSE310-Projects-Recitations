/*
    Author:     Brandan Tyler Lasley
    Class:      CSE310 Summer
    Date:       5/26/2019 14:29
    Compiler:   MSVC 15.7.6
    Language:   C++14 Standard
*/
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <cassert>

struct MenuOption
{
    MenuOption() noexcept : key(0)  {}
    MenuOption(const char & k, const std::string & d) : key(k), description(d) {}
    char            key;
    std::string     description;
};

std::vector<struct MenuOption> _options =
{
    { '1', "Add student record (name, average) *** No spaces ***"   },
    { '2', "Display student records ()"                             },
    { '3', "Count number of records ()"                             },
    { '4', "Exit ()"                                                }
};

enum class Commands
{
    COMMAND_NONE,
    COMMAND_ADD_STUDENT,
    COMMAND_DISPLAY_STUDENT,
    COMMAND_COUNT_RECORDS,
    MAX_COMMANDS
};

struct CommandParams
{
    CommandParams() noexcept : average(0) {}
    std::string         name;
    double              average;
};

class DoubleLinkList
{
public:
    DoubleLinkList() noexcept : _head(nullptr), _tail(nullptr), _size(0) {}

    void addItem(const std::string & name, const double average)
    {
        if (!_head)
        {
            _head = new _Data(name, average);
            _tail = _head;
        }
        else
        {
            _tail->next = new _Data(name, average);
            _tail = _tail->next;
        }
        _size++;
    }

    void display()
    {
        std::cout << "Displaying Students: \n";
        for (_Data * curr = _head; curr; curr = curr->next)
        {
            std::cout << "Name: " << curr->name << "\t\tAverage: " << curr->average << '\n';
        }
        std::cout << '\n';
    }

    size_t size()
    {
        return _size;
    }
private:
    struct _Data
    {
        _Data(const std::string & _name, const double _average) : name(_name), average(_average), next(nullptr) {}
        std::string name;
        double average;
        _Data* next;
    };

    _Data*  _head;
    _Data*  _tail;
    size_t  _size;
};

class Menu
{
public:
    Menu() noexcept : _exit(false)
    {
        std::cout << "Author:\tBrandan Lasley\nID:\t1214587374\nDate:\t5/26/2019 14:29\nClass:\tCSE310 Summer\n\n";

        std::cout << "Main Menu:\n";
        for (const auto & m : _options)
            std::cout << m.key << " - " << m.description << '\n';
        std::cout << '\n';

        std::cout << "Example Add Command: \"1 Brandan 2.50\"\n\n";
    }

    void    main_menu()
    {
        /*
        Input validation & menu selection.
        */
        struct CommandParams    Args;
        char                    key = 0;

        std::cout << "Enter Command: ";

        while (!_exit)
        {
            std::cin >> key;
            switch (key)
            {
            case '\r': // Win32
            case '\n':
            case '\t':
            case ' ':
                continue; // Skip blank space.
                break;

            case '1':
                /*
                    Add student
                */
                std::cin >> Args.name;
                std::cin >> Args.average;
                process_command(Commands::COMMAND_ADD_STUDENT, Args);
                break;

            case '2':
                /*
                    Display Students
                */
                process_command(Commands::COMMAND_DISPLAY_STUDENT, Args);
                break;

            case '3':
                /*
                    Count the number of records
                */
                process_command(Commands::COMMAND_COUNT_RECORDS, Args);
                break;

            case '4':
                /*
                Stop Program
                */
                _exit = true;
                break;

            default:
                // Unknown key.
                std::cout << "\nInvalid Command\n";
            }

            // This is placed at the end so we can skip all the blank space.
            if (!_exit)
                std::cout << "Enter Command: ";
        }
    }

    void    process_command(const Commands command, struct CommandParams & args)
    {
        std::cout << "Executing command: ";
        switch (command)
        {
        case Commands::COMMAND_ADD_STUDENT:
            std::cout << "COMMAND_ADD_STUDENT name = " << args.name << " average = " << args.average << '\n';
            _list.addItem(args.name, args.average);
            std::cout << "Successfully added student!\n";
            break;
        case Commands::COMMAND_COUNT_RECORDS:
            std::cout << "COMMAND_COUNT_RECORDS" << '\n';
            std::cout << "LinkList size = " << _list.size() << '\n';
            break;
        case Commands::COMMAND_DISPLAY_STUDENT:
            std::cout << "COMMAND_DISPLAY_STUDENT" << '\n';
            _list.display();
            break;
        case Commands::MAX_COMMANDS:
        case Commands::COMMAND_NONE:
            assert(false); // How did we get here?
        default:
            assert(false); // How did we get here?
        }
    }
private:
    DoubleLinkList  _list;
    bool            _exit;
};

int main()
{
    Menu m;
    m.main_menu();
    return 0;
}
