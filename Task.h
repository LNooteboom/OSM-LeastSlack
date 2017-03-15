/*
 * Task.h
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#ifndef TASK_H_
#define TASK_H_
#include "Machine.h"

class Task
{
public:
	Task(Machine& _machine, int _duration, Task* _prevTask);
	virtual ~Task();
	int getES();
	int getLS();

	int getDuration() const
	{
		return duration;
	}

	void setDuration(int duration)
	{
		this->duration = duration;
	}

	const Task* getNextTask() const
	{
		return nextTask;
	}

	void setNextTask(Task* nextTask)
	{
		this->nextTask = nextTask;
	}

	int getNummer() const
	{
		return nummer;
	}

	const Task* getPrevTask() const
	{
		return prevTask;
	}

	void setPrevTask(Task* prevTask)
	{
		this->prevTask = prevTask;
	}

	const int getMachineId() const
	{
		return machine.getId();
	}

private:
	int duration;
	int nummer;
	Machine& machine;
	Task* nextTask;
	Task* prevTask;
};

#endif /* TASK_H_ */
