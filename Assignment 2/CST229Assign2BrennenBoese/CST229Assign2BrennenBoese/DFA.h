#pragma once

#include <map>
#include <string>
using std::string;
using std::map;

class DFAState;

class DFA
{
public:

	DFA();
	~DFA();
	void AddTransition(char fromState, char inputLetter, char toState);
	void AddFinalState(char finalStateName);
	bool Accepts(const string& str);

private:

	DFAState* initState;
	map<char, DFAState*> States;
	DFAState* AddOrFind(char stateName);

};

