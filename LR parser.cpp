#include <iostream>
#include <string>
#include <iomanip>

/*
E -> E + T | T
T -> T * F | F
F -> (E) | a

0. E' -> E
1. E -> E + T
2. E -> T
3. T -> T * F
4. T -> F
F -> (E)
6. F -> a

*/
const int STACK_SIZE = 100;
int NOW_SIZE; // of stack
class stack
{
public:
    std::string cstack;
    int istack[STACK_SIZE];
    stack()
    {
        int i;

        cstack.reserve(STACK_SIZE);
        cstack = "$";
        istack[0] = 0;

        for (i = 1; i < STACK_SIZE; ++i)
        {
            istack[i] = -1;
        }
    }
    void push(char, int);
    char pop();
    void show();
};
void stack::push(char ic, int ii)
{
    ++NOW_SIZE;

    this->cstack += ic;
    this->istack[NOW_SIZE] = ii;
}
void stack::show()
{
    std::string tempout;
    int i;

    for (i = 0; i <= NOW_SIZE; ++i)
    {
        if (i)
        {
            tempout += cstack[i];
        }
        tempout += std::to_string(istack[i]);
    }
    
    std::cout << std::left << std::setw(35) << tempout;

    return;
}
char stack::pop()
{
    char temp;

    temp = cstack.back();
    cstack = cstack.substr(0, cstack.size()-1);

    istack[NOW_SIZE] = -1;
    --NOW_SIZE;

    return temp;
}
stack stash;
std::string inputstring;
std::string outstring;
std::string actionstring;

void shift(int state);
void print_reject();
void print_stacksizereject(int);
void reduce(int order); // language-dependent
int GOTO(char);// language-dependent

int main()
{
    std::cout << "input string : ";
    std::cin >> inputstring;

    if (inputstring.back() != '$')
    {
        std::cout << std::endl;
        std::cout << "ERROR : last character of input string must be string dollar($)" << std::endl;
        return 1;
    }

    std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "\t\t" << "Stack" << "\t\t\t" << "Input" << "\t\t" << "Action" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
    actionstring = "START";
    stash.show();
    std::cout << std::right << std::setw(10) << inputstring << "           " << actionstring << std::endl;
    
    while (1)
    {
        // equal to parse table : language-dependent
        switch (stash.istack[NOW_SIZE])
        {
        case 0:
            switch (inputstring.front())
            {
            case 'a':
                shift(5);
                break;
            case '(':
                shift(4);
                break;
            default:
                print_reject();
            }
            break;
        case 1:
            switch (inputstring.front())
            {
            case '+':
                shift(6);
                break;
            case '$':
                actionstring = "Accept";
                break;
            default:
                print_reject();
            }
            break;
        case 2:
            switch (inputstring.front())
            {
                break;
            case '*':
                shift(7);
                break;
            case '+':
            case ')':
            case '$':
                reduce(2);
                break;
            default:
                print_reject();
            }
            break;
        case 3:
            switch (inputstring.front())
            {
            case '+':
            case '*':
            case ')':
            case '$':
                reduce(4);
                break;
            default:
                print_reject();
            }
            break;
        case 4:
            switch (inputstring.front())
            {
            case 'a':
                shift(5);
                break;
            case '(':
                shift(4);
                break;
            default:
                print_reject();
            }
            break;
        case 5:
            switch (inputstring.front())
            {
            case '+':
            case '*':
            case ')':
            case '$':
                reduce(6);
                break;
            default:
                print_reject();
            }
            break;
        case 6:
            switch (inputstring.front())
            {
            case 'a':
                shift(5);
                break;
            case '(':
                shift(4);
                break;
            default:
                print_reject();
            }
            break;
        case 7:
            switch (inputstring.front())
            {
            case 'a':
                shift(5);
                break;
            case '(':
                shift(4);
                break;
            default:
                print_reject();
            }
            break;
        case 8:
            switch (inputstring.front())
            {
            case '+':
                shift(6);
                break;
            case ')':
                shift(11);
                break;
            default:
                print_reject();
            }
            break;
        case 9:
            switch (inputstring.front())
            {
            case '*':
                shift(7);
                break;
            case '+':
            case ')':
            case '$':
                reduce(1);
                break;
            default:
                print_reject();
            }
            break;
        case 10:
            switch (inputstring.front())
            {
            case '+':
            case '*':
            case ')':
            case '$':
                reduce(3);
                break;
            default:
                print_reject();
            }
            break;
        case 11:
            switch (inputstring.front())
            {
            case '+':
            case '*':
            case ')':
            case '$':
                reduce(5);
                break;
            default:
                print_reject();
            }
            break;
        default:
            std::cout << std::endl;
            std::cout << "ERROR : istack Out Of Range or NOW_SIZE " << std::endl;
            return 1;
        }
        
        stash.show();
        std::cout << std::right << std::setw(10) << inputstring << "           " << actionstring << std::endl;

        if (actionstring == "Accept")
        {
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "Accept!!" << std::endl;
            std::cout << "Right Parse : " << outstring << std::endl;
            break;
        }
    }



    return 0;
}
void shift(int state)
{
    stash.push(inputstring.front(), state);
    inputstring = inputstring.substr(1, inputstring.size());
    actionstring = "shift ";
    actionstring += std::to_string(state);

    return;
}
void print_reject()
{
    std::cout << std::endl;
    std::cout << "REJECT : Wrong Sentence" << std::endl;

    exit(1);
    return;
}
void print_stacksizereject(int size)
{
    std::cout << std::endl;
    std::cout << "REJECT : stack size must be over " << size << std::endl;
}
int GOTO(char input)
{
    switch (stash.istack[NOW_SIZE])
    {
    case 0:
        switch (input)
        {
        case 'E':
            return 1;
        case 'T':
            return 2;
        case 'F':
            return 3;
        default:
            std::cout << std::endl;
            std::cout << "REJECT : input not good" << std::endl;
            exit(1);
        }
    case 4:
        switch (input)
        {
        case 'E':
            return 8;
        case 'T':
            return 2;
        case 'F':
            return 3;
        default:
            std::cout << std::endl;
            std::cout << "REJECT : input not good" << std::endl;
            exit(1);
        }
    case 6:
        switch (input)
        {
        case 'T':
            return 9;
        case 'F':
            return 3;
        default:
            std::cout << std::endl;
            std::cout << "REJECT : input not good" << std::endl;
            exit(1);
        }
    case 7:
        switch (input)
        {
        case 'F':
            return 10;
        default:
            std::cout << std::endl;
            std::cout << "REJECT : input not good" << std::endl;
            exit(1);
        }
    default:
        std::cout << std::endl;
        std::cout << "REJECT : GOTO destination missing" << std::endl;
        exit(1);
    }
}
void reduce(int order)
{
    switch (order)
    {
    case 1:
        if (NOW_SIZE < 3)
        {
            print_stacksizereject(3);
        }
        else if(stash.cstack.substr(stash.cstack.size()-3,stash.cstack.size()) == "E+T")
        {
            stash.pop();
            stash.pop();
            stash.pop();
            stash.push('E', GOTO('E'));
            
        }
        else
        {
            print_reject();
        }
        break;
    case 2:
        if (NOW_SIZE < 1)
        {
            print_stacksizereject(1);
        }
        else if (stash.cstack.substr(stash.cstack.size() - 1, stash.cstack.size()) == "T")
        {
            stash.pop();
            stash.push('E', GOTO('E'));

        }
        else
        {
            print_reject();
        }
        break;
    case 3:
        if (NOW_SIZE < 3)
        {
            print_stacksizereject(3);
        }
        else if (stash.cstack.substr(stash.cstack.size() - 3, stash.cstack.size()) == "T*F")
        {
            stash.pop();
            stash.pop();
            stash.pop();
            stash.push('T', GOTO('T'));

        }
        else
        {
            print_reject();
        }
        break;
    case 4:
        if (NOW_SIZE < 1)
        {
            print_stacksizereject(1);
        }
        else if (stash.cstack.substr(stash.cstack.size() - 1, stash.cstack.size()) == "F")
        {
            stash.pop();
            stash.push('T', GOTO('T'));

        }
        else
        {
            print_reject();
        }
        break;
    case 5:
        if (NOW_SIZE < 3)
        {
            print_stacksizereject(3);
        }
        else if (stash.cstack.substr(stash.cstack.size() - 3, stash.cstack.size()) == "(E)")
        {
            stash.pop();
            stash.pop();
            stash.pop();
            stash.push('F', GOTO('F'));

        }
        else
        {
            print_reject();
        }
        break;
    case 6:
        if (NOW_SIZE < 1)
        {
            print_stacksizereject(1);
        }
        else if (stash.cstack.substr(stash.cstack.size() - 1, stash.cstack.size()) == "a")
        {
            stash.pop();
            stash.push('F', GOTO('F'));

        }
        else
        {
            print_reject();
        }
        break;
    default:
        std::cout << std::endl;
        std::cout << "ERROR : order out of range" << std::endl;
        exit(1);
    }
    outstring += std::to_string(order);
    actionstring = "reduce ";
    actionstring += std::to_string(order);

    return;
}



/*

a+a*a
F+a*a       6
T+a*a       4
E+a*a       2
E+F*a       6
E+T*a       4
E+T*F       6
E+T           3
E               1

6 4 2 6 4 6 3 1

a*a+a
F*a+a     6
T*a+a     4
T*F+a     6
T+a         3
E+a         2
E+F         6
E+T         4
E             1

6 4 6 3 2 6 4 1

*/