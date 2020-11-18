// TM.h
// Brennen Boese, OIT
// Fall 2020
//
// Represents a Turing Machine
// implemented using a state transition table design
//

#pragma once

#include <string>
#include "Tape.h"
#include <map>

class TM
{
private: 
	class Transition
	{
	public:
		char currentState;
		char readChar;
		char writeChar;
		char direction;
		char nextState;
	};

	std::map<std::pair<int,char>, Transition> transitions;		// <currentState,readChar> -> Transition 

public:
	TM(int numTransitions);

	// direction is 'L' or 'R'
	void AddTransition(char currentState, char readChar, char writeChar, char direction, char nextState);


	// returns true if halts, false if crashes
	// expects taoe to have the input string initially
	// modifies tape as it runs
	bool Accept(Tape& t);
};

