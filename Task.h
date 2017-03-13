/*
 * Task.h
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#ifndef TASK_H_
#define TASK_H_
#include "Machine.h"

class Task
{
public:
	Task();
	virtual ~Task();
	int getES();
	int getLS();

private:
	int duration;
	int nummer;
	Machine* machine;
	Task* nextTask;
	Task* prevTask;
};

#endif /* TASK_H_ */
