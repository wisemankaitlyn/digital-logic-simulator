/*
Wire.h    Specification of the Wire class.
Author:   Kaitlyn Wiseman
Modified: 30 Oct 2020
*/

#pragma once

class Gate;

#include<iostream>
#include<vector>

using namespace std;

class Wire {

public:
	// constructor
	Wire(string iname, int iwireNo);
	// destructor
	~Wire();

	// getters
	int    at       (int time      ) const                            ;
	string GetName  (              ) const { return name;            };
	int    GetWireNo(              ) const { return wireNo;          };
	Gate*  GetGate  (int gateNo = 0) const { drives.at(gateNo);      };

	// setters
	void SetValue (int time, int val);
	void AddGate  (Gate* g          ) { drives.push_back(g); };

	// print function to make Circuit::Print() nicer
	void Print() const;
	
protected:
	string        name;    // if it's a named input/output/whatever
	int           wireNo;
	vector<int>   values;  // -1: don't-care, 0: low, 1: high, 2: not yet def
	vector<Gate*> drives;  // gates this wire is an input to

};