#include "Core.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    Payroll payroll;
    int choice;

    do {
        cout << "\n1. Add Employee\n2. Display Payroll\n3. Exit\nChoose: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            double salary;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter salary: ";
            cin >> salary;
            payroll.addEmployee(name, salary);
        }
        else if (choice == 2) {
            payroll.displayAll();
        }

    } while (choice != 3);

    /*  Line 29-39 is for txt integration, this is only for testing but shall be modified for the payroll system
    fstream myFile;
    myFile.open("data.txt", ios::out | ios::in | ios::app);
    if (myFile.is_open()) {
        myFile << "File opened successfully!" << endl;
        myFile.close();
    } else {
        cerr << "Error opening file!" << endl;
        return 1;
        myFile.close();
    }
    */

    cout << "Exiting program.\n";
    return 0;
}

