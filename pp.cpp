#include <iostream>
#include <string>
#include <algorithm>

class parsetable
{
public:
    int parsenumber;
    char NT;
    std::string NToutput;


    void set(int parsenumber, char NT, std::string NToutput)
    {
        this->parsenumber = parsenumber;
        this->NT = NT;
        this->NToutput = NToutput;
    }
};
class stack
{
    std::string stash;
public:
    stack()
    {
        stash = "$S";
    }
    char seek(); // == top
    char pop();
    void push(char);
    void push(std::string);
    std::string show();
};
char stack::seek()
{
    return stash.back();
}
char stack::pop()
{
    char temp;

    temp = stash.back();
    if (temp == '$')
    {
        std::cout << std::endl;
        std::cout << "ERROR POP END" << std::endl;

        exit(4);
    }
    stash.pop_back();

    return temp;
}
void stack::push(char input)
{
    this->stash += input;

    return;
}
void stack::push(std::string input)
{
    std::reverse(input.begin(), input.end());
    
    this->stash += input;

    return;
}
std::string stack::show()
{
    return stash;
}

const int parsetablesize = 2; // language-dependent
const int MAXNT = 2;
const int MAXT = 4;
const char NT[MAXNT] = { 'S', 'A' };
const char T[MAXT] = { 'a', 'b', 'd', 'c' };
parsetable table[parsetablesize][parsetablesize];

std::string inputstring;
std::string outstring;

char getnextsymbol(); // inputstring에서 맨 앞 문자 잘라냄
int isNT(char); // 인풋이 NT인가? 맞다면 좌표 리턴
int isT(char); // 위의것 T버전
int parsecount;

int main()
{
    stack stash;
    std::string tempstring;
    char nextsymbol;
    int i;
    int j;

    
    // language-dependent. parsetablesizexparsetablesize
    table[0][0].set(1, 'S', inputstring = "aS");
    table[0][1].set(2, 'S', inputstring = "bA");
    table[1][0].set(3, 'A', inputstring = "d");
    table[1][1].set(4, 'A', inputstring = "ccA");
    

    if (0)
    {
        std::cout << "table check : " << std::endl;
        for (j = 0; j < parsetablesize; ++j)
        {
            for (i = 0; i < parsetablesize; ++i)
            {
                std::cout << "table [" << j << "][" << i << "] / num : " << table[j][i].parsenumber << " / NT : " << table[j][i].NT << " / NToutput : " << table[j][i].NToutput << std::endl;
            }
        }
        std::cout << "table check end" << std::endl;
    }


    std::cout << "Enter a sentence : ";
    std::cin >> inputstring;

    if (inputstring.back() != '$')
    {
        std::cout << std::endl;
        std::cout << "ERROR INPUT" << std::endl;

        exit(1);
    }


    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << " Step\tStack\t\tInput\t\tParse" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    std::cout << ++parsecount << "\t" << stash.show() << "\t\t" << inputstring << "\t" << outstring << std::endl;


    while (1)
    {
        nextsymbol = getnextsymbol();

        if (nextsymbol == '$')
        {
            if (stash.seek() == '$')
            {
                // 완료
                std::cout << std::endl;
                std::cout << "ACCEPT!!" << std::endl;
                std::cout << "Left Parse : " << outstring << std::endl;

                break;
            }
            else
            {
                // 오류
                std::cout << std::endl;
                std::cout << "REJECT!!" << std::endl;
                std::cout << "ERROR MORE NT" << std::endl;

                exit(2);
            }
        }

        if (-1 < isT(nextsymbol))
        {
            if (stash.seek() == nextsymbol)
            {                
                //std::cout << ++parsecount << "\t" << stash.show() << "\t\t" << nextsymbol+inputstring << "\t" << outstring << std::endl;
                
                stash.pop();

                std::cout << ++parsecount << "\t" << stash.show() << "\t\t" << inputstring << "\t" << outstring << std::endl;

                continue;
            }
            else if(-1 < isNT(stash.seek()))
            {
                tempstring = table[isNT(stash.seek())][isT(nextsymbol)].NToutput;
                outstring += std::to_string(table[isNT(stash.seek())][isT(nextsymbol)].parsenumber);
                stash.pop();
                stash.push(tempstring);
                
                inputstring = nextsymbol + inputstring;
                std::cout << ++parsecount << "\t" << stash.show() << "\t\t" << inputstring << "\t" << outstring << std::endl;
            }
            else
            {
                std::cout << std::endl;
                std::cout << "ERROR T not match" << std::endl;
                exit(3);
            }
        }
    }


    return 0;
}
char getnextsymbol()
{
    char nextsymbol;


    nextsymbol = inputstring.front();
    inputstring = inputstring.substr(1, -1);

    return nextsymbol;
}
int isNT(char input)
{
    int i;

    for (i = 0; i < MAXNT; ++i)
    {
        if (input == NT[i])
        {
            return i;
        }
    }

    return -1;
}
int isT(char input)
{
    int i;

    for (i = 0; i < MAXT; ++i)
    {
        if (input == T[i])
        {
            return i%MAXNT;
        }
    }

    return -1;
}