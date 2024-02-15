#include <iostream>
#include <string>
#include <vector>
#include "Reader.h"

using namespace std;

vector<string> opcodes = {
    "MOV", "MVI", "LXI", "LDA", "STA", "LHLD", "SHLD", "LDAX", "STAX", "XCHG", "ADD", "ADI", "SUB", "SUI", "INR", "DCR", "INX", "DCX", "DAD", "CMA", "CMP", "JMP", "JC", "JNC", "JZ", "JNZ", "CALL", "RET", "RZ", "RNZ", "RC", "RNC", "RST", "PUSH", "POP", "XTHL", "SPHL", "HLT"
};

Reader::Instruction makeIns(const string& instruction) {
    Reader::Instruction result;
    istringstream iss(instruction);
    getline(iss, result.opcode, ' ');
    string operand;
    while(getline(iss, operand, ' ')) {
        result.operands.push_back(operand);
    }
    return result;
}

void execute(uint16_t address) {
    processor.PC = address;
    string memIns;
    Reader::Instruction ins;
    while(true) {
        memIns = processor.memory.readIns((uint16_t)processor.PC);
        ins = makeIns(memIns);
        if (ins.opcode == "HLT") break;
        if (ins.opcode == "MOV") {
            cout << ins.opcode << " " << ins.operands[0] << " " << ins.operands[1] << endl;
            // MOV(ins.operands[0], ins.operands[1]);
            processor.PC += 1;
            continue;
        }
        if (ins.opcode == "MVI") {
            uint8_t val = processor.memory.readVal(processor.PC + 1);
            cout << ins.opcode << " " << ins.operands[0] << " " << hex << unsigned(val) << endl;
            // MVI(ins.operands[0], val);
            processor.PC += 2;
            continue;
        }
        break;
    }
}

int main() {
    string x = "XCHG";
    reader.writeIns(0x2001, x);
    processor.memory.display();
    execute(0x2001);
    return 0;
}