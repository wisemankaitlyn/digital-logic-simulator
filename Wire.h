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
	Wire(string iname = "", int iwireNo = -1);

	// getter
	int  at(int time) const { return values.at(time); };
	// setter
	void SetValue(int time, int val);
	
	/* ideas for some operators?
	int operator&(Wire& rhs);
	int operator|(Wire& rhs);
	int operator^(Wire& rhs);*/
protected:
	string name;
	int    wireNo;
	vector<int> values;
};