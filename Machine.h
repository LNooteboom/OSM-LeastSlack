/*
 * Machine.h
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#ifndef MACHINE_H_
#define MACHINE_H_

class Task;
class Machine
{
public:
	Machine(int _id);
	virtual ~Machine();

	int getId() const
	{
		return id;
	}

private:
	Task* curTask;
	int id;
};

#endif /* MACHINE_H_ */
