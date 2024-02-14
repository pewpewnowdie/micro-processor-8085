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
    uint8_t A,B,C,D,E,H,L;
    uint8_t SP,PC;
    bool flag[8];
    public:
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
        void setA(uint8_t a) {A=a;}
        void setB(uint8_t b) {B=b;}
        void setC(uint8_t c) {C=c;}
        void setD(uint8_t d) {D=d;}
        void setE(uint8_t e) {E=e;}
        void setH(uint8_t h) {H=h;}
        void setL(uint8_t l) {L=l;}
        void setSP(uint8_t sp) {SP=sp;}
        void setPC(uint8_t pc) {PC=pc;}
        void setFlag(int f) {flag[f]=true;}
        void resetFlag(int f) {flag[f]=false;}
        uint8_t getA() {return A;}
        uint8_t getB() {return B;}
        uint8_t getC() {return C;}
        uint8_t getD() {return D;}
        uint8_t getE() {return E;}
        uint8_t getH() {return H;}
        uint8_t getL() {return L;}
        uint8_t getSP() {return SP;}
        uint8_t getPC() {return PC;}
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