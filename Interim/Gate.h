/*
Gate.h    Specification & implementation of Gate class.
Author:   Kaitlyn Wiseman
Modified: 22 Oct 2020
*/

#pragma once

class Wire;

class Gate
{
public:
	// constructors
	// regular gates (2 inputs)
	Gate(string typex, int delayx, Wire* input0x, Wire* input1x, Wire* outputx)
		: type(typex), delay(delayx), input0(input0x), input1(input1x), output(outputx) {};
	// not gates (1 input)
	Gate(string typex, int delayx, Wire* input0x,                Wire* outputx)
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

	// setters
	void SetType  (string itype  ) { type   = itype;    };
	void SetDelay (int    idelay ) { delay  = idelay;   };
	void SetInput0(Wire&  iinput0) { input0 = &iinput0; };
	void SetInput1(Wire&  iinput1) { input1 = &iinput1; };
	void SetOutput(Wire&  ioutput) { output = &ioutput; };

protected:
	string type;     // type of gate, e.g. XOR
	int    delay;    // propagation delay in unit time
	Wire*  input0;   // wire input 1
	Wire*  input1;   // wire input 2
	Wire*  output;   // wire output
};