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

	///Returns this task's remaining duration
	int getDuration() const
	{
		return duration;
	}

	///Sets this task's remaining duration
	void setDuration(int duration)
	{
		this->duration = duration;
	}

	///Returns this task's index
	int getIndex() const
	{
		return index;
	}

	///Returns the id of the machine this task must be executed on
	int getMachineId() const;

private:
	///The remaining duration
	int duration;

	///The id of the machine this task must be executed on
	int machineId;

	///The index of this task in the job's vector
	int index;

};

#endif /* TASK_H_ */
