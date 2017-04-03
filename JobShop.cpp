/*
 * JobShop.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#include <vector>
#include <iostream>
#include "JobShop.h"
#include "Machine.h"
#include <string>
#include <climits>
#include <cstring>

#define BUFFER_LEN	8

JobShop::JobShop(std::ifstream& _istrm)
:istrm(_istrm),
 currentTime(0),
 completedJobs(0)
{
	// TODO Auto-generated constructor stub
	//get args
	std::string firstLine;
	std::getline(istrm, firstLine);
	std::size_t pos;
	nrofJobs = std::stoi(firstLine, &pos);
	nrofMachines = std::stoi(firstLine.substr(pos));

	//std::cout << nrofJobs << ", " << nrofMachines << std::endl;

	for (int i = 0; i < nrofMachines; i++)
	{
		machines.push_back(Machine(i));
	}
	parseJobs();

}

JobShop::~JobShop()
{
	// TODO Auto-generated destructor stub
}

void JobShop::start()
{
	calcCritPath();

	for (unsigned int i = 0; i < machines.size(); i++)
	{
		//std::cout << "ls: " << i << ": ";
		machines[i].getNextJob(currentTime, jobs, *critPath);
	}
	while (completedJobs < nrofJobs)
	{
		//calcCritPath();
		doScheduling();
	}
	//std::cout << "end" << std::endl;
	for (unsigned int i = 0; i < jobs.size(); i++)
	{
		std::cout << i << " " << jobs[i].getStartTime() << " " << jobs[i].getEndTime() << std::endl;
	}
}

void JobShop::parseJobs()
{
	for (int i = 0; i < nrofJobs; i++) {
		const std::string wspaceChars = " \t";
		std::string line;
		std::getline(istrm, line);
		jobs.push_back(Job(i));

		std::size_t pos = 0;
		int currentIndex = 0;
		while (true) {
			pos = line.find_first_not_of(wspaceChars, pos);
			if (pos == std::string::npos || pos >= line.size() - 1) {
				break;
			}

			std::size_t newPos;
			int machineNum;
			machineNum = std::stoi(line.substr(pos), &newPos);
			pos += newPos;

			pos = line.find_first_not_of(wspaceChars, pos);
			int duration = std::stoi(line.substr(pos), &newPos);
			pos += newPos;

			Machine& curMachine = machines[machineNum];
			jobs.back().addTask(Task(currentIndex++, curMachine, duration));
		}
	}
}

void JobShop::calcCritPath()
{
	int longestDuration = -1;
	int longestDurIndex = -1;
	for (unsigned int i = 0; i < jobs.size(); i++)
	{
		if (jobs[i].getTotalDuration() > longestDuration)
		{
			longestDuration = jobs[i].getTotalDuration();
			longestDurIndex = i;
		}
	}
	//std::cout << "crit: " << longestDurIndex << "=" << longestDuration << std::endl;
	critPath = &(jobs[longestDurIndex]);
}

void JobShop::doScheduling()
{
	int lowestDuration = INT_MAX;
	for (unsigned int i = 0; i < machines.size(); i++)
	{
		if (machines[i].getCurJob())
		{
			int dur = machines[i].getCurJob()->getCurrentTaskDuration();
			if (dur < lowestDuration)
			{

				lowestDuration = dur;
			}
		}
	}
	//std::cout << "skipping: " << lowestDuration << std::endl;
	if (lowestDuration == INT_MAX) {
		std::cout << "failed" << std::endl;
		std::cout << nrofMachines << std::endl;
		abort();
	}
	currentTime += lowestDuration;
	for (unsigned int i = 0; i < machines.size(); i++)
	{
		if (machines[i].skipTime(lowestDuration, currentTime))
		{
			completedJobs++;
			//std::cout << completedJobs << std::endl;
		}
	}
	calcCritPath();
	for (unsigned int i = 0; i < machines.size(); i++)
	{
		if (machines[i].getTimeRemaining() == 0)
		{
			machines[i].getNextJob(currentTime, jobs, *critPath);
		}
	}
}

void JobShop::print()
{
	for (int i = 0; i < nrofJobs; i++)
	{
		Job& curJob = jobs[i];
		std::cout << i << ": ";

		for (int j = 0; j < curJob.getNrOfTasks(); j++)
		{
			 std::cout << curJob.getTasks()[j].getMachineId() << "-" << curJob.getTasks()[j].getDuration() << ", ";
		}
		std::cout << std::endl;
	}
}
