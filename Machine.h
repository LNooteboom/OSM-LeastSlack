/*
 * Machine.h
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#ifndef MACHINE_H_
#define MACHINE_H_
#include <vector>

class Job;
class Task;
class Machine
{
public:
	Machine(int _id);
	virtual ~Machine();

	void getNextJob(const std::vector<Job>* job);

	int getId() const
	{
		return id;
	}

	bool inUse() const
	{
		return curTask;
	}

private:
	Task* curTask;
	int id;
};

#endif /* MACHINE_H_ */
