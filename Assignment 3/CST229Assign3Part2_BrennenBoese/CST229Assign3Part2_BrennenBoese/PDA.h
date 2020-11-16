//Brennen Boese
//CST229 
//Assignment 3

// PDA.h

#pragma once

#include <string>
#include <map>
#include <stack>

class PDA
{
public:
	enum Action { PUSH, POP, READ, ACCEPT, UNKNOWN };

private:
	class StateAction
	{
	public:
		PDA::Action action;
		char dataCharcter;		// used for PUSH actions

		StateAction(PDA::Action a, char dc) { action = a; dataCharcter = dc; }
	};

	std::map<char, StateAction> stateTable;					// stateName -> action
	std::map<std::pair<char, char>, char> transitionTable;  // fromState/dataChar -> toState
	char startState;

public:
	PDA();
	void AddState(char stateName, Action action, char dataCharacter);
	void AddTransition(char fromStateName, char inputChar, char toStateName);

	bool Accept(const std::string& s);

private:
	char ReadTape(const std::string& tape, int& index);
	char PopStack(std::stack<char> & stack);
	void PushStack(std::stack<char>& stack, char c);
	char NextState(char currentState, char inputChar);

};

