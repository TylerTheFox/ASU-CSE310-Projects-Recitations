/*
Author:     Brandan Tyler Lasley
Class:      CSE310 Summer
Date:       6/18/2019 21:02
Compiler:   MSVC 15.7.6
Language:   C++14 Standard
*/
#if 1
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <cassert>

struct MenuOption
{
    MenuOption() noexcept : key(0) {}
    MenuOption(const char & k, const std::string & d) : key(k), description(d) {}
    char            key;
    std::string     description;
};

std::vector<struct MenuOption> _options =
{
    { '1', "Make a landing request (name, minutes)" },
    { '2', "Withdraw Request (minutes)" },
    { '3', "List all the landing requests ()" },
    { '4', "Exit ()" }
};

enum class Commands
{
    COMMAND_NONE,
    COMMAND_LAND_REQUEST,
    COMMAND_WITHDRAW,
    COMMAND_LIST_ALL_REQUESTS,
    MAX_COMMANDS
};

struct CommandParams
{
    CommandParams() noexcept : fuel(0) {}
    std::string         name;
    int                 fuel;
};

class Element
{
public:
    Element() noexcept : key(0) { }
    Element(const std::string & _name, int _key) : name(_name), key(_key) { }
    Element(const Element & e) { this->name = e.name; this->key = e.key; }

    void setKey(const int _key) { this->key = _key; }
    void setName(const std::string & _name) { this->name = _name; }
    int  getKey() const { return key; };
    const std::string & getName() { return name; };
    void decreaseKey(const int amount) { key -= amount; }
    bool operator <(const Element& d) { return key < d.key; }
    bool operator >(const Element& d) { return key > d.key; }
    bool operator <=(const Element& d) { return key <= d.key; }
    bool operator >=(const Element& d) { return key >= d.key; }
    Element& operator=(const Element & rhs) { this->name = rhs.name; this->key = rhs.key; return *this; }
private:
    int key;
    std::string name;
};


class BinarySearchTree
{
public:
    BinarySearchTree() noexcept : _tree_root(nullptr)
    {

    }

    ~BinarySearchTree()
    {
        destoryTree();
    }

    void clear()
    {
        destoryTree();
    }

    void insert(const std::string & name, int key)
    {
        node* elm = new node({ name, key });
        this->insert_impl(_tree_root, elm);
    }

    void postorder()
    {
        auto func = [this](struct node * _node)
        {
            print_node_impl(_node);
        };
        itterate_tree_post(func, _tree_root);
        std::cout << "\n";
    }

    void preorder()
    {
        auto func = [this](struct node * _node)
        {
            print_node_impl(_node);
        };
        itterate_tree_pre(func, _tree_root);
        std::cout << "\n";
    }

    void inorder()
    {
        auto func = [this](struct node * _node)
        {
            print_node_impl(_node);
        };
        itterate_tree_in(func, _tree_root);
        std::cout << "\n";
    }

    const Element& findMax()
    {
        auto ptr = this->findMax_impl(_tree_root);
        if (ptr)
            return ptr->data;
        return voidnull;
    }

    Element* findInsertNode(Element elm)
    {
        node  _node(elm);
        auto ptr = this->sim_insert_impl(_tree_root, &_node);
        if (ptr)
            return &ptr->data;
        return nullptr;
    }

    bool deleteFromTree(int key)
    {
        return deleteFromTree_impl(_tree_root, key);
    }

    void deleteMax()
    {
        deleteNode(findMax_impl(_tree_root));
    }

    Element extractMin()
    {
        auto ret = _tree_root->data;
        deleteNode(_tree_root);
        return ret;
    }

    const Element& findSuccessor()
    {
        auto ptr = findTreeSuccessor(_tree_root);
        if (ptr)
            return ptr->data;
        return voidnull;
    }

private:
    struct node
    {
        node(const Element & elm) : data(elm), left(nullptr), right(nullptr) {}
        class Element   data;
        struct node*    left;
        struct node*    right;

        bool operator<(const node& d) { return data < d.data; }
        bool operator>(const node& d) { return data > d.data; }
        bool operator<=(const node& d) { return data <= d.data; }
        bool operator>=(const node& d) { return data >= d.data; }
    }*_tree_root;
    Element voidnull;

    void print_node_impl(node * _node)
    {
        std::cout << _node->data.getName() << " (" << _node->data.getKey() << "), ";
    }

    void insert_impl(node *& _node, node * elm)
    {
        if (_node)
        {
            if (*elm < *_node)
            {
                insert_impl(_node->left, elm);
                return;
            }
            insert_impl(_node->right, elm);
            return;
        }
        _node = elm;
    }

    node* sim_insert_impl(node *& _node, node * elm)
    {
        if (_node)
        {
            if (*elm < *_node)
            {
                if (_node->left)
                    sim_insert_impl(_node->left, elm);
                else
                    return _node;
            }
            if (_node->right)
                sim_insert_impl(_node->right, elm);
            else
                return _node;
        }
        return nullptr; // idk how we got here... empty tree?
    }

    node*& findMax_impl(struct node *& _node)
    {
        if (_node)
        {
            struct node ** curr;
            for (curr = &_node; (*curr)->right; curr = &(*curr)->right);
            return *curr;
        }
        return _node;
    }

    bool deleteFromTree_impl(struct node *& _node, int key)
    {
        if (!_node)
            return false;

        if (_node->data.getKey() == key)
        {
            deleteNode(_node);
            return true;
        }
        else if (_node->data.getKey() > key)
            return deleteFromTree_impl(_node->left, key);
        else
            return deleteFromTree_impl(_node->right, key);
        return false;
    }

    const node* findTreeSuccessor(node * _node)
    {
        if (_node)
        {
            if (_node->right)
                return findMin(_node->right);

            // We don't store the parent pointer so 
            // We kind of have to make our own algro here.
            struct node* ret = nullptr;
            struct node* root = _tree_root;

            while (root)
            {
                if (*_node < *root)
                {
                    ret = root;
                    root = root->left;
                }
                else if (*_node > *root)
                    root = root->right;
                else break;
            }
            return ret;
        }
        return nullptr;
    }

    void deleteNode(struct node *& _node)
    {
        if (_node)
        {
            node* tmp;

            // Case 1 (leaf)
            if (!(_node->left || _node->right))
            {
                delete _node;
                _node = nullptr;
            }
            // Case 2 Not a leaf, but does not have a left branch.
            else if (!_node->left)
            {
                tmp = _node;
                _node = _node->right;
                delete tmp;
            }
            // Case 3 Not a leaf, but does not have a right branch.
            else if (!_node->right)
            {
                tmp = _node;
                _node = _node->left;
                delete tmp;
            }
            // Case 4 both left and right nodes exist.
            else
            {
                node * prev = nullptr;
                node * curr = _node;

                while (curr->left)
                {
                    prev = curr;
                    curr = curr->left;
                }
                _node->data = curr->data;

                if (!prev)
                    _node->right = curr->right;
                else
                    prev->left = curr->left;

                curr->right = nullptr;
                delete curr;
            }
        }
    }

    void destoryTree()
    {
        auto func = [](struct node * _node)
        {
            delete _node;
        };
        itterate_tree_post(func, _tree_root);
        _tree_root = nullptr;
    }

    node*& findMin(node *& _node)
    {
        node *& curr = _node;
        while (curr->left)
            curr = curr->left;
        return curr;
    }

    template<typename tree_func>
    void itterate_tree_post(const tree_func & _func, struct node *& _node)
    {
        if (_node)
        {
            itterate_tree_post(_func, _node->left);
            itterate_tree_post(_func, _node->right);
            _func(_node);
        }
    }

    template<typename tree_func>
    void itterate_tree_pre(const tree_func & _func, struct node *& _node)
    {
        if (_node)
        {
            _func(_node);
            itterate_tree_pre(_func, _node->left);
            itterate_tree_pre(_func, _node->right);
        }
    }

    template<typename tree_func>
    void itterate_tree_in(const tree_func & _func, struct node *& _node)
    {
        if (_node)
        {
            itterate_tree_in(_func, _node->left);
            _func(_node);
            itterate_tree_in(_func, _node->right);
        }
    }
};

class Menu
{
public:
    Menu() noexcept : _exit(false), _k_val(0)
    {
        std::cout << "Author:\tBrandan Lasley\nID:\t1214587374\nDate:\t6/18/2019 21:02\nClass:\tCSE310 Summer\n\n";

        std::cout << "Please input k value: ";
        std::cin >> _k_val;

        std::cout << "\nMain Menu:\n";
        for (const auto & m : _options)
            std::cout << m.key << " - " << m.description << '\n';
        std::cout << '\n';

        std::cout << "Example Add Command: \"1 AA1107 30\"\n\n";
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
                Make a landing request
                */
                std::cin >> Args.name;
                std::cin >> Args.fuel;
                process_command(Commands::COMMAND_LAND_REQUEST, Args);
                break;

            case '2':
                /*
                Land a Plane
                */
                std::cin >> Args.fuel;
                process_command(Commands::COMMAND_WITHDRAW, Args);
                break;

            case '3':
                /*
                List all the landing requests
                */
                process_command(Commands::COMMAND_LIST_ALL_REQUESTS, Args);
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
        case Commands::COMMAND_LAND_REQUEST:
        {
            std::cout << "COMMAND_LAND_REQUEST name = " << args.name << " fuel (in minutes) = " << args.fuel << '\n';
            auto test_insert = _data.findInsertNode({ args.name, args.fuel });

            if (test_insert)
            {
                // Test for K
                auto diff = test_insert->getKey() - args.fuel;
                if (_k_val > diff)
                {
                    std::cout << "Landing request denied!\n";
                    return;
                }
            }
            _data.insert(args.name, args.fuel);
            std::cout << "Successfully added aircraft!\n";
            break;
        }
        case Commands::COMMAND_WITHDRAW:
        {
            std::cout << "COMMAND_WITHDRAW" << '\n';
            if (_data.deleteFromTree(args.fuel))
                std::cout << "Successfully withdrawn flight!\n";
            else
                std::cout << "Error withdrawling flight from tracker\n";
            break;
        }
        case Commands::COMMAND_LIST_ALL_REQUESTS:
            std::cout << "COMMAND_LIST_ALL_REQUESTS" << '\n';
            _data.inorder();
            break;
        case Commands::MAX_COMMANDS:
        case Commands::COMMAND_NONE:
            assert(false); // How did we get here?
        default:
            assert(false); // How did we get here?
        }
    }
private:
    BinarySearchTree    _data;
    bool                _exit;
    int                 _k_val;
};

int main()
{
    Menu m;
    m.main_menu();
    return 0;
}
#endif