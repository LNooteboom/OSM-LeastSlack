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

#define BUFFER_LEN	8

JobShop::JobShop(std::ifstream& _istrm)
:istrm(_istrm),
 currentTime(0),
 completedJobs(0)
{
	// TODO Auto-generated constructor stub
	//get args
	bool newLine;
	nrofMachines = getNextValue(newLine);
	nrofJobs = getNextValue(newLine);

	std::cout << nrofJobs << ", " << nrofMachines << std::endl;

	for (int i = 0; i < nrofMachines; i++)
	{
		machines.push_back(Machine(i));
	}
	if (!newLine)
	{
		//ignore next chars until newline;
		char c;
		do {
			istrm.get(c);
		} while (c != '\n');
	}
	parseJobs();
	calcCritPath();

	for (unsigned int i = 0; i < machines.size(); i++)
	{
		//std::cout << "ls: " << i << ": ";
		machines[i].getNextJob(currentTime, jobs, *critPath);
	}
	while (completedJobs < nrofJobs)
	{
		doScheduling();
	}
	std::cout << "end" << std::endl;
	for (unsigned int i = 0; i < jobs.size(); i++)
	{
		std::cout << i << " " << jobs[i].getStartTime() << " " << jobs[i].getEndTime() << std::endl;
	}
}

JobShop::~JobShop()
{
	// TODO Auto-generated destructor stub
}

void JobShop::parseJobs()
{
	for (int i = 0; i < nrofJobs; i++) {
		jobs.push_back(Job(i));
		bool newLine;
		int currentIndex = 0;
		do
		{
			int machineNum = getNextValue(newLine);
			int duration = getNextValue(newLine);
			Machine& curMachine = machines[machineNum];
			jobs.back().addTask(Task(currentIndex++, curMachine, duration));
			if (!newLine)
			{
				char c;
				while (true)
				{
					c = istrm.peek();
					if (c == ' ')
					{
						istrm.get(c);
					}
					else if (c == '\n')
					{
						newLine = true;
						break;
					}
					else
					{
						break;
					}
				}
			}
		} while (!newLine);
	}

}

int JobShop::getNextValue(bool& newLine)
{
	char c;
	char arr[BUFFER_LEN];
	int count = 0;
	newLine = false;
	while (true)
	{
		istrm.get(c);
		if (istrm.eof())
		{
			if (count == 0)
			{
				return -1;
			}
			else
			{
				break;
			}
		}
		else if (c != ' ' && c != '\t' && c != '\n')
		{
			arr[count++] = c;
			if (count >= BUFFER_LEN) {
				break;
			}
		}
		else if (count != 0)
		{
			if (c == '\n')
			{
				newLine = true;
			}
			break;
		}
	}
	return std::stoi(arr);
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
	std::cout << "crit: " << longestDurIndex << std::endl;
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
	if (lowestDuration > 5000)
	{
		std::cout << "sad";
	}
	std::cout << "skipping: " << lowestDuration << std::endl;
	currentTime += lowestDuration;
	for (unsigned int i = 0; i < machines.size(); i++)
	{
		if (machines[i].skipTime(lowestDuration, currentTime, jobs, *critPath))
		{
			completedJobs++;
			//std::cout << completedJobs << std::endl;
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
