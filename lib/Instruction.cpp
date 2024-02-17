#include <iostream>
#include <string>
#include <vector>
#include "Reader.h"
#include <map>

using namespace std;

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

void LDA(uint16_t address) {
    processor.A = processor.memory.readVal(address);
}

void STA(uint16_t address) {
    processor.memory.writeVal(address, processor.A);
}

void MOV(string dest, string src) {
    if (dest == "A") {
        if (src == "B") processor.A = processor.B;
        else if (src == "C") processor.A = processor.C;
        else if (src == "D") processor.A = processor.D;
        else if (src == "E") processor.A = processor.E;
        else if (src == "H") processor.A = processor.H;
        else if (src == "L") processor.A = processor.L;
        else if (src == "M") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.A = processor.memory.readVal(address);
        }
    }
    else if (dest == "B") {
        if (src == "A") processor.B = processor.A;
        else if (src == "C") processor.B = processor.C;
        else if (src == "D") processor.B = processor.D;
        else if (src == "E") processor.B = processor.E;
        else if (src == "H") processor.B = processor.H;
        else if (src == "L") processor.B = processor.L;
        else if (src == "M") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.B = processor.memory.readVal(address);
        }
    }
    else if (dest == "C") {
        if (src == "A") processor.C = processor.A;
        else if (src == "B") processor.C = processor.B;
        else if (src == "D") processor.C = processor.D;
        else if (src == "E") processor.C = processor.E;
        else if (src == "H") processor.C = processor.H;
        else if (src == "L") processor.C = processor.L;
        else if (src == "M") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.C = processor.memory.readVal(address);
        }
    }
    else if (dest == "D") {
        if (src == "A") processor.D = processor.A;
        else if (src == "B") processor.D = processor.B;
        else if (src == "C") processor.D = processor.C;
        else if (src == "E") processor.D = processor.E;
        else if (src == "H") processor.D = processor.H;
        else if (src == "L") processor.D = processor.L;
        else if (src == "M") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.D = processor.memory.readVal(address);
        }
    }
    else if (dest == "E") {
        if (src == "A") processor.E = processor.A;
        else if (src == "B") processor.E = processor.B;
        else if (src == "C") processor.E = processor.C;
        else if (src == "D") processor.E = processor.D;
        else if (src == "H") processor.E = processor.H;
        else if (src == "L") processor.E = processor.L;
        else if (src == "M") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.E = processor.memory.readVal(address);
        }
    }
    else if (dest == "H") {
        if (src == "A") processor.H = processor.A;
        else if (src == "B") processor.H = processor.B;
        else if (src == "C") processor.H = processor.C;
        else if (src == "D") processor.H = processor.D;
        else if (src == "E") processor.H = processor.E;
        else if (src == "L") processor.H = processor.L;
        else if (src == "M") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.H = processor.memory.readVal(address);
        }
    }
    else if (dest == "L") {
        if (src == "A") processor.L = processor.A;
        else if (src == "B") processor.L = processor.B;
        else if (src == "C") processor.L = processor.C;
        else if (src == "D") processor.L = processor.D;
        else if (src == "E") processor.L = processor.E;
        else if (src == "H") processor.L = processor.H;
        else if (src == "M") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.L = processor.memory.readVal(address);
        }
    }
    else if (dest == "M") {
        if (src == "A") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.memory.writeVal(address, processor.A);
        }
        else if (src == "B") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.memory.writeVal(address, processor.B);
        }
        else if (src == "C") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.memory.writeVal(address, processor.C);
        }
        else if (src == "D") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.memory.writeVal(address, processor.D);
        }
        else if (src == "E") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.memory.writeVal(address, processor.E);
        }
        else if (src == "H") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.memory.writeVal(address, processor.H);
        }
        else if (src == "L") {
            uint16_t address = (processor.H << 8) | processor.L;
            processor.memory.writeVal(address, processor.L);
        }
    }
}

void MVI(string dest, uint8_t val) {
    if (dest == "A") processor.A = val;
    else if (dest == "B") processor.B = val;
    else if (dest == "C") processor.C = val;
    else if (dest == "D") processor.D = val;
    else if (dest == "E") processor.E = val;
    else if (dest == "H") processor.H = val;
    else if (dest == "L") processor.L = val;
    else if (dest == "M") {
        uint16_t address = (processor.H << 8) | processor.L;
        processor.memory.writeVal(address, val);
    }
}

void LDAX(string reg) {
    if (!(reg == "B" || reg == "D")) {
        processor.PC += 1;
        return;
    }
    uint16_t address;
    if (reg == "B") {
        address = (processor.B << 8) | processor.C;
        processor.A = processor.memory.readVal(address);
        return;
    }
    if (reg == "D") {
        address = (processor.D << 8) | processor.E;
        processor.A = processor.memory.readVal(address);
        return;
    }
}

void STAX(string reg) {
    if (!(reg == "B" || reg == "D")) {
        processor.PC += 1;
        return;
    }
    uint16_t address;
    if (reg == "B") {
        address = (processor.B << 8) | processor.C;
        processor.memory.writeVal(address, processor.A);
        return;
    }
    if (reg == "D") {
        address = (processor.D << 8) | processor.E;
        processor.memory.writeVal(address, processor.A);
        return;
    }
}

void LXI(string reg, uint16_t data) {
    if (!(reg == "B" || reg == "D" || reg == "H" || reg == "SP")) {
        processor.PC += 3;
        return;
    }
    if (reg == "B") {
        processor.B = data / (16*16);
        processor.C = data % (16*16);
        return;
    }
    if (reg == "D") {
        processor.D = data / (16*16);
        processor.E = data % (16*16);
        return;
    }
    if (reg == "H") {
        processor.H = data / (16*16);
        processor.L = data % (16*16);
        return;
    }
    if (reg == "SP") {
        processor.SP = data;
        return;
    }
}

void LHLD(uint16_t address) {
    processor.L = processor.memory.readVal(address);
    processor.H = processor.memory.readVal(address + 0x1);
}

void SHLD(uint16_t address) {
    processor.memory.writeVal(address, processor.L);
    processor.memory.writeVal(address+0x1, processor.H);
}

void XCHG() {
    uint8_t temp1, temp2;
    temp1 = processor.D;
    temp2 = processor.E;
    processor.D = processor.H;
    processor.E = processor.L;
    processor.H = temp1;
    processor.L = temp2;
}

void OUT(uint8_t address) {
    processor.memory.writeVal((uint16_t)address, processor.A);
}

void IN(uint8_t address) {
    processor.A = processor.memory.readVal((uint16_t)address);
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
            MOV(ins.operands[0], ins.operands[1]);
            processor.PC += 1;
            continue;
        }
        if (ins.opcode == "MVI") {
            uint8_t val = processor.memory.readVal(processor.PC + 1);
            MVI(ins.operands[0], val);
            processor.PC += 2;
            continue;
        }
        if (ins.opcode == "LDA") {
            uint16_t address = (processor.memory.readVal(processor.PC + 2) << 8) | processor.memory.readVal(processor.PC + 1);
            LDA(address);
            processor.PC += 3;
            continue;
        }
        if (ins.opcode == "STA") {
            uint16_t address = (processor.memory.readVal(processor.PC + 2) << 8) | processor.memory.readVal(processor.PC + 1);
            STA(address);
            processor.PC += 3;
            continue;
        }
        if (ins.opcode == "LDAX") {
            LDAX(ins.operands[0]);
            processor.PC += 1;
            continue;
        }
        if (ins.opcode == "STAX") {
            STAX(ins.operands[0]);
            processor.PC += 1;
            continue;
        }
        if (ins.opcode == "LXI") {
            uint16_t val = (processor.memory.readVal(processor.PC + 2) << 8) | processor.memory.readVal(processor.PC + 1);
            LXI(ins.operands[0], val);
            processor.PC += 3;
            continue;
        }
        if (ins.opcode == "LHLD") {
            uint16_t address = (processor.memory.readVal(processor.PC + 2) << 8) | processor.memory.readVal(processor.PC + 1);
            LHLD(address);
            processor.PC += 3;
            continue;
        }
        if (ins.opcode == "SHLD") {
            uint16_t address = (processor.memory.readVal(processor.PC + 2) << 8) | processor.memory.readVal(processor.PC + 1);
            SHLD(address);
            processor.PC += 3;
            continue;
        }
        if (ins.opcode == "XCHG") {
            XCHG();
            processor.PC += 1;
            continue;
        }
        if (ins.opcode == "OUT") {
            OUT(processor.memory.readVal(processor.PC + 1));
            processor.PC += 2;
            continue;
        }
        if (ins.opcode == "IN") {
            IN(processor.memory.readVal(processor.PC + 1));
            processor.PC += 2;
            continue;
        }
        cout << "no HLT found\n";
        break;
    }
}

int main() {
    Reader reader;
    execute(0x2000);
    processor.showReg();
    processor.memory.display();
    return 0;
}