//Brennen Boese
//CST229 
//Assignment 3

#include <iostream>
#include "PDA.h"

int main()
{
	// define a class to represent a PDA
	 // include a stack and an input tape (kinda like a queue)

	 //
	 // read definition of the PDA from stdin
	 //

	 // instatiate an empty PDA
	 // with an accepting state called F 
	PDA pda;
	pda.AddState('F', PDA::Action::ACCEPT, 'z');

	// throw away the first line, which is just a comment
	std::string line;
	std::getline(std::cin, line);
	std::cout << "Comment: " << line << std::endl;

	// read # of states
	std::getline(std::cin, line);
	int nStates = atoi(line.c_str());
	std::cout << "Num States: " << nStates << std::endl;

	// read transition lines, and for each...
	std::getline(std::cin, line);
	while (isupper(line[0]))
	{
		// lines like "S, read, a, A", "S, pop, a, A", "S, push, a, A"

		// from state
		char fromState = line[0];

		// actions are "read", "push", "pop"
		PDA::Action action;
		if (line[3] == 'r')
			action = PDA::Action::READ;
		else if (line[3] == 'p' && line[4] == 'u')
			action = PDA::Action::PUSH;
		else
			action = PDA::Action::POP;

		// data character
		char dataCharacter = line[line.length() - 4];

		// to state
		char toState = line[line.length() - 1];

		// add states to the PDA as we identify them in the input
		pda.AddState(fromState, action, dataCharacter);
		pda.AddState(toState, PDA::Action::UNKNOWN, dataCharacter);

		// add transitions to the PDA
		pda.AddTransition(fromState, dataCharacter, toState);

		// next line
		std::getline(std::cin, line);

	}
	
	//
	// read and process input strings
	//

	// read each line and...
	// NOTE: we've already read the first line of input strings above
	bool done = false;

	while(!done)
	{
		std::cout << "Testing " << line << std::endl;
		if (pda.Accept(line))
		{
			//print the correct result
			std::cout << "accept";
		}
		else
		{
			//print the correct result
			std::cout << "reject";

		}
		std::cout << "\t" << line << std::endl;

		//read next line
		std::cin.peek();

		if (!std::cin.eof())
			std::getline(std::cin, line);
		else
			done = true;
	} 

	// ask the PDA to accept/reject the input string

}

