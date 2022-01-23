#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>

#include "Nomad.h"

int main(int argc, char* argv[]) {

	// Make sure a file name is supplied
	// TODO: Add window dialogue for Windows when a file name is not supplied
	if (argc < 2) {
		std::cerr << "[ERROR]: No ROM File Supplied" << std::endl;
		return 2;
	}

	// Open the file, make sure it isn't empty
	std::ifstream inputFile{ argv[1] };
	if (!inputFile) {
		std::cerr << "[ERROR]: Couldn't open ROM file, or empty file" << std::endl;
		return 1;
	}

	// Check for the signature at the beginning of the file to make sure it's the correct type
	// TODO: Maybe add support for .BIN files?
	std::string x{};
	std::getline(inputFile, x);
	if (x != "v2.0 raw") {
		std::cerr << "[ERROR]: Not correct file type (Logisim ROM)" << std::endl;
		return 3;
	}

	// Read the contents of the file to a vector
	std::vector<uint16_t> inputRom;
	while (inputFile) {
		std::getline(inputFile, x);
		if (x != "" || x != "\n") {
			inputRom.push_back(std::stoul(x, nullptr, 16));
		}
	}

	std::cout << "Starting Emulation of " << argv[1] << std::endl;

	Nomad emu(inputRom);
	emu.startEmulation();

	std::cout << std::endl << "Emulation Ended. Press [Enter] to Quit." << std::endl;
	std::cin.get();
	return 0;
}