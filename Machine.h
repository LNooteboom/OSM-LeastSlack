/*
 * Machine.h
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#ifndef MACHINE_H_
#define MACHINE_H_
#include "Task.h"

class Machine
{
public:
	Machine();
	virtual ~Machine();
private:
	Task& curTask;
};

#endif /* MACHINE_H_ */
