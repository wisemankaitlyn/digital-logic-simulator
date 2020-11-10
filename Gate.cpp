/*
Gate.cpp  Implementation of Gate class.
Author:   Kaitlyn Wiseman
Modified: 06 Nov 2020
*/

#pragma once

#include "Gate.h"

int Gate::Evaluate(int time) const
{
	if (type == "NOT")
	{
		switch (input0->at(time))
		{
		case -1:
			return -1;
			break;
		case 0:
			return 1;
			break;
		case 1:
			return 0;
			break;
		}
		return 3; // error
	}
	else if (type == "AND")
	{
		if (input0->at(time) == 1 && input1->at(time) == 1)
		{
			return 1;
		}
		else if (input0->at(time) == -1 && input1->at(time) == -1)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
	else if (type == "OR")
	{
		if (input0->at(time) == 1 || input1->at(time) == 1)
		{
			return 1;
		}
		else if (input0->at(time) == -1 && input1->at(time) == -1)
		{
			return -1;
		}
		else 
		{
			return 0;
		}
	}
	else if (type == "XOR")
	{
		if (input0->at(time) == -1 || input1->at(time) == -1)
		{
			return -1;
		}
		else if ((input0->at(time) == 1 && input1->at(time) == 0)
			|| (input0->at(time) == 0 && input1->at(time) == 1))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (type == "NAND")
	{
		if (input0->at(time) == 1 && input1->at(time) == 1)
		{
			return 0;
		}
		else if (input0->at(time) == -1 && input1->at(time) == -1)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
	else if (type == "NOR")
	{
		if (input0->at(time) == 1 || input1->at(time) == 1)
		{
			return 0;
		}
		else if (input0->at(time) == -1 && input1->at(time) == -1)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
	else if (type == "XNOR")
	{
		if (input0->at(time) == -1 || input1->at(time) == -1)
		{
			return -1;
		}
		else if (input0->at(time) != input1->at(time))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}