#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Processor.h"

using namespace std;

class Reader : public Processor{
    public:
        struct Instruction {
            string opcode;
            vector<string> operands;
        };
        string regPair(string reg) {
            string pair;
            if(reg ==  "B") return "C";
            if(reg == "D") return "E";
            if(reg == "H") return "L";
            return "";
        }
        uint8_t hexToDec8(string hexVal) 
        { 
            int len = hexVal.size(); 
            int base = 1; 
            uint8_t dec_val = 0; 
            for (int i = len - 1; i >= 0; i--) { 
                if (hexVal[i] >= '0' && hexVal[i] <= '9') { 
                    dec_val += (int(hexVal[i]) - 48) * base; 
                    base = base * 16; 
                } 
                else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') { 
                    dec_val += (int(hexVal[i]) - 55) * base; 
                    base = base * 16; 
                } 
            } 
            return dec_val; 
        } 
        uint16_t hexToDec16(string hexVal) 
        { 
            int len = hexVal.size(); 
            int base = 1; 
            uint16_t dec_val = 0; 
            for (int i = len - 1; i >= 0; i--) { 
                if (hexVal[i] >= '0' && hexVal[i] <= '9') { 
                    dec_val += (int(hexVal[i]) - 48) * base; 
                    base = base * 16; 
                } 
                else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') { 
                    dec_val += (int(hexVal[i]) - 55) * base; 
                    base = base * 16; 
                } 
            } 
            return dec_val; 
        }
        string trim(const string& str) {
            size_t first = str.find_first_not_of(' ');
            if (string::npos == first) {
                return str;
            }
            size_t last = str.find_last_not_of(' ');
            return str.substr(first, (last - first + 1));
        }
        Instruction splitIns(const string& instruction) {
            Instruction result;
            istringstream iss(instruction);
            getline(iss, result.opcode, ' ');
            string operand;
            while (getline(iss, operand, ',')) {
                result.operands.push_back(trim(operand));
            }
            return result;
        }
        bool isReg(const string& operand) {
            if(operand == "SP") return true;
            if(operand == "PSW") return true;
            if(operand.size() != 1)
                return false;
            if(operand[0] == 'A' || operand[0] == 'B' || operand[0] == 'C' || operand[0] == 'D' || operand[0] == 'E' || operand[0] == 'H' || operand[0] == 'L' || operand[0] == 'M') 
                return true;
            return false;
        }
        bool isNumber(const string& operand) {
            for(auto i:operand) {
                if(i>='0' && i<='9')
                    continue;
                else
                    return false;
            }
            return true;
        }
        bool isData(const string& operand) {
            if (isReg(operand))
                return false;
            if (operand.size() == 2 || operand.size() == 4) {
                for(auto i:operand) {
                    if(i>='0' && i<='9' || i>='A' && i<='F' || i>='a' && i<='f')
                        continue;
                    else
                        return false;
                }
                return true;
            }
            return false;
        }
        bool is8bit(const string& operand) {
            if(!isData(operand))
                return false;
            if (operand.length() <= 2) {
                return true;
            }
            return false;
        }
        bool is16bit(const string& operand) {
            if(!isData(operand))
                return false;
            if (operand.length() <= 4 && operand.length() > 2) {
                return true;
            }
            return false;
        }
        void writeIns(uint16_t address, string instruction) {
            Instruction ins = splitIns(instruction);
            processor.PC = address;
            if(ins.operands.size() == 0) {
                processor.memory.writeIns(address, ins.opcode);
                processor.PC += 0x1;
                return;
            }
            if(ins.operands.size() == 1) {
                if(isReg(ins.operands[0])) { // is register
                    processor.memory.writeIns(address, ins.opcode + " " + ins.operands[0]);
                    processor.PC += 0x1;
                    return;
                }
                else if(is8bit(ins.operands[0])) { // is 8 bit
                    processor.memory.writeIns(address, ins.opcode);
                    processor.memory.writeVal(address+0x1, hexToDec8(ins.operands[0]));
                    processor.PC += 0x2;
                    return;
                }
                else if(is16bit(ins.operands[0])) { // is 16 bit
                    processor.memory.writeIns(address, ins.opcode);
                    processor.memory.writeVal(address+0x1, (uint8_t)(hexToDec16(ins.operands[0]) % (16*16)));
                    processor.memory.writeVal(address+0x2, (uint8_t)(hexToDec16(ins.operands[0]) / (16*16)));
                    processor.PC += 0x3;
                    return;
                }
                else {
                    cout << "wrong instruction!" << endl;
                    return;
                }
            }
            if(ins.operands.size() == 2) {
                if(isReg(ins.operands[0]) && isReg(ins.operands[1])) { // both operands are registers
                    processor.memory.writeIns(address, ins.opcode + " " + ins.operands[0] + " " + ins.operands[1]);
                    processor.PC += 0x1;
                    return;
                }
                if(isReg(ins.operands[0]) && is8bit(ins.operands[1])) { // operand1 is register and operand2 is 8 bit
                    processor.memory.writeIns(address, ins.opcode + " " + ins.operands[0]);
                    processor.memory.writeVal(address+0x1, hexToDec8(ins.operands[1]));
                    processor.PC += 0x2;
                    return;
                }
                if(isReg(ins.operands[0]) && is16bit(ins.operands[1])) { // operand1 is register and operand2 is 16 bit
                    processor.memory.writeIns(address, ins.opcode + " " + ins.operands[0]);
                    processor.memory.writeVal(address+0x1, (uint8_t)(hexToDec16(ins.operands[1]) % (16*16)));
                    processor.memory.writeVal(address+0x2, (uint8_t)(hexToDec16(ins.operands[1]) / (16*16)));
                    processor.PC += 0x3;
                    return;
                }
                if(is8bit(ins.operands[0]) && is8bit(ins.operands[1])) { // operand1 is 8 bit and operand 2 is 8 bit
                    processor.memory.writeIns(address, ins.opcode);
                    processor.memory.writeVal(address+0x1, (uint8_t)(hexToDec16(ins.operands[1]) % (16*16)));
                    processor.memory.writeVal(address+0x2, (uint8_t)(hexToDec16(ins.operands[1]) / (16*16)));
                    processor.PC += 0x3;
                    return;
                }
                else {
                    cout << "wrong instruction!!" << endl;
                    return;
                }
            }
            else {
                cout << "invalid instruction!" << endl;
                return;
            }
        }
};

Reader reader;