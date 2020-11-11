/*
Circuit.cpp   Implementation of the Circuit class
Author:       Kaitlyn Wiseman
Modified:     10 Nov 2020
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
	bool flag = true;
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

			flag = false;

			getline(in, keyword);
		}

		in >> keyword;
	}

	in.close();
	return flag;
}

// step 2.
bool Circuit::ReadVector(std::string filename) {
	bool flag = true;
	std::ifstream in;
	std::string keyword;
	std::string wireName;
	int time;
	std::string tempval;
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
			in >> wireName >> time >> tempval;

			if (tempval == "X")
			{
				val = -1;
			}
			else
			{
				val = atoi(tempval.c_str());
			}

			for (Wire* w : ioWires)
			{
				if (w->GetName() == wireName)
				{
					q.push(Event(w->GetWireNo(), time, val));
					break;
				}
			}
		}
		else
		{
			// this line is invalid input...
			flag = false;
		}

		in >> keyword;
	}

	in.close();
	return flag;
}

// step 3.
bool Circuit::Simulate() {

	while (!q.empty())
	{
		// get the next event
		Event e = q.top();
		q.pop();

		Wire* w = wires.at(e.GetWire());
		int val = e.GetValue();
		int time = e.GetTime();
		// implement it
		w->SetValue(time, val);

		// find out if it has any lingering effects
		// + add addl events accordingly
		int i = 0;
		while (true)
		{
			try {
				Gate* g = w->GetGate(i);

				// find out whether the value changed
				if (g->Evaluate(time) != 
					g->GetOutput()->at(time + g->GetDelay()))
				{
					// yes, the value has changed.

					// find out if there's a duplicate event in the
					// queue
					Event n(g->GetOutput()->GetWireNo(), time + g->GetDelay(),
						g->Evaluate(time));

					if (!IsInQueue(n))
					{
						// if there's no duplicate, put the event in
						q.push(n);
					}
					
					// also go ahead and set the wire...
					//wires.at(n.GetWire())->SetValue(n.GetTime(), n.GetValue());

				}
			}
			// if we index out of the vector range, we've exhausted
			// the number of gates
			catch (std::out_of_range)
			{
				break;
			}
			i++;
		}
		
	}
	return true;
}

// step 4.
bool Circuit::Print() {
	std::cout << "Circuit: " << name << std::endl;
	std::cout << "Wire traces:" << std::endl;

	int time = ioWires.at(0)->GetValuesSize();
	int nameLen = ioWires.at(0)->GetName().length();

	for (Wire* w : ioWires)
	{
		if (w->GetValuesSize() > time)
		{
			time = w->GetValuesSize();
		}

		if (w->GetName().length() > nameLen)
		{
			nameLen = w->GetName().length();
		}
	}

	for (Wire* w : ioWires)
	{
		w->Print(time, nameLen);
	}

	// print the numbers at the bottom
	std::cout << "   0";
	while (time > 0)
	{
		if (time >= 10)
		{
			std::cout << "    5    0";
			time -= 10;
		}
		else if (time >= 5)
		{
			std::cout << "    5";
			time = 0;
		}
		else
		{
			time = 0;
		}
		
	}

	std::cout << std::endl << std::endl;

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

bool Circuit::IsInQueue(Event& e)
{
	Queue temp = q;

	while (!temp.empty())
	{
		Event qe = temp.top();
		temp.pop();

		if (qe == e)
		{
			return true;
		}
	}

	return false;
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