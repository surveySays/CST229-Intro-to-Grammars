// CST229Assign2BrennenBoese.cpp

#include <iostream>
#include "DFA.h"

int main()
{
	DFA dfa;

	char line[256];

	//read the comment
	std::cin.getline(line, sizeof(line));

	std::cout << "Read comment: " << line << std::endl;

	// read number of states
	std::cin.getline(line, sizeof(line));

	int numStates = atoi(line);

	std::cout << "Num States: " << numStates << std::endl;

	//read in transitions
	do {
		std::cin.getline(line, sizeof(line));

		if (line[0] != 'F') {

			std::cout << "Transition: " << line << std::endl;

			char fromState = line[0];
			char inputLetter = line[3];
			char toState = line[6];

			dfa.AddTransition(fromState, inputLetter, toState);
		}

		if (line[0] == 'F') {

			std::cout << "Final State: " << line << std::endl;
		}

	} while (line[0] != 'F');

	
	for (int i = 3; line[i] != '\0'; i++) {

		if (line[i] != ',' && line[i] != ' ') {

			char finalStateName = line[i];


			dfa.AddFinalState(finalStateName);
		}
	}

	while (!std::cin.eof())
	{
		std::cin.getline(line, sizeof(line));
		std::cout << "Input String: " << line << std::endl;

		if (dfa.Accepts(line)) {
			std::cout << "accept\t ";
		}
		else {
			std::cout << "reject\t";
		}
		std::cout << "\t" << line << std::endl;
	}
}
