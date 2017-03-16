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
	JobShop(std::ifstream& _istrm);
	virtual ~JobShop();
	void print();

private:
	std::ifstream& istrm;
	std::vector<Job> jobs;
	std::vector<Machine> machines;
	Job* critPath;

	int nrofJobs;
	int nrofMachines;
	int currentTime;
	int completedJobs;

	int getNextValue(bool& newLine);
	void parseJobs();
	void calcCritPath();
	void doScheduling();
};

#endif /* JOBSHOP_H_ */
