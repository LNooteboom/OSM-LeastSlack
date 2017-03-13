/*
 * JobShop.h
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#ifndef JOBSHOP_H_
#define JOBSHOP_H_

class JobShop
{
public:
	JobShop();
	virtual ~JobShop();
	void createJobs();
private:
	Job jobs[];
	Job& critPath;
};

#endif /* JOBSHOP_H_ */
