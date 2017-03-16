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
	int getNextES(const Job& critPath);
	int getNextLS(const Job& critPath);
	int getTotalDuration() const;

	const Task& getCurrentTask() const
	{
		return tasks[currentTask];
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

	bool isInProgress() const
	{
		return inProgress;
	}

	void setInProgress(bool inProgress)
	{
		this->inProgress = inProgress;
	}

private:
	std::vector<Task> tasks;
	int id;
	unsigned int currentTask;
	bool inProgress;
};

#endif /* JOB_H_ */
