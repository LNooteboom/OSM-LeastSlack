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
	///Constructor
	/**
	 * Constructs the scheduler.
	 * @param _istrm A stream to the input
	 */
	JobShop(std::ifstream& _istrm);
	virtual ~JobShop();

	//Starts scheduling
	void start();

	///Prints all jobs and tasks
	void print();

private:
	///File stream to the input
	std::ifstream& istrm;

	///Vector of jobs
	std::vector<Job> jobs;

	///Vector of machines
	std::vector<Machine> machines;

	///The critical path
	Job* critPath;

	///Number of jobs
	int nrofJobs;
	///Number of machines
	int nrofMachines;
	///Current time
	int currentTime;
	///Number of completed jobs
	int completedJobs;

	///Parses the file input and creates all jobs and tasks
	/**
	 * Parses the file input and creates all jobs and tasks.
	 */
	void parseJobs();

	///calculates the critical path
	/**
	 * calculates the critical path and stores it in critPath
	 */
	void calcCritPath();

	///Skips time forward and orders the machines to find a new task if it completed
	/**
	 * Skips time forward and orders the machines to find a new task if it completed.
	 * Finds the time to be forwarded first by scanning the list of machines and finding
	 * the shortest amount remaining.
	 */
	void doScheduling();
};

#endif /* JOBSHOP_H_ */
