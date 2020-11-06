/*
Circuit.h   Implementation of the Circuit class
Author:     Kaitlyn Wiseman
Modified:   27 Oct 2020
*/

#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

#include "Circuit.cpp"

class Event;
class Gate;
class Wire;

#include "Event.h"

using namespace std;
typedef priority_queue<Event, vector<Event>, less<Event>> Queue;

class Circuit {
public:
	// constructor
	Circuit();

	// destructor
	~Circuit();
	
	// to use in main()
	bool ReadCircuit(string filename);
	bool ReadVector (string filename);
	bool Simulate   (               );
	bool Print      (               );

	// other
	void MakeWire(int wireNo, string iname = "");

protected:
	string name;
	vector<Wire*> wires;    // reminder: whenever you .resize() these vectors
	vector<Wire*> ioWires;  //           of pointers, default init should be 
	vector<Gate*> gates;    //           NULL
	Queue q;
};