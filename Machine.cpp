/*
 * Machine.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#include "Machine.h"
#include "Task.h"
#include "Job.h"
#include <cstddef>
#include <climits>
#include <iostream>

Machine::Machine(int _id)
:id(_id),
 curJob(NULL)
{
	// TODO Auto-generated constructor stub

}

Machine::~Machine()
{
	// TODO Auto-generated destructor stub
}

int Machine::getTimeRemaining() const
{
	if (curJob == NULL || curJob->getCurrentTask() == NULL)
	{
		return 0;
	}
	return curJob->getCurrentTaskDuration();
}

void Machine::getNextJob(int curTime, std::vector<Job>& jobs, const Job& critPath)
{
	Job* bestCandidate = NULL;
	int leastSlack = INT_MAX;
	for (unsigned int i = 0; i < jobs.size(); i++)
	//for (int i = (int)jobs.size() - 1; i >= 0; i--)
	{
		const Task* curTask = jobs[i].getCurrentTask();
		if (curTask && curTask->getMachineId() == id)
		{
			if (&(jobs[i]) == &critPath)
			{
				bestCandidate = &(jobs[i]);
				break;
			}
			int curSlack = jobs[i].getNextLS(critPath) - jobs[i].getNextES(critPath);
			if (curSlack < leastSlack)
			{
				leastSlack = curSlack;
				bestCandidate = &(jobs[i]);
			}
		}
	}
	if (bestCandidate)
	{
		//std::cout << "job: " << bestCandidate->getId() << std::endl;
		if (bestCandidate->getStartTime() == -1)
		{
			bestCandidate->setStartTime(curTime);
		}
	}
	curJob = bestCandidate;
}

bool Machine::skipTime(int amount, int curTime)
{
	//int newDur = 0;
	bool ret = false;
	if (curJob && curJob->getCurrentTask())
	{

		int newDur = curJob->getCurrentTaskDuration() - amount;
		curJob->getCurrentTask()->setDuration(newDur);
		if (newDur <= 0)
		{
			curJob->nextTask();
			if (!curJob->getCurrentTask())
			{
				curJob->setEndTime(curTime);
				ret = true;
			}
			curJob = NULL;
		}
	}
	return ret;
}
