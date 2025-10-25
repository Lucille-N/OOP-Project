#include "Core.h"

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

    cout << "Exiting program.\n";
    return 0;
}

