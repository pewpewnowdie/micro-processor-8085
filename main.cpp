#include <iostream>
#include <string>
#include "lib/Instruction.h"

void displayMenu() {
    cout << "Menu:\n";
    cout << "1. Write\n";
    cout << "2. Execute\n";
    cout << "3. Display Memory\n";
    cout << "4. Display Registers\n";
    cout << "5. Exit\n";
}

int getUserChoice() {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void processChoice(int choice) {
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
            cout << "Exiting...\n";
            exit(0);
        default:
            cout << "Invalid choice\n";
    }
}

int main() {
    while(true) {
        displayMenu();
        int choice = getUserChoice();
        processChoice(choice);
    }
    return 0;
}