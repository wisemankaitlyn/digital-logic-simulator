/*
Main.cpp  
Author:   Kaitlyn Wiseman
Modified: 12 Nov 2020
*/


#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include "Wire.h"
#include "Gate.h"
#include "Event.h"
#include "Circuit.h"

using namespace std;

int main()
{
	string filename;
	Circuit cir;

	cout << "What is the name of the circuit test file (base name only)?  ";

	cin >> filename;

	if (!cir.ReadCircuit(filename))
	{
		cout << "ERROR reading circuit description file" << endl;
		return 1;
	}

	if (!cir.ReadVector(filename))
	{
		cout << "ERROR reading circuit vector file" << endl;
		return 1;
	}

	cout << endl;
	cout << "Simulating " << filename << ".txt." << endl;
	cout << endl;

	cir.Simulate();

	cir.Print();

	return 0;
}
