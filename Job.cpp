/*
 * Job.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: Lieven Plasmans, Luke Nooteboom
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
		return INT_MIN;
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

Task* Job::getCurrentTask()
{
	if (currentTask < tasks.size())
	{
		return &(tasks[currentTask]);
	}
	else
	{
		return NULL;
	}
}

int Job::getId() const
{
	return id;
}

int Job::getNrOfTasks() const
{
	return tasks.size();
}

const std::vector<Task>& Job::getTasks() const
{
	return tasks;
}

void Job::nextTask()
{
	currentTask++;
}

int Job::getEndTime() const
{
	return endTime;
}

void Job::setEndTime(int endTime)
{
	this->endTime = endTime;
}

int Job::getStartTime() const
{
	return startTime;
}

void Job::setStartTime(int startTime)
{
	this->startTime = startTime;
}

int Job::getCurrentTaskDuration() const
{
	if (currentTask >= tasks.size())
	{
		return INT_MAX;
	}
	else
	{
		return tasks[currentTask].getDuration();
	}
}

int Job::getCurrentMachineId() const
{
	if (currentTask >= tasks.size())
	{
		return -1;
	}
	else
	{
		return tasks[currentTask].getMachineId();
	}
}

