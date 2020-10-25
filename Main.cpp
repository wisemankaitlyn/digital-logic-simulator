/*
Main.cpp  Just a little something to work out what the classes
			need to do
Author:   Kaitlyn Wiseman
Modified: 22 Oct 2020
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include "Wire.cpp"
#include "Gate.h"
#include "Event.h"

typedef priority_queue<Event> Queue;

int main()
{
	cout << "What is the name of the circuit test file (base name only)?  ";

	// find the files, output an error if they can't be found.

	string input1;
	int input2;
	vector<Wire*> wires;
	vector<Gate*> gates;
	
	cin >> input1;
	while (/*!eof*/)
	{
		if (input1 == "INPUT")
		{
			cin >> input1;
			cin >> input2;
			Wire temp(input1, input2, 1);
			inputs.push_back(&temp);
		}
		else if (input1 == "OUTPUT")
		{
			cin >> input1;
			cin >> input2;
			Wire temp(input1, input2, 0);
			outputs.push_back(&temp);
		}
		else
		{

		}
	}
}
