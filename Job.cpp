/*
 * Job.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#include <vector>
#include "Job.h"

Job::Job()
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
