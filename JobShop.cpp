/*
 * JobShop.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
 */

#include <vector>
#include "JobShop.h"
#include <string>

#define BUFFER_LEN	8

JobShop::JobShop(std::ifstream& _istrm)
:istrm(_istrm),
 critPath(NULL)
{
	// TODO Auto-generated constructor stub
	//get args
	nrofMachines = getNextValue();
	nrofJobs = getNextValue();

	std::cout << nrofJobs << ", " << nrofMachines << std::endl;

	for (int i = 0; i < nrofMachines; i++)
	{
		machines.push_back(Machine());
	}
	//ignore next chars until newline;
	char c;
	do {
		istrm.get(c);
	} while (c != '\n');
	parseJobs();
}

JobShop::~JobShop()
{
	// TODO Auto-generated destructor stub
}

void JobShop::parseJobs()
{

	Task* prevTask = NULL;
	for (int i = 0; i < nrofJobs; i++) {
		jobs.push_back(Job());
		bool newLine;
		std::cout << jobs.size() << ": ";
		do
		{
			int machineNum = getNextValue();
			int duration = getNextValue();
			Machine& curMachine = machines[machineNum];
			jobs.back().addTask(Task(curMachine, duration, prevTask));
			prevTask = jobs.back().getLastTask();
			std::cout << machineNum << "-" << duration << ", ";
			char c;
			while (true)
			{
				c = istrm.peek();
				if (c == '\n' || c == ' ')
				{
					newLine = true;
					break;
				}
				else if (c != ' ')
				{
					break;
				}
				else
				{
					c = istrm.get();
				}
			}
		} while (!newLine);
		std::cout << std::endl;
	}

}

int JobShop::getNextValue()
{
	char c;
	char arr[BUFFER_LEN];
	int count = 0;
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
			break;
		}
	}
	return std::stoi(arr);
}

void JobShop::print()
{
	for (int i = 0; i < nrofJobs; i++)
	{
		Job& curJob = jobs[i];
		std::cout << i << ": " << curJob.getNrOfTasks() << std::endl;
		/*
		for (int j = 0; j < curJob.getNrOfTasks(); j++)
		{
			 //std::cout << curJob.getTasks()[j].getDuration() << ", ";
		}*/
		//std::cout << std::endl;
	}
}
