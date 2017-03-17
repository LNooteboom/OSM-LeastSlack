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
	{
		const Task* curTask = jobs[i].getCurrentTask();
		if (curTask && curTask->getMachineId() == id)
		{
			int curSlack = jobs[i].getNextLS(critPath) - jobs[i].getNextES(critPath);
			if (curSlack < 1)
			{
				curSlack = 1;
			}
			if (curSlack < leastSlack)
			{
				leastSlack = curSlack;
				bestCandidate = &(jobs[i]);
			}
		}
	}
	if (bestCandidate)
	{
		if (bestCandidate->getStartTime() == -1)
		{
			bestCandidate->setStartTime(curTime);
		}
		//std::cout <<  "cand: " <<bestCandidate->getId() << std::endl;
	} else {
		//std::cout << "none" <<std::endl;
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

		if (newDur == 0)
		{
			curJob->nextTask();
			if (curJob->getCurrentTask() == NULL)
			{
				curJob->setEndTime(curTime);
				ret = true;
			}
			curJob = NULL;
		}
	}

	/*
	if (newDur == 0)
	{
		if (curJob)
		{
			curJob->nextTask();
			if (curJob->getCurrentTask() == NULL)
			{
				//std::cout << curJob->getId() << "EndTime: " << curTime << std::endl;
				curJob->setEndTime(curTime);
				ret = true;
			}
		}
		//getNextJob(curTime, jobs, critPath);
	}*/
	return ret;
}
