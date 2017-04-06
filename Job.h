/*
 * Job.h
 *
 *  Created on: Mar 13, 2017
 *      Author: Lieven Plasmans, Luke Nooteboom
 */

#ifndef JOB_H_
#define JOB_H_
#include "Task.h"
#include <vector>
#include <climits>
#include <cstddef>
#include <iostream>

class Job
{
public:
	Job(int _id);
	virtual ~Job();

	///Adds a task to this job.
	/**
	 * Adds a task to this job's vector of tasks.
	 */
	void addTask(Task task);

	///Gets the earliest start time for the next task
	/**
	 * Uses critPath to calculate the earliest start time at which the
	 * next task can begin.
	 */
	int getNextES(const Job& critPath) const;

	///Gets the latest start time for the next task
	/**
	 * Uses critPath to calculate the latest start time at which the
	 * next task can begin.
	 */
	int getNextLS(const Job& critPath) const;

	///Calculates the total remaining duration for this job
	/**
	 * Returns the remaining duration for this job by adding all it's
	 * tasks remaining values.
	 */
	int getTotalDuration() const;

	///Returns a pointer to the current task
	/**
	 * Returns a pointer to the current task, or NULL if all tasks are
	 * completed.
	 */
	Task* getCurrentTask();

	///Returns this job's id
	int getId() const;

	///Returns this jobs's tota number of tasks
	int getNrOfTasks() const;

	///Returns a reference to this job's vector of tasks
	const std::vector<Task>& getTasks() const;

	///Increments the task index
	void nextTask();

	///Gets this job's end time
	int getEndTime() const;

	///Sets this job's end time
	void setEndTime(int endTime);

	///Gets this job's start time
	int getStartTime() const;

	///Sets this job's start time
	void setStartTime(int startTime);

	///Returns the duration of this job's current task
	/**
	 * Returns the duration of this job's current task, or
	 * NULL if there are no more remaining tasks.
	 */
	int getCurrentTaskDuration() const;

	int getCurrentMachineId() const;

private:
	///Vector of tasks
	std::vector<Task> tasks;

	///This job's id
	int id;

	///A index to the current task
	unsigned int currentTask;

	///This job's end time
	int startTime;

	///This job's start time
	int endTime;
};

#endif /* JOB_H_ */
