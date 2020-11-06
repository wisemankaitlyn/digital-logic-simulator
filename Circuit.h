/*
Circuit.h   Implementation of the Circuit class
Author:     Kaitlyn Wiseman
Modified:   06 Nov 2020
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "Wire.h"
#include "Gate.h"
#include "Event.h"
 
class Event;
class Gate;
class Wire;

typedef std::priority_queue<Event, std::vector<Event>, std::less<Event>> Queue;

class Circuit {
public:
	// constructor
	Circuit();

	// destructor
	//~Circuit();
	
	// to use in main()
	bool ReadCircuit(std::string filename);
	bool ReadVector (std::string filename);
	bool Simulate   (               );
	bool Print      (               );

	// other
	void MakeWire(int wireNo, std::string iname = "");

	// for testing
	void PrintQueue() const;

protected:
	std::string name;
	std::vector<Wire*> wires;    // reminder: whenever you .resize() these vectors
	std::vector<Wire*> ioWires;  //           of pointers, default init should be 
	std::vector<Gate*> gates;    //           NULL
	Queue q;
};