/*
 * Task.h
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#ifndef TASK_H_
#define TASK_H_

class Machine;
class Task
{
public:
	Task(int _index, Machine& _machine, int _duration);
	virtual ~Task();


	int getDuration() const
	{
		return duration;
	}

	void setDuration(int duration)
	{
		this->duration = duration;
	}

	int getIndex() const
	{
		return index;
	}

	const int getMachineId() const;

private:
	int duration;
	Machine& machine;
	int index;

};

#endif /* TASK_H_ */
