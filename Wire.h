/*
Wire.h    Specification of the Wire class.
Author:   Kaitlyn Wiseman
Modified: 22 Oct 2020
*/

#pragma once

#include<iostream>
#include<vector>
#include "Wire.cpp"
using namespace std;

class Wire
{
public:
	// constructor, initializes values vector
	Wire(string iname = "", int iwireNo = -1, int iwireType = -2);

	// getter
	int  at(int time) const { return values.at(time); };
	// setter
	void SetValue(int time, int val);
	bool IsOutput() const { return (wireType == 0); };
	bool IsInput () const { return (wireType == 1); };
	
	/* ideas for some operators?
	int operator&(Wire& rhs);
	int operator|(Wire& rhs);
	int operator^(Wire& rhs);*/
protected:
	string name;
	int    wireNo;
	int    wireType;  // = 0: output; = 1: input; = -1: other
	vector<int> values;
};