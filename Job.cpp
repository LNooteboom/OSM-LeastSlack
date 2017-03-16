/*
 * Job.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#include <vector>
#include <iostream>
#include "Job.h"

Job::Job(int _id)
:id(_id),
 currentTask(0),
 startTime(-1),
 endTime(-1)
{
	// TODO Auto-generated constructor stub
}

Job::~Job()
{
	// TODO Auto-generated destructor stub
}

void Job::addTask(Task task)
{
	tasks.push_back(task);
}

Task* Job::getLastTask()
{
	return &( tasks.back() );
}

int Job::getTotalDuration() const
{
	int dur = 0;
	for (unsigned int i = currentTask; i < tasks.size(); i++)
	{
		dur += tasks[i].getDuration();
	}
	return dur;
}

int Job::getNextES(const Job& critPath) const
{
	if (this == &critPath)
	{
		return 0;
	}
	const std::vector<Task>& critTasks = critPath.getTasks();
	const int critProgress = critPath.currentTask;

	int es = 0;
	for (unsigned int i = critProgress; i < critTasks.size(); i++)
	{
		if (tasks[currentTask].getMachineId() != critTasks[i].getMachineId())
		{
			break;
		}
		es += critTasks[i].getDuration();
	}
	return es;
}

int Job::getNextLS(const Job& critPath) const
{
	if (this == &critPath)
	{
		return 0;
	}
	int critPathDuration = critPath.getTotalDuration();
	int thisDuration = getTotalDuration();
	return critPathDuration - thisDuration;
}
