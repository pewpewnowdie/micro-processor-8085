#include <iostream>
#include <string>
#include "lib/Instruction.h"

void banner() {
    cout << R"(        
    ___  ____                                                               _____ _____ _____  _____ 
    |  \/  (_)                                                             |  _  |  _  |  _  ||  ___|
    | .  . |_  ___ _ __ ___  _ __  _ __ ___   ___ ___  ___ ___  ___  _ __   \ V /| |/' |\ V / |___  | 
    | |\/| | |/ __| '__/ _ \| '_ \| '__/ _ \ / __/ _ \/ __/ __|/ _ \| '__|  / _ \|  /| |/ _ \     \ \
    | |  | | | (__| | | (_) | |_) | | | (_) | (_|  __/\__ \__ \ (_) | |    | |_| \ |_/ / |_| |/\__/ /
    \_|  |_/_|\___|_|  \___/| .__/|_|  \___/ \___\___||___/___/\___/|_|    \_____/\___/\_____/\____/ 
                            | |                                                                      
                            |_|                                                                      
    )" << endl;
}

void displayMenu() {
    cout << "+-----------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                    Menu:                                                      |" << endl;
    cout << "|                                    1. Write                                                   |" << endl;
    cout << "|                                    2. Execute                                                 |" << endl;
    cout << "|                                    3. Display Memory                                          |" << endl;
    cout << "|                                    4. Display Registers                                       |" << endl;
    cout << "|                                    5. Exit                                                    |" << endl;
    cout << "+-----------------------------------------------------------------------------------------------+" << endl;
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
    banner();
    while(true) {
        displayMenu();
        int choice = getUserChoice();
        processChoice(choice);
    }
    return 0;
}