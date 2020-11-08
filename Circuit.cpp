/*
Circuit.cpp   Implementation of the Circuit class
Author:       Kaitlyn Wiseman
Modified:     08 Nov 2020
*/

#pragma once

#include "Circuit.h"

//using namespace std;

// constructor
Circuit::Circuit() {
	
}

/*
// destructor
Circuit::~Circuit() {
	for (auto w : wires)
	{
		delete w;
	}
	wires.clear();

	for (auto w : ioWires)
	{
		delete w;
	}
	ioWires.clear();

	for (auto g : gates)
	{
		delete g;
	}
	gates.clear();
}*/


// main() functions

// step 1.
bool Circuit::ReadCircuit(std::string filename) {

	std::ifstream in;
	std::string keyword;
	std::string name;
	int number;
	std::string delay;
	int input0;
	int input1;
	int output;

	in.open(filename + ".txt");
	if (!in.is_open())
	{
		std::cerr << "could not open file " << filename << ".txt" << std::endl;
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
			std::cerr << "invalid keyword " << keyword 
				<< ". skipping this line." << std::endl;

			getline(in, keyword);
		}

		in >> keyword;
	}

	in.close();
	return true;
}

// step 2.
bool Circuit::ReadVector(std::string filename) {

	std::ifstream in;
	std::string keyword;
	std::string wireName;
	int time;
	int val;

	in.open(filename + "_v.txt");
	if (!in.is_open())
	{
		std::cerr << "could not open file " << filename << "_v.txt" << std::endl;
		return false;
	}

	in >> keyword;
	while (!in.eof())
	{
		if (keyword == "VECTOR")
		{
			// as of right now, we don't do anything with the vector name...
			in >> keyword;
		}
		else if (keyword == "INPUT")
		{
			in >> wireName >> time >> val;
			for (Wire* w : ioWires)
			{
				if (w->GetName() == wireName)
				{
					q.push(Event(w->GetWireNo(), time, val));
					break;
				}
			}
		}

		in >> keyword;
	}

	in.close();
	return true;
}

// step 3.
bool Circuit::Simulate() {
	return true;
}

// step 4.
bool Circuit::Print() {
	for (Wire* w : ioWires)
	{
		w->Print();
	}

	// print the numbers at the bottom
	return true;
}


void Circuit::MakeWire(int wireNo, std::string iname) {
	if (wires.size() <= wireNo)
	{
		wires.resize(wireNo + 1, NULL);
	}
	if (wires.at(wireNo) == NULL)
	{
		wires.at(wireNo) = new Wire(iname, wireNo);
	}
}


// for debugging - to test the contents of the queue
void Circuit::PrintWires() const {
	std::cout << "Printing all wires: " << std::endl;

	for (Wire* w : wires)
	{
		if (w == NULL) continue;

		std::cout << w->GetWireNo() << " drives ";

		int i = 0;
		while (true)
		{
			try {
				std::cout << w->GetGate(i)->GetType() << " ";
				i++;
			}
			catch (std::out_of_range)
			{
				break;
			}
		}

		std::cout << std::endl;
	}
	
	std::cout << std::endl;

	std::cout << "Printing I/O wires: " << std::endl;

	for (Wire* w : ioWires)
	{
		std::cout << w->GetName() << " " << w->GetWireNo() << " drives ";

		int i = 0;
		while (true)
		{
			try {
				std::cout << w->GetGate(i)->GetType() << " ";
				i++;
			}
			catch (std::out_of_range)
			{
				break;
			}
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void Circuit::PrintGates() const {
	std::cout << "Printing gates: " << std::endl;

	for (Gate* g : gates)
	{
		std::cout << g->GetType() << " " << g->GetDelay() << " "
			<< g->GetInput0()->GetWireNo() << " ";
		if (g->GetType() != "NOT")
		{
			std::cout << g->GetInput1()->GetWireNo() << " ";
		}

		std::cout << g->GetOutput()->GetWireNo() << std::endl;
	}

	std::cout << std::endl;
}

void Circuit::PrintQueue() const {
	Queue temp = q;

	std::cout << "Printing contents of queue: " << std::endl;

	while (!temp.empty())
	{
		Event e = temp.top();
		std::cout << e.GetWire() << " " << e.GetTime() << " "
			<< e.GetValue() << std::endl;

		temp.pop();
	}
}