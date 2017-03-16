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
	int getTimeRemaining() const;
	void getNextJob(int curTime, std::vector<Job>& jobs, const Job& critPath);
	bool skipTime(int amount, int curTime, std::vector<Job>& jobs, const Job& critPath);

	int getId() const
	{
		return id;
	}

	bool inUse() const
	{
		return curJob;
	}

	Job* getCurJob() const
	{
		return curJob;
	}

private:
	int id;
	Job* curJob;
};

#endif /* MACHINE_H_ */
