#include <iostream>
#include <string>


std::string inputstring; // 입력될 문장
std::string outstring; // 출력될 문장
int parsecount;

char getnextsymbol();
void NT_S(); // 논터미널  S
void NT_A(); // 논터미널 A


int main()
{

	std::cout << "Enter a Sentence : ";
	std::cin >> inputstring;

	if (inputstring.back() != '$')
	{
		std::cout << std::endl;
		std::cout << "ERROR INPUT" << std::endl;
		
		exit(4);
	}

	NT_S(); // Start Symbol

	if (getnextsymbol() != '$')
	{
		std::cout << std::endl;
		std::cout << "ERROR PARSE END" << std::endl;

		exit(5);
	}
	else
	{
		std::cout << "ACCEPT!!" << std::endl;

		std::cout << "Left Parse : " << outstring << std::endl;
	}


	return 0;
}
char getnextsymbol() // inputstring에서 맨 앞 문자 잘라냄
{
	char nextsymbol;


	nextsymbol = inputstring.front();
	inputstring = inputstring.substr(1, -1);

	return nextsymbol;
}
void NT_S()
{
	char nextsymbol;

	nextsymbol = getnextsymbol();
	std::cout << ++parsecount << "\t\t" << inputstring << "\t\t";

	switch (nextsymbol)
	{
	case 'a': // S -> aS
		std::cout << "a" << std::endl;
		outstring += "1";

		NT_S();

		break;
	case 'b': // S -> bA
		std::cout << "b" << std::endl;
		outstring += "2";

		NT_A();

		break;
	default:
		std::cout << std::endl;
		std::cout << "ERROR NT_S" << std::endl;
		exit(1);
	}


	return;
}
void NT_A()
{
	char nextsymbol;

	nextsymbol = getnextsymbol();
	std::cout << ++parsecount << "\t\t";

	switch (nextsymbol)
	{
	case 'c': // A -> ccA

		if (getnextsymbol() == 'c')
		{
			std::cout << inputstring << "\t\t" << "cc" << std::endl;
			outstring += "4";

			NT_A();
		}
		else
		{
			std::cout << std::endl;
			std::cout << "ERROR c" << std::endl;
			exit(3);
		}

		break;
	case 'd':
		std::cout << inputstring << "\t\t" << "d" << std::endl;
		outstring += "3";

		break;
	default:
		std::cout << std::endl;
		std::cout << "ERROR NT_A" << std::endl;
		exit(2);
	}


	return;
}