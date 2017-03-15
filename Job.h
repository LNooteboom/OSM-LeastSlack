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

class Job
{
public:
	Job(int _id);
	virtual ~Job();

	void addTask(Task task);
	Task* getLastTask();

	int getCurrentTask() const
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

private:
	std::vector<Task> tasks;
	int currentTask;
	int id;
};

#endif /* JOB_H_ */
