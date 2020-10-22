#include<iostream>
#include<fstream>
#include<vector>
#include "Wire.h"
#include "Gate.h"

int main()
{
	cout << "What is the name of the circuit test file (base name only)?  ";

	// find the files, output an error if they can't be found.

	string input;
	vector<Wire*> inputs;
	vector<Wire*> outputs;
	vector<Wire*> others;
	vector<Gate*> gates;
	
	while (/*!eof*/)
	{
		cin >> input;
		if (input == "INPUT")
		{
			Wire* temp(cin>>)
		}
	}
}
