/*
Wire.h    Specification of the Wire class.
Author:   Kaitlyn Wiseman
Modified: 27 Oct 2020
*/

#pragma once

#ifndef IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR
#include<vector>
#endif

using namespace std;

class Gate;

class Wire {

public:
	// constructor, initializes values vector
	Wire(string iname = "", int iwireNo = -1);  // implemented in .cpp
	// destructor
	~Wire();  // implemented in .cpp

	// getters
	int    at       (int time      ) const                            ;
	string GetName  (              ) const { return name;            };
	int    GetWireNo(              ) const { return wireNo;          };
	Gate*  GetGate  (int gateNo = 0) const { drives.at(gateNo);      };

	// setters
	void SetValue (int time, int val);  // implemented in .cpp
	void AddGate  (Gate& g          ) { drives.push_back(&g); };

	// print function to make Circuit::Print() nicer
	void Print();
	
protected:
	string        name;    // if it's a named input/output/whatever
	int           wireNo;
	vector<int>   values;  // -1: don't-care, 0: low, 1: high
	vector<Gate*> drives;  // gates this wire is an input to

};