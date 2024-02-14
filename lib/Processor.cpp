#include <string>
#include <iostream>
#include <map>
#include <cstdint>

using namespace std;

class MemoryMapper {
    struct data {
        string ins;
        uint8_t val;
    };
    map<int, data> memory;

    public:
        void writeIns(int address, string ins) {
            data d;
            d.ins = ins;
            memory[address] = d;
        }
        void writeVal(int address, uint8_t val) {
            data d;
            d.val = val;
            memory[address] = d;
        }
        string readIns(int address) {
            return memory[address].ins;
        }
        uint8_t readVal(int address) {
            return memory[address].val;
        }
        void display() {
            for(auto i:memory) {
                if(i.second.ins!="")
                    cout<<i.first<<" "<<i.second.ins<<endl;
                else if(i.second.val!=0)
                    cout<<i.first<<" "<<i.second.val<<endl;
            }
        }
};

class Processor {
    public:
        uint8_t A,B,C,D,E,H,L;
        uint8_t SP,PC;
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
            cout<<"A: "<< hex << unsigned(A)<<endl;
            cout<<"B: "<< hex << unsigned(B)<<endl;
            cout<<"C: "<< hex << unsigned(C)<<endl;
            cout<<"D: "<< hex << unsigned(D)<<endl;
            cout<<"E: "<< hex << unsigned(E)<<endl;
            cout<<"H: "<< hex << unsigned(H)<<endl;
            cout<<"L: "<< hex << unsigned(L)<<endl;
            cout<<"SP: "<< hex << unsigned(PC)<<endl;
            cout<<"PC: "<< hex << unsigned(SP)<<endl;
            cout<<"Flags: ";
            for(int i=0;i<8;i++)
                cout<<flag[i]<<" ";
            cout<<endl;
        }
};

int main() {
    Processor p;
}