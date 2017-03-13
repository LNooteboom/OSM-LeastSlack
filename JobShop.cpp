/*
 * JobShop.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#include "JobShop.h"

JobShop::JobShop()
{
	// TODO Auto-generated constructor stub

}

JobShop::~JobShop()
{
	// TODO Auto-generated destructor stub
}

void JobShop::createJobs()
{
}

const std::string& JobShop::getFilename() const
{
	return filename;
}

void JobShop::setFilename(const std::string& filename)
{
	this->filename = filename;
}
