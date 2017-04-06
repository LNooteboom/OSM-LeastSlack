/*
 * JobShop.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: Lieven Plasmans, Luke Nooteboom
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
	//get number of jobs and machines from first line
	std::string firstLine;
	std::getline(istrm, firstLine);
	std::size_t pos;
	nrofJobs = std::stoi(firstLine, &pos);
	nrofMachines = std::stoi(firstLine.substr(pos));

	//Initialize the machines
	for (int i = 0; i < nrofMachines; i++)
	{
		machines.push_back(Machine(i));
	}
	//Parse the file into jobs and tasks
	parseJobs();

}

JobShop::~JobShop()
{
	// TODO Auto-generated destructor stub
}

void JobShop::start()
{
	//Calculate the critical path of the starting situation
	//And assign the first jobs
	calcCritPath();
	for (unsigned int i = 0; i < machines.size(); i++)
	{
		//std::cout << "ls: " << i << ": ";
		machines[i].getNextJob(currentTime, jobs, *critPath);
	}

	//Do the actual scheduling while there are still uncompleted jobs
	while (completedJobs < nrofJobs)
	{
		//calcCritPath();
		doScheduling();
	}

	//Print the start and end time of each job
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
			//Find first non-whitespace character
			pos = line.find_first_not_of(wspaceChars, pos);
			if (pos == std::string::npos || pos >= line.size() - 1) {
				//Break if the end of the line is reached
				break;
			}

			std::size_t newPos;
			//Get the machine number
			int machineNum;
			machineNum = std::stoi(line.substr(pos), &newPos);
			//Adjust the current position
			pos += newPos;

			//Get the duration
			pos = line.find_first_not_of(wspaceChars, pos);
			int duration = std::stoi(line.substr(pos), &newPos);
			pos += newPos;

			//Get a reference to the current machine
			Machine& curMachine = machines[machineNum];
			//Add this task to the current job
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
		//Get the job which takes the longest
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
	//Look in all the machines and get the task which has the lowest duration
	//remaining
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

	//Skip time by the lowest duration
	currentTime += lowestDuration;
	for (unsigned int i = 0; i < machines.size(); i++)
	{
		if (machines[i].skipTime(lowestDuration, currentTime))
		{
			completedJobs++;
			//std::cout << completedJobs << std::endl;
		}
	}

	//Recalculate the critical path
	calcCritPath();
	//Assign new jobs for each machine
	for (unsigned int i = 0; i < machines.size(); i++)
	{
		if (machines[i].getTimeRemaining() == 0) //If this machine has no task or task has ended
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
