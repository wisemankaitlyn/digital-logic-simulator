/*
Wire.cpp  Definition of the Wire class.
Author:   Kaitlyn Wiseman
Modified: 06 Nov 2020
*/

#pragma once

class Gate;

#include "Wire.h"


// constructor
Wire::Wire(std::string iname, int iwireNo) {
	name = iname;
	wireNo = iwireNo;

	values.resize(1, -1);
}


// destructor
Wire::~Wire() {
	for (Gate* g : drives) {
		delete g;
	}
	drives.clear();
}


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
			if (values.size() <= i || values.at(time) == 2)
			{
				continue;
			}
			return values.at(i);
		}
		// if you run out of values to cycle through, it's undefined
		return -1;
	}
	else
	{
		return values.at(time);
	}
}


// set value
void Wire::SetValue(int time, int val) {

	if (time >= 0)
	{
		if (values.size() < time) 
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


// print function, to make circuit::print cleaner
void Wire::Print(int time) const
{
	std::cout << name << "  ";

	for (int i = 0; i < time; i++)
	{
		int val = this->at(i);

		switch (val)
		{
		case -1:
			std::cout << "x";
			break;
		case 0:
			std::cout << "_";
			break;
		case 1:
			std::cout << "-";
			break;
		default: // something went wrong
			std::cout << "?";
			break;
		}
	}

	std::cout << std::endl;
}