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

	///Gets the time remaining of the task this machine is currently
	///executing
	int getTimeRemaining() const;

	///Scans the list of jobs and allocates a new task to this machine
	/**
	 * Scans the list of jobs and allocates a new task to this machine
	 * based on the least slack time algorithm.
	 */
	void getNextJob(int curTime, std::vector<Job>& jobs, const Job& critPath);

	///Decrements the time remaining on this machine's current task
	/**
	 * Decrements the time remaining on this machine's current task
	 * and frees it if the time remaining reaches zero
	 */
	bool skipTime(int amount, int curTime);

	///Returns this machine's id
	int getId() const
	{
		return id;
	}

	///Returns this machine's current job
	Job* getCurJob() const
	{
		return curJob;
	}

private:
	///This machine's id
	int id;

	///The job this machine is currently executing
	Job* curJob;
};

#endif /* MACHINE_H_ */
