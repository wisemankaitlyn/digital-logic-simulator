/*
Main.cpp  Just a little something to work out what the classes
			need to do
Author:   Kaitlyn Wiseman
Modified: 08 Nov 2020
*/

#define TEST 0

using namespace std;

#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include "Wire.h"
#include "Gate.h"
#include "Event.h"
#include "Circuit.h"


int main()
{
	string filename;
	Circuit cir;

	cout << "What is the name of the circuit test file (base name only)?  ";

	cin >> filename;

	if (!cir.ReadCircuit(filename))
	{
		cout << "ERROR reading circuit file" << endl;
		return 1;
	}

	if (!cir.ReadVector(filename))
	{
		cout << "ERROR reading vector file" << endl;
		return 1;
	}

	if (TEST)
	{
		cir.PrintWires();
		cir.PrintGates();
		cir.PrintQueue();
	}

}
