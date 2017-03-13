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
	const std::string& getFilename() const;
	void setFilename(const std::string& filename);

private:
	std::vector<Job> jobs;
	Job* critPath;
	std::string filename;
};

#endif /* JOBSHOP_H_ */
