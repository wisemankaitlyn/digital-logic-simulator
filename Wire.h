/*
Wire.h    Specification of the Wire class.
Author:   Kaitlyn Wiseman
Modified: 12 Nov 2020
*/

#pragma once

class Gate;

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Event.h"

class Wire {

public:
	// CONSTRUCTOR
	Wire(std::string iname, int iwireNo);

	// GETTERS
	int         at       (int time      ) const                              ;
	std::string GetName  (              ) const { return name;              };
	int         GetWireNo(              ) const { return wireNo;            };
	Gate*       GetGate  (int gateNo = 0) const { return drives.at(gateNo); };
	int     GetValuesSize(              ) const { return values.size();     };

	// SETTERS
	void SetValue (int time, int val);
	void AddGate  (Gate* g          ) { drives.push_back(g); };

	// OTHER
	// print function to make Circuit::Print() nicer
	void Print(int time, int nameLen) const;
	
protected:
	std::string        name;    // if it's a named input/output/whatever
	int                wireNo;
	std::vector<int>   values;  // -1: undetermined, 0: low, 1: high, 
								//     2: not yet def
	std::vector<Gate*> drives;  // gates this wire is an input to

};