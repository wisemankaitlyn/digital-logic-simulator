/*
Wire.cpp  Definition of the Wire class.
Author:   Kaitlyn Wiseman
Modified: 12 Nov 2020
*/

#pragma once

class Gate;

#include "Wire.h"


// CONSTRUCTOR
Wire::Wire(std::string iname, int iwireNo) {
	name = iname;
	wireNo = iwireNo;

	values.resize(1, -1);
}


// GETTERS

// get value
int Wire::at(int time) const {
	if (time < 0)
	{
		std::cerr << "invalid time entered" << std::endl;
		return 3;
	}
	else if (values.size() <= time || values.at(time) == 2)
	{ 
		// if values.at(time) DNE or hasn't been propagated (2),
		// backtrack until there's a valid value.
		for (int i = time - 1; i >= 0; i--)
		{
			if (values.size() <= i || values.at(i) == 2)
			{
				continue;
			}
			return values.at(i);
		}
		// if you run out of values to cycle through, it's undefined
		return -1;
	}
	return values.at(time);
}

// SETTERS

// set value
void Wire::SetValue(int time, int val) {

	if (time >= 0)
	{
		if (values.size() <= time) 
		{
			// initializes the new values in the vector to 2 to not interfere
			// with later value propagation (since vectors are zero-initialized)
			values.resize(time + 1, 2);
		}

		values.at(time) = val;
	}
	else
	{
		std::cerr << "invalid time entered: " << time << std::endl;
	}
}

// OTHER

// print function, to make circuit::print cleaner
std::string Wire::Print(int time, int nameLen) const
{	
	std::string output = "";
	// print the name of the wire--allows for names of
	// variable length
	output += name;
	for (int i = 0; i < nameLen - name.length() + 2; i++)
	{
		output += " ";
	}

	for (int i = 0; i < time; i++)
	{
		int val = this->at(i);

		switch (val)
		{
		case -1:
			output += "x";
			break;
		case 0:
			output += "_";
			break;
		case 1:
			output += "-";
			break;
		default: // something went wrong
			output += "?";
			break;
		}
	}

	output += "\n";

	return output;
}