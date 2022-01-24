#include "Nomad.h"
#include <iostream>
#include <cstdint>
#include <vector>
#include <chrono>
#include <thread>

Nomad::Nomad(std::vector<uint16_t> inputRom, int target_clock) {
	state.rom = inputRom;
	state.TARGET_CLOCK_SPEED = target_clock;
}

int Nomad::performOp() {

	// Check to make sure we haven't reached the end of the ROM
	if (state.pc >= state.rom.size()) {
		return -1;
	}

	// Decode the next instruction
	state.instruction = state.rom[state.pc];
	state.op  = state.instruction >> 12;
	state.rs  = (state.instruction >> 8) & 0x0F;
	state.im = state.instruction & 0xFF;


	// Perform the next instruction
	switch (state.op) {
	case 0x0: NOP_00(); break;
	case 0x1: ADD_01(); break;
	case 0x2: SUB_02(); break;
	case 0x3: AND_03(); break;
	case 0x4: NOT_04(); break;
	case 0x5:  OR_05(); break;
	case 0x6: XOR_06(); break;
	case 0x7: LSL_07(); break;
	case 0x8: LSR_08(); break;
	case 0x9: MOV_09(); break;
	case 0xA: LMR_0A(); break;
	case 0xB: LRM_0B(); break;
	case 0xC: JEQ_0C(); break;
	case 0xD: JNQ_0D(); break;
	case 0xE: JGT_0E(); break;
	case 0xF: JLT_0F(); break;
	default: 
		return -2;
	}

	state.pc += 1;
	return 0;
}

void Nomad::startEmulation() {

	// Standard Emulation Loop
	while (true) {
		// Perform the operation, store the result
		int result = performOp();
		
		// If the result is an error, stop execution and print error
		if (result != 0) {
			switch (result) {
				// -1: End of Program			
				case -1: break;
				// -2: Unknown Opcode
				case -2:
					std::cerr << "\n[ERROR]: Unknown Opcode" << std::endl;
					break;
				// Any other error we haven't written a case for yet
				default:
					std::cerr << "\n[ERROR]: Unknown Error" << std::endl;
					break;
			}

			// Break from the infinite loop
			break;
		}
		// Print the character stored in the TTY register
		std::cout << state.registers[10];
		// Sleep for CLOCK_SPEED milliseconds, which is an expression of 1000/Hz
		std::this_thread::sleep_for(std::chrono::milliseconds(state.TARGET_CLOCK_SPEED));
	}
	return;
}

inline void Nomad::NOP_00() {
	return;
}

inline void Nomad::ADD_01() {
	// Add A,B, output to RS
	state.registers[state.rs] = state.registers[0] + state.registers[1];
}

inline void Nomad::SUB_02() {
	// Sub A-B, output to RS
	state.registers[state.rs] = state.registers[0] - state.registers[1];
}

inline void Nomad::AND_03() {
	// AND A,B, output to RS
	state.registers[state.rs] = state.registers[0] & state.registers[1];
}

inline void Nomad::NOT_04() {
	// NOT A, output to RS
	state.registers[state.rs] = ~state.registers[0];
}

inline void Nomad::OR_05() {
	// OR A,B, output to RS
	state.registers[state.rs] = state.registers[0] | state.registers[1];
}

inline void Nomad::XOR_06() {
	// XOR A,B, output to RS
	state.registers[state.rs] = state.registers[0] ^ state.registers[1];
}

inline void Nomad::LSL_07() {
	// LSL A<<B, output to RS
	state.registers[state.rs] = state.registers[0] << state.im;
}

inline void Nomad::LSR_08() {
	// LSR A>>B, output to RS
	state.registers[state.rs] = state.registers[0] >> state.im;
}

inline void Nomad::MOV_09() {
	// Registers i0,i1,i2,i3 are input only, and cannot be output to
	if (state.rs < 0xD) {
		state.registers[state.rs] = state.im;
	}
}

inline void Nomad::LMR_0A() {
	// Contents of RS -> 0xIM
	state.registers[state.rs] = state.ram[state.im];
}

inline void Nomad::LRM_0B() {
	// Contents of 0xIM -> RS
	state.ram[state.im] = state.registers[state.rs];
}

inline void Nomad::JEQ_0C() {
	// Jump to 0xIM if A==B
	if (state.registers[0] == state.registers[1]) {
		state.pc = state.im;
	}
}

inline void Nomad::JNQ_0D() {
	// Jump to 0xIM if A!=B
	if (state.registers[0] != state.registers[1]) {
		state.pc = state.im;
	}
}

inline void Nomad::JGT_0E() {
	// Jump to 0xIM if A>B
	if (state.registers[0] > state.registers[1]) {
		state.pc = state.im;
	}
}

inline void Nomad::JLT_0F() {
	// Jump to 0xIM if A<B
	if (state.registers[0] < state.registers[1]) {
		state.pc = state.im;
	}
}