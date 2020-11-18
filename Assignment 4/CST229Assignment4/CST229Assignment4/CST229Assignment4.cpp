// CST229
// Assignment 4
// Brennen Boese

#include <iostream>
#include <string>
#include "TM.h"
#include "Tape.h"

int main()
{
    //
	// read in the TM definition
	//

	// read and throw away comment
	std::string line;
	std::getline(std::cin, line);
	std::cout << "Comment: " << line << std::endl;

	// read # of transitions
	std::getline(std::cin, line);
	int nTransitions = atoi(line.c_str());
	std::cout << "Num Transitions: " << nTransitions << std::endl;

	// construct the TM
	TM tm(nTransitions);

	// read each transition line, and for each transition...
	std::getline(std::cin, line);
	while (isdigit(line[0]))
	{
		// examples "1, a, a, R, 2", "2, _, _, L, H"
		// add transition (currentState, readChar, writeChar, direction, nextState) to TM
		tm.AddTransition(line[0], line[3], line[6], line[9], line[12]);
		std::cout << "Transition: " << line << std::endl;

		// get the next line
		std::getline(std::cin, line);
	}


	// 
	// read and process input strings
	//

	// read and process each input string
	// NOTE: we've already read the first line of input strings above
	bool done = false;
	while (!done)
	{
		// load the input string into a new tape
		Tape tape(line);

		// ask the TM to accept te string
		std::cout << "Testing " << line << std::endl;
		if (tm.Accept(tape))
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

		// print contents of tape
		std::cout << "-->\t" << tape.ToString() << std::endl;

		//read next line
		std::cin.peek();
		if (!std::cin.eof())
			std::getline(std::cin, line);
		else
			done = true;
	}


}
