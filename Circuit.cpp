/*
Circuit.cpp   Implementation of the Circuit class
Author:       Kaitlyn Wiseman
Modified:     30 Oct 2020
*/

#pragma once

#include "Circuit.h"
#include "Wire.h"
#include "Gate.h"
#include <string>

// constructor
Circuit::Circuit() {

}


// destructor
Circuit::~Circuit() {

}


// main() functions

// step 1.
bool Circuit::ReadCircuit(string filename) {
	ifstream in;
	string keyword;
	string name;
	int number;
	string delay;
	int input0;
	int input1;
	int output;

	in.open(filename + ".txt");
	if (!in.is_open())
	{
		cerr << "could not open file " << filename << ".txt" << endl;
		return false;
	}

	in >> keyword;
	while (!in.eof())
	{
		// circuit name
		if (keyword == "CIRCUIT")
		{
			in >> this->name;
		}
		// io wires
		else if (keyword == "INPUT" || keyword == "OUTPUT")
		{
			in >> name >> number;

			MakeWire(number, name);
			ioWires.push_back(wires.at(number));
		}
		// not gate
		else if (keyword == "NOT")
		{
			in >> delay >> input0 >> output;

			// check whether the wires exist and make them if they don't
			MakeWire(input0);
			MakeWire(output);

			gates.push_back(new Gate(keyword, atoi(delay.c_str()), 
				wires.at(input0), wires.at(output)));

			wires.at(input0)->AddGate(gates.back());
		}
		// other gates
		else if (keyword == "AND" || keyword == "OR" || keyword == "XOR"
			|| keyword == "NAND" || keyword == "NOR" || keyword == "XNOR")
		{
			in >> delay >> input0 >> input1 >> output;

			MakeWire(input0);
			MakeWire(input1);
			MakeWire(output);

			gates.push_back(new Gate(keyword, atoi(delay.c_str()),
				wires.at(input0), wires.at(input1), wires.at(output)));

			wires.at(input0)->AddGate(gates.back());
			wires.at(input1)->AddGate(gates.back());
		}
		// invalid input
		else
		{
			cerr << "invalid keyword " << keyword 
				<< ". skipping this line." << endl;

			getline(in, keyword);
		}

		in >> keyword;
	}

	in.close();
}

// step 2.
bool Circuit::ReadVector(string filename) {

}

// step 3.
bool Circuit::Simulate() {

}

// step 4.
bool Circuit::Print() {
	for (Wire* w : ioWires)
	{
		w->Print();
	}

	// print the numbers at the bottom
}


void Circuit::MakeWire(int wireNo, string iname = "") {
	if (wires.size() <= wireNo)
	{
		wires.resize(wireNo + 1, NULL);
	}
	if (wires.at(wireNo) == NULL)
	{
		wires.at(wireNo) = new Wire(iname, wireNo);
	}
}