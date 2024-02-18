#include <iostream>
#include <string>
#include "lib/Instruction.h"

int main() {
    while(true) {
        cout << "Menu:\n1. Write\n2. Execute\n3. Display Memory\n4. Display Registers\n5. Exit\n";
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1:
                write();
                break;
            case 2:
                execute();
                break;
            case 3:
                processor.memory.display();
                break;
            case 4:
                processor.showReg();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
    return 0;
}