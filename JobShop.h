/*
 * JobShop.h
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#ifndef JOBSHOP_H_
#define JOBSHOP_H_
#include "Job.h"
#include <fstream>
#include <iostream>
#include <string>

class JobShop
{
public:
	JobShop();
	virtual ~JobShop();
	void createJobs();

private:
	std::vector<Job> jobs;
	Job* critPath;
};

#endif /* JOBSHOP_H_ */
