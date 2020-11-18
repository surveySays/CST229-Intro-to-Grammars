// Tape.h
// Brennen Boese, OIT
// Fall 2020
//
// Represents a Turning Machine's tape
// 2-way infinite
// can move tape head left or right
// can both read and write
//

#pragma once

#include <string>


class Tape
{
public: 
	Tape(const std::string& s);

	void Move(char direction);	// direction = 'L' or 'R'
	char Read();
	void Write(char c);

	std::string ToString() const;
};

