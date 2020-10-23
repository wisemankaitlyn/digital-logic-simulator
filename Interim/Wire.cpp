/*
Wire.cpp  Definition of the Wire class.
Author:   Kaitlyn Wiseman
Modified: 22 Oct 2020
*/



#ifndef WIRE_H
#include "Wire.h"
#endif

using namespace std;


Wire::Wire(string iname, int iwireNo = -1) {
	name = iname;
	wireNo = iwireNo;

	values.resize(1);
	values.at(0) = -1;
}


Wire::~Wire() {
	for (Gate* g : toGate) {
		delete g;
	}
	toGate.clear();
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