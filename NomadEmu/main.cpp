#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "Nomad.h"

int main(int argc, char* argv[]) {

	/*
		Command Line Arguments:
			argv[1]: Filename of ROM
			argv[2]: Desired Clock Speed in Hz
	*/

	// If nothing was input, default to 128Hz
	int desired_clock_speed{ 1000 / 128 };

	// Make sure a file name is supplied
	// TODO: Add window dialogue for Windows when a file name is not supplied
	if (argc == 1) {
		std::cerr << "[ERROR]: No ROM File Supplied" << std::endl;
		return 2;
	}
	else if (argc == 3) { 
		// Convert the second argument to an integer
		desired_clock_speed = atoi(argv[2]);
		// If Zero was manually input, or an invalid result was entered, it functions as uncapped speed.
		if (desired_clock_speed > 0) {
			// Delay time is represented in milliseconds, so divide 1000 by our clock speed
			desired_clock_speed = 1000 / desired_clock_speed;
		}
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

	Nomad emu(inputRom, desired_clock_speed);
	emu.startEmulation();

	std::cout << std::endl << "Emulation Ended. Press [Enter] to Quit." << std::endl;
	std::cin.get();
	return 0;
}