/*
Event.cpp    Definition of the Event class
Author:      Kaitlyn Wiseman
Modified:    08 Nov 2020
*/

#pragma once

#include "Event.h"

bool Event::operator==(const Event& rhs) const {
	if (this->wireNum == rhs.wireNum
		&& this->time == rhs.time
		&& this->value == rhs.value)
	{
		return true;
	}
	return false;
}