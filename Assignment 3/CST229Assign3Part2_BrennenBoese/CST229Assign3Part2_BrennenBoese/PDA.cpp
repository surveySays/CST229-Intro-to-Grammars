//Brennen Boese
//CST229 
//Assignment 3

#include "PDA.h"
#include <stack>

class NoTransitionException {};

PDA::PDA() : startState('0')
{
	// nothing to do here, move along
}

void PDA::AddState(char stateName, PDA::Action action, char dataCharacter)
{
	// first see if the state alrady exists
	auto foundState = stateTable.find(stateName);
	if (foundState == stateTable.end())
	{
		// state does not yet exist
		// add it!
		stateTable.emplace(stateName, StateAction(action, dataCharacter));

		//see if this is the first state added...
		if (startState == '0' && stateName != 'F')
		{
			startState = stateName;
		}
	}
	else
	{
		// state already exists in the table

		// IF the state already exists with an unknown action
		// AND the new action is NOT unknown
		// THEN, update the state's action

		if (foundState->second.action == Action::UNKNOWN && action != Action::UNKNOWN)
		{
			// update it!
			foundState->second.action = action;
			foundState->second.dataCharcter = dataCharacter;
		}
	}
}

void PDA::AddTransition(char fromStateName, char inputChar, char toStateName)
{
	//std::map<std::pair<char, char>, char> transitionTable; //fromState/dataChar -> toState
	transitionTable[std::pair<char, char>(fromStateName, inputChar)] = toStateName;
}

bool PDA::Accept(const std::string& s)
{
	//run the state machine on the input s 
	try 
	{
		int tapeIndex = 0;
		std::stack<char> stack;

		char currentState = startState;

		while (true)
		{
			char dataChar;

			Action action = stateTable.find(currentState)->second.action;
			switch (action)
			{
				case Action::READ:
					//read the tape to get the next input character
					dataChar = ReadTape(s, tapeIndex);
					break;

				case Action::PUSH:
					//push the specificied character onto the stack
					//the character is in the state table for the current state
					dataChar = stateTable.find(currentState)->second.dataCharcter;
					PushStack(stack, dataChar);
					break;

				case Action::POP:
					//pop the character off the stack to get the data character
					dataChar = PopStack(stack);
					break;

				case Action::ACCEPT:
					//we have found the accept state! accept the string
					return true;

			default:
				//probably an error?
				throw "Unknown state action! Panic!";
				break;
			}
			//transition to the next state
			currentState = NextState(currentState, dataChar);

		}
	}
	catch (NoTransitionException)
	{
		//machine crashed, no transition found
		return false;
	}
}

char PDA::ReadTape(const std::string& tape, int& index)
{
	//return the characer at the current index and then advance the index
	//or, return 'z' if we are off the end of the tape
	if (index >= tape.length())
		return 'z';

	return tape[index++];
}

char PDA::PopStack(std::stack<char>& stack)
{
	//pop and return the character from the top of the stack
	//or, return 'z' of the stack is already empty
	char c = 'z';

	if (!stack.empty())
	{
		c = stack.top();
		stack.pop();
	}

	return c;
}

void PDA::PushStack(std::stack<char>& stack, char c)
{
	//push the character onto the top of the stack
	stack.push(c);
}

char PDA::NextState(char currentState, char inputChar)
{
	//look up the next state from the transition table
	//based on the current state and data character
	//or, throw NoTransitionException if there is no valid transition

	auto iter = transitionTable.find(std::pair<char, char>(currentState, inputChar));
	if (iter == transitionTable.end())
		throw NoTransitionException();

	return iter->second;
}
