#include "DFA.h"

class DFAState {
private:

	char name;
	bool acceptingState;
	std::map<char, DFAState*> transitions;

public:

	DFAState(char name) : name(name), acceptingState(false) {}
	void AddTranstion(char inputLetter, DFAState* toState) { transitions[inputLetter] = toState; }
	void SetAccepting() { acceptingState = true; }
	DFAState* Transition(char inputLetter)
	{
		if (transitions.find(inputLetter) != transitions.end()) {
			return transitions[inputLetter];
		}
		return nullptr;
	}
	bool IsAccepting() { return acceptingState; }
};

DFA::DFA()
{
	initState = nullptr;
}

void DFA::AddTransition(char fromState, char inputLetter, char toState)
{
	DFAState* fs = AddOrFind(fromState);
	DFAState* ts = AddOrFind(toState);
	fs->AddTranstion(inputLetter, ts);
}

void DFA::AddFinalState(char finalStateName)
{
	DFAState* s = AddOrFind(finalStateName);
	s->SetAccepting();
}

bool DFA::Accepts(const std::string& str)
{
	DFAState* currentState = initState;

	for (int i = 0; i < str.length() && currentState != nullptr; i++) {

		char inputChar = str[i];
		currentState = currentState->Transition(inputChar);
	}
	if (currentState != nullptr) {
		return currentState->IsAccepting();
	}
	return false;
}

DFAState* DFA::AddOrFind(char stateName)
{
	if (States.find(stateName) == States.end())
	{
		States[stateName] = new DFAState(stateName);
	}

	if (initState == nullptr)
	{
		initState = States[stateName];
	}
	
	return States[stateName];
}

DFA::~DFA() {
	for (auto iter = States.begin(); iter != States.end(); iter++)
	{
		delete iter->second;
	}
}