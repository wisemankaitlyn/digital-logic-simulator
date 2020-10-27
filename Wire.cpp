/*
Wire.cpp  Definition of the Wire class.
Author:   Kaitlyn Wiseman
Modified: 27 Oct 2020
*/



#ifndef WIRE_H
#include "Wire.h"
#endif

using namespace std;


Wire::Wire(string iname = "", int iwireNo = -1) {
	name = iname;
	wireNo = iwireNo;

	values.resize(1);
	values.at(0) = -1;
}


Wire::~Wire() {
	for (Gate* g : drives) {
		delete g;
	}
	drives.clear();
}


int Wire::at(int time) const {
	if (time < 0)
	{
		cerr << "invalid time entered" << endl;
		return 3;
	}
	else if (values.size() <= time || values.at(time) == 2)
	{
		for (int i = time - 1; i >= 0; i--)
		{
			if (values.size() <= i || values.at(time) == 2)
			{
				continue;
			}
			return values.at(i);
		}
		return -1;
	}
	
}


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
		cerr << "invalid time entered: " << time << endl;
	}
}


void Wire::Print()
{
	cout << name << "  ";

	for (int val : values)
	{
		switch (val)
		{
		case -1:
			cout << "x";
			break;
		case 0:
			cout << "_";
			break;
		case 1:
			cout << "-";
			break;
		default:
			cout << "?";
			break;
		}
	}

	cout << endl;
}