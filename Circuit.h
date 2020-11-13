/*
Circuit.h   Implementation of the Circuit class
Author:     Kaitlyn Wiseman
Modified:   12 Nov 2020
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

typedef std::priority_queue<Event, std::vector<Event>, std::greater<Event>> Queue;

class Circuit {
public:
	// constructor
	Circuit();
	
	// TO USE IN MAIN()
	bool ReadCircuit(std::string filename);
	bool ReadVector (std::string filename);
	void Simulate   (                    );
	std::string Print      (                    );

	// OTHER
	void MakeWire(int wireNo, std::string iname = "");
	// Checks to see if there is already an Event in the Queue exactly
	//    the same as e.
	bool IsInQueue     (Event& e) const;
	// An event is in conflict if there is already an event in the Queue
	//    for the same wire at the same time but with a different value.
	//    This function returns true if it finds Event e in conflict 
	//    with another event in the Queue.
	bool IsConflict    (Event& e) const;
	// Given a conflict in the Queue, this function will replace the
	//    conflicting Event with e.
	void ReplaceInQueue(Event& e)      ;

	// for debugging
	void PrintWires() const;  // prints both wires vector and
							  //    ioWires vector
	void PrintGates() const;  // prints gates vector
	void PrintQueue() const;  // prints q

protected:
	std::string        name;
	std::vector<Wire*> wires;    // reminder: whenever you .resize() these vectors
	std::vector<Wire*> ioWires;  //           of pointers, default init should be 
	std::vector<Gate*> gates;    //           NULL
	Queue              q;
};