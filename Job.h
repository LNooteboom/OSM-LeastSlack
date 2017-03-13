/*
 * Job.h
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#ifndef JOB_H_
#define JOB_H_
#include "Task.h"

class Job
{
public:
	Job();
	virtual ~Job();
private:
	Task tasks[];
	int nrOfTasks;
	int currentTask;
	int id;
};

#endif /* JOB_H_ */
