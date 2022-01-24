#pragma once
#include <cstdint>
#include <vector>

class Nomad
{
public:
	
	Nomad(std::vector<uint16_t> inputRom, int target_clock);
	int  performOp();
	void startEmulation();

	struct State {
		int TARGET_CLOCK_SPEED{ 1000 / 120 };

		uint8_t pc{ 0 };
		uint8_t registers[16];

		uint16_t instruction{ 0 };
		uint8_t op{ 0 };
		uint8_t rs{ 0 };
		uint8_t im{ 0 };

		std::vector<uint16_t> rom{ 0 };
		uint8_t ram[256]{ 0 };
	};

private:
	State state;

	inline void NOP_00();
	inline void ADD_01();
	inline void SUB_02();
	inline void AND_03();
	inline void NOT_04();
	inline void  OR_05();
	inline void XOR_06();
	inline void LSL_07();
	inline void LSR_08();
	inline void MOV_09();
	inline void LMR_0A();
	inline void LRM_0B();
	inline void JEQ_0C();
	inline void JNQ_0D();
	inline void JGT_0E();
	inline void JLT_0F();
};

