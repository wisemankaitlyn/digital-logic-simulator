/*
Event.h   Definition of the Event class
Author:   Kaitlyn Wiseman
Modified: 25 Oct 2020
*/

#pragma once

class Wire;
class Gate;

class Event {
public:
	// constructors
	// default
	Event()
		: wireNum(-1), time(-1), value(-2), cnt(-1) {};
	// preferred
	Event(int iwireNum, int itime, int ivalue, int icnt)
		: wireNum(iwireNum), time(itime), value(ivalue), cnt(icnt) {};


	// getters:
	int GetWire () const { return wireNum; }
	int GetTime () const { return time;    }
	int GetValue() const { return value;   }
	int GetCnt  () const { return cnt;     }

	// setters:
	void SetWire (int iwireNum) { wireNum = iwireNum; }
	void SetTime (int itime)    { time = itime;       }
	void SetValue(int ivalue)   { value = ivalue;     }
	void SetCnt  (int icnt)     { cnt = icnt;         }

protected:
	int wireNum;
	int time;
	int value;
	int cnt;
};