#pragma once
#include <cstdint>
#include <vector>

class Nomad
{
public:

	const int CLOCK_SPEED = (1000 / 120);
	
	Nomad(std::vector<uint16_t> inputRom);
	int  performOp();
	void startEmulation();

	struct State {
		uint8_t pc{ 0 };
		uint8_t registers[16];

		uint16_t instruction{ 0 };
		uint8_t op{ 0 };
		uint8_t rs{ 0 };
		uint8_t im{ 0 };

		std::vector<uint16_t> rom{ 0 };
		uint16_t ram[256]{ 0 };
	};

private:
	State state;

	void NOP_00();
	void ADD_01();
	void SUB_02();
	void AND_03();
	void NOT_04();
	void  OR_05();
	void XOR_06();
	void LSL_07();
	void LSR_08();
	void MOV_09();
	void LMR_0A();
	void LRM_0B();
	void JEQ_0C();
	void JNQ_0D();
	void JGT_0E();
	void JLT_0F();

};

