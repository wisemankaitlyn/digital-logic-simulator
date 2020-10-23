/*
Wire.h    Specification of the Wire class.
Author:   Kaitlyn Wiseman
Modified: 22 Oct 2020
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

	// getter
	int    at       (int time      ) const { return values.at(time); };
	string GetName  (              ) const { return name;            };
	int    GetWireNo(              ) const { return wireNo;          };
	Gate*  GetGate  (int gateNo = 0) const { toGate.at(gateNo);      };

	// setter
	void SetValue (int time, int val);  // implemented in .cpp
	void SetName  (string iname     ) { name = iname;         };
	void SetWireNo(int iwireNo      ) { wireNo = iwireNo;     };
	void AddGate  (Gate& g          ) { toGate.push_back(&g); };

	
protected:
	string        name;    // if it's a named input/output/whatever
	int           wireNo;
	vector<int>   values;  // -1: don't-care, 0: low, 1: high
	vector<Gate*> toGate;  // gates this wire is an input to

};