/*
 * Task.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: Lieven Plasmans, Luke Nooteboom
 */

#include "Task.h"
#include "Machine.h"

Task::Task(int _index, Machine& _machine, int _duration)
:duration(_duration),
 machineId(_machine.getId()),
 index(_index)
{
	// TODO Auto-generated constructor stub

}

Task::~Task()
{
	// TODO Auto-generated destructor stub
}

int Task::getDuration() const
{
	return duration;
}

void Task::setDuration(int duration)
{
	this->duration = duration;
}

int Task::getIndex() const
{
	return index;
}

int Task::getMachineId() const
{
	return machineId;
}
