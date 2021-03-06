/*
 * Main.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: Lieven Plasmans, Luke Nooteboom
 */

#include <iostream>
#include <fstream>
#include <string>
#include "JobShop.h"
#include <memory>

int main(int argc, char **argv) {
	char *filename;
	if (argc >= 2) {
		filename = argv[1];
	} else {
		std::cout << "Please specify a filename" << std::endl;
		return 1;
	}
	std::ifstream istrm(filename, std::ios::binary);
	if (istrm.fail()) {
		std::cout << "Failed to open file: " << filename << std::endl;
		return 1;
	}
	JobShop* js = new JobShop(istrm);
	js->start();
	//js->print();

	istrm.close();

	return 0;
}


