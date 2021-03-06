/*
Event.h   Definition of the Event class
Author:   Kaitlyn Wiseman
Modified: 12 Nov 2020
*/

#pragma once

class Wire;
class Gate;

class Event {
public:
	// CONSTRUCTORS
	// default - probably don't need this
	Event()
		: wireNum(-1), time(-1), value(-2) {};
	// preferred
	Event(int iwireNum, int itime, int ivalue)
		: wireNum(iwireNum), time(itime), value(ivalue) {};


	// GETTERS
	int GetWire () const { return wireNum; }
	int GetTime () const { return time;    }
	int GetValue() const { return value;   }

	// SETTERS - probably don't need these
	void SetWire (int iwireNum) { wireNum = iwireNum; }
	void SetTime (int itime)    { time = itime;       }
	void SetValue(int ivalue)   { value = ivalue;     }

	// OPERATORS
	// for use with priority queue comparator
	bool operator<(const Event& rhs) const { return (this->time < rhs.time); }
	bool operator>(const Event& rhs) const { return (this->time > rhs.time); }
	// equality operator, for use with Circuit::IsInQueue
	bool operator==(const Event& rhs) const;

protected:
	int wireNum;
	int time;
	int value;
};