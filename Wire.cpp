/*
Wire.cpp  Definition of the Wire class.
Author:   Kaitlyn Wiseman
Modified: 22 Oct 2020
*/


#include "Wire.h"
using namespace std;

Wire::Wire(string iname = "", int iwireNo = -1, int iwireType = -2) {
	name = iname;
	wireNo = iwireNo;
	wireType = iwireType;

	values.resize(1);
	values.at(0) = 1;
}

void Wire::SetValue(int time, int val) {

	if (time >= 0)
	{
		// take the previous value and propagate it until time
		while (values.size() < time)
		{
			values.push_back(values.at(values.size() - 1));
		}
		// set val to time
		values.push_back(val);
	}
	else
	{
		cerr << "invalid time entered: " << time << endl;
	}
}