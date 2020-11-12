/*
Gate.h    Specification & implementation of Gate class.
Author:   Kaitlyn Wiseman
Modified: 12 Nov 2020
*/

#pragma once


#include <iostream>
#include <string>
#include <vector>
#include "Wire.h"

class Wire;

class Gate
{
public:
	// CONSTRUCTORS
	// regular gates (2 inputs)
	Gate(std::string typex, int delayx, Wire* input0x, Wire* input1x, Wire* outputx)
		: type(typex), delay(delayx), input0(input0x), input1(input1x), output(outputx) {};
	// not gates (1 input, input1 init to NULL)
	Gate(std::string typex, int delayx, Wire* input0x,                Wire* outputx)
		: type(typex), delay(delayx), input0(input0x), input1(NULL   ), output(outputx) {};

	// GETTERS
	std::string GetType  () const { return type;   }
	int         GetDelay () const { return delay;  }
	Wire*       GetInput0() const { return input0; }
	Wire*       GetInput1() const { return input1; }
	Wire*       GetOutput() const { return output; }

	// OTHER
	// returns what the value of the output wire should be
	//    at (time + delay), using the values of the input(s)
	//    at time.
	int Evaluate(int time) const;

protected:
	std::string type;     // type of gate, e.g. XOR
	int         delay;    // propagation delay in unit time
	Wire*       input0;   // wire input 1
	Wire*       input1;   // wire input 2
	Wire*       output;   // wire output
};