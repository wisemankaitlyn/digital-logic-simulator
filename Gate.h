/*
Gate.h    Specification & implementation of Gate class.
Author:   Kaitlyn Wiseman
Modified: 22 Oct 2020
*/

#pragma once
#include<iostream>
#include "Wire.h"
using namespace std;

class Gate
{
public:
	// constructors
	// regular gates (2 inputs)
	Gate(string typex, int delayx, Wire* input0x, Wire* input1x, Wire* outputx)
		: type(typex), delay(delayx), input0(input0x), input1(input1x), output(outputx) {};
	// not gates (1 input)
	Gate(string typex, int delayx, Wire* input0x,              Wire* outputx)
		: type(typex), delay(delayx), input0(input0x),                  output(outputx) {
		input1 = NULL;
	};

	// destructor
	~Gate() { delete input0; delete input1; delete output; };

	// getters
	string GetType  () const { return type;   }
	int    GetDelay () const { return delay;  }
	Wire*  GetInput0() const { return input0; }
	Wire*  GetInput1() const { return input1; }
	Wire*  GetOutput() const { return output; }

protected:
	string type;
	int delay;
	Wire* input0;
	Wire* input1;
	Wire* output;
};