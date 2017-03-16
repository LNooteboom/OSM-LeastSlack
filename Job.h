/*
 * Job.h
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#ifndef JOB_H_
#define JOB_H_
#include "Task.h"
#include <vector>
#include <climits>
#include <cstddef>

class Job
{
public:
	Job(int _id);
	virtual ~Job();

	void addTask(Task task);
	Task* getLastTask();
	int getNextES(const Job& critPath) const;
	int getNextLS(const Job& critPath) const;
	int getTotalDuration() const;

	Task* getCurrentTask()
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

	int getCurrentTaskIndex() const
	{
		return currentTask;
	}

	int getId() const
	{
		return id;
	}

	int getNrOfTasks() const
	{
		return tasks.size();
	}

	const std::vector<Task>& getTasks() const
	{
		return tasks;
	}

	void nextTask()
	{
		currentTask++;
	}

	int getEndTime() const
	{
		return endTime;
	}

	void setEndTime(int endTime)
	{
		this->endTime = endTime;
	}

	int getStartTime() const
	{
		return startTime;
	}

	void setStartTime(int startTime)
	{
		this->startTime = startTime;
	}
	int getCurrentTaskDuration() const
	{
		if (currentTask == tasks.size())
		{
			return INT_MAX;
		}
		else
		{
			return tasks[currentTask].getDuration();
		}
	}

private:
	std::vector<Task> tasks;
	int id;
	unsigned int currentTask;
	int startTime;
	int endTime;
};

#endif /* JOB_H_ */
