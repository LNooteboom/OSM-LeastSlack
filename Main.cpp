/*
 * Main.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: lieven
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

	return 0;
}


