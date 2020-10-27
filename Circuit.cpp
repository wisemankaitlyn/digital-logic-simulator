/*
Circuit.cpp   Implementation of the Circuit class
Author:       Kaitlyn Wiseman
Modified:     27 Oct 2020
*/

#include "Circuit.h"
#include "Wire.h"

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

	in.open(filename + ".txt");
	if (!in.is_open())
	{
		cerr << "could not open file " << filename << ".txt" << endl;
		return false;
	}

	in >> keyword;
	while (!in.eof())
	{
		if (keyword == "CIRCUIT")
		{

		}
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