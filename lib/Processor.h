#include <iostream>
#include <string>
#include <map>
#include <cstdint>

using namespace std;

class MemoryMapper {
    struct data {
        string ins;
        uint8_t val;
    };

    public:
        map<uint16_t, data> memory;
        void writeIns(uint16_t address, string ins) {
            data d;
            d.ins = ins;
            memory[address] = d;
        }
        void writeVal(uint16_t address, uint8_t val) {
            data d;
            d.val = val;
            memory[address] = d;
        }
        string readIns(uint16_t address) {
            return memory[address].ins;
        }
        uint8_t readVal(uint16_t address) {
            return memory[address].val;
        }
        void display() {
            cout<< "--------------------------------"<<endl;
            for(auto i:memory) {
                if(i.second.ins!="")
                    cout<< hex << i.first<<" "<< i.second.ins<<endl;
                else
                    cout<< hex << i.first<<" "<< hex << unsigned(i.second.val)<<endl;
            }
            cout<< "--------------------------------"<<endl;
        }
};

class Processor {
    public:
        uint8_t A,B,C,D,E,H,L;
        uint16_t SP,PC;
        bool flag[8];
        MemoryMapper memory;
        Processor() {
            A=0;
            B=0;
            C=0;
            D=0;
            E=0;
            H=0;
            L=0;
            SP=0;
            PC=0;
            for(int i=0;i<8;i++)
                flag[i]=false;
        }
        void setFlag(int f) {flag[f]=true;}
        void resetFlag(int f) {flag[f]=false;}
        bool getFlag(int f) {return flag[f];}
        void showReg() {
            cout<< "--------------------------------"<<endl;
            cout<<"A: "<< hex << unsigned(A)<<endl;
            cout<<"B: "<< hex << unsigned(B)<<endl;
            cout<<"C: "<< hex << unsigned(C)<<endl;
            cout<<"D: "<< hex << unsigned(D)<<endl;
            cout<<"E: "<< hex << unsigned(E)<<endl;
            cout<<"H: "<< hex << unsigned(H)<<endl;
            cout<<"L: "<< hex << unsigned(L)<<endl;
            cout<<"SP: "<< hex << unsigned(SP)<<endl;
            cout<<"PC: "<< hex << unsigned(PC)<<endl;
            cout<<"Flags: ";
            for(int i=7;i>=0;i--) {
                if (i==1 || i==3 || i==5)
                    cout << "-" << " ";
                else
                    cout<<flag[i]<<" ";
            }
            cout<<"\n--------------------------------"<<endl;
        }
};

Processor processor;