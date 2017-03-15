/*
 * Task.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#include "Task.h"

Task::Task(Machine& _machine, int _duration, Task* _prevTask)
:duration(_duration),
 machine(_machine),
 prevTask(_prevTask)
{
	// TODO Auto-generated constructor stub

}

Task::~Task()
{
	// TODO Auto-generated destructor stub
}

int Task::getES() {

}

int Task::getLS() {

}
