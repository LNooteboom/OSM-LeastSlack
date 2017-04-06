/*
 * Machine.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: Lieven Plasmans, Luke Nooteboom
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
		return 0; //Return 0 if this machine isn't doing anything
	}
	return curJob->getCurrentTaskDuration();
}

void Machine::getNextJob(int curTime, std::vector<Job>& jobs, const Job& critPath)
{
	//Get the next task with the lowest slack time
	Job* bestCandidate = NULL;
	int leastSlack = INT_MAX;
	for (unsigned int i = 0; i < jobs.size(); i++)
	//for (int i = (int)jobs.size() - 1; i >= 0; i--)
	{
		const Task* curTask = jobs[i].getCurrentTask();
		//Check if the machine ID matches with this machine's ID
		if (curTask && curTask->getMachineId() == id)
		{
			//If this job is the critical path
			if (&(jobs[i]) == &critPath)
			{
				bestCandidate = &(jobs[i]);
				break;
			}
			//Calculate the amount of slack this job has
			int curSlack = jobs[i].getNextLS(critPath) - jobs[i].getNextES(critPath);
			if (curSlack < leastSlack)
			{
				leastSlack = curSlack;
				bestCandidate = &(jobs[i]);
			}
		}
	}
	//If there is a new task for this machine
	if (bestCandidate)
	{
		//std::cout << "job: " << bestCandidate->getId() << std::endl;
		if (bestCandidate->getStartTime() == -1)
		{
			bestCandidate->setStartTime(curTime);
		}
	}
	//Assign it
	curJob = bestCandidate;
}

bool Machine::skipTime(int amount, int curTime)
{
	bool ret = false;
	//If this machine has a task
	if (curJob && curJob->getCurrentTask())
	{
		//Calculate this job's new duration
		int newDur = curJob->getCurrentTaskDuration() - amount;
		curJob->getCurrentTask()->setDuration(newDur);
		//If the new duration equals zero
		if (newDur <= 0)
		{
			//Select the next task in this job
			curJob->nextTask();
			//If there are no more tasks in this job
			if (!curJob->getCurrentTask())
			{
				//Set it's end time and return true
				curJob->setEndTime(curTime);
				ret = true;
			}
			curJob = NULL;
		}
	}
	return ret;
}

int Machine::getId() const
{
	return id;
}

Job* Machine::getCurJob() const
{
	return curJob;
}
