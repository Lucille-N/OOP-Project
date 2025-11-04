
#include "core.h"
#include <cctype>

// ===== Employee =====
Employee::Employee() {
    firstName = lastName = middleName = "";
    contactNumber = "";
    hourlyWage = 0;
    overtimeWage = 0;
    expectedHoursPerDay = 0;
    advancePayment = 0;
}

void Employee::inputInfo() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n=== Add Employee ===\n";
    cout << "Enter 0 anytime to return to main menu.\n";

    string input;
    cout << "Last Name: ";
    getline(cin, input);
    lastName = input;

    cout << "First Name: ";
    getline(cin, input);
    if (input == "0") return;
    firstName = input;

    cout << "Middle Name: ";
    getline(cin, input);
    if (input == "0") return;
    middleName = input;

    // Contact Number validation
    while (true) {
        cout << "Contact Number (11 digits, starts with 09): ";
        getline(cin, contactNumber);
        if (contactNumber == "0") return;
        if (contactNumber.length() == 11 && contactNumber.substr(0, 2) == "09") {
            bool allDigits = true;
            for (char c : contactNumber)
                if (!isdigit(c)) { allDigits = false; break; }
            if (allDigits) break;
        }
        cout << "Invalid contact. Must be 11 digits and start with 09.\n";
    }

    // Hourly Wage
    while (true) {
        cout << "Hourly Wage (0 to cancel): ";
        if (!(cin >> hourlyWage)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }
        if (hourlyWage == 0) return;
        if (hourlyWage > 0) break;
        cout << "Invalid input.\n";
    }

    // Overtime Wage
    while (true) {
        cout << "Overtime Wage per Hour (0 to cancel): ";
        if (!(cin >> overtimeWage)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input.\n";
            continue;
        }
        if (overtimeWage == 0) return;
        if (overtimeWage > 0) break;
        cout << "\nInvalid input.\n";
    }

    // Expected Hours per Day
    while (true) {
        cout << "Expected Hours per Day (0 to cancel): ";
        if (!(cin >> expectedHoursPerDay)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input.\n";
            continue;
        }
        if (expectedHoursPerDay == 0) return;
        if (expectedHoursPerDay > 0) break;
        cout << "\nInvalid input.\n";
    }

    advancePayment = 0;
}

void Employee::recordAdvance() {
    cout << "\n=== Record Advance Payment ===\n";
    cout << "Enter 0 to return to main menu.\n";
    while (true) {
        cout << "\nEnter amount: ";
        if (!(cin >> advancePayment)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input.\n";
            continue;
        }
        if (advancePayment == 0) {
            cout << "\nReturning to main menu.\n";
            return;
        }
        if (advancePayment > 0) break;
        cout << "\nInvalid input.\n";
    }
    cout << "\nAdvance payment recorded: " << advancePayment << endl;
}

void Employee::computePay() {
    cout << "\n=== Compute Pay ===\n";
    cout << "\nEnter 0 to return to main menu.\n";

    double actualHours;
    while (true) {
        cout << "\nEnter actual hours worked today: ";
        if (!(cin >> actualHours)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input.\n";
            continue;
        }
        if (actualHours == 0) {
            cout << "\nReturning to main menu.\n";
            return;
        }
        if (actualHours > 0) break;
        cout << "\nInvalid input.\n";
    }

    double overtimeHours = 0;
    double undertimeHours = 0;
    if (actualHours > expectedHoursPerDay)
        overtimeHours = actualHours - expectedHoursPerDay;
    else if (actualHours < expectedHoursPerDay)
        undertimeHours = expectedHoursPerDay - actualHours;

    double regularPay = hourlyWage * actualHours;
    double overtimePay = overtimeWage * overtimeHours;
    double undertimeDeduction = hourlyWage * undertimeHours;
    double totalPay = regularPay + overtimePay - undertimeDeduction - advancePayment;

    cout << "\n--- Pay Summary ---\n";
    cout << "Regular Pay: " << regularPay << endl;
    cout << "Overtime Pay: " << overtimePay << endl;
    cout << "Undertime Deduction: " << undertimeDeduction << endl;
    cout << "Advance Deduction: " << advancePayment << endl;
    cout << "Total Daily Pay: " << totalPay << endl;
}

void Employee::showSummary() const {
    cout << "\n=== Employee Info ===\n";
    cout << "Full Name: " << lastName << ", " << firstName << " " << middleName << endl;
    cout << "Contact: " << contactNumber << endl;
    cout << "Hourly Wage: " << hourlyWage << endl;
    cout << "Overtime Wage: " << overtimeWage << endl;
    cout << "Expected Hours per Day: " << expectedHoursPerDay << endl;
    cout << "Advance Payment: " << advancePayment << endl;
}

string Employee::getFullName() const {
    return lastName + "," + firstName + "," + middleName;
}
string Employee::getContactNumber() const { return contactNumber; }

bool Employee::saveToFile(ofstream &file) const {
    if (!file) return false;
    file << lastName << endl << firstName << endl << middleName << endl
         << contactNumber << endl
         << hourlyWage << endl << overtimeWage << endl
         << expectedHoursPerDay << endl << advancePayment << endl;
    return true;
}

bool Employee::loadFromFile(ifstream &file) {
    if (!getline(file, lastName)) return false;
    if (!getline(file, firstName)) return false;
    if (!getline(file, middleName)) return false;
    if (!getline(file, contactNumber)) return false;
    if (!(file >> hourlyWage)) return false;
    if (!(file >> overtimeWage)) return false;
    if (!(file >> expectedHoursPerDay)) return false;
    if (!(file >> advancePayment)) return false;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

// ===== EmployeeManager =====
EmployeeManager::EmployeeManager() { empCount = 0; }

void EmployeeManager::addEmployee() {
    if (empCount >= MAX_EMPLOYEES) { cout << "\nMaximum employees reached.\n"; return; }

    Employee temp;
    temp.inputInfo();
    if (temp.getFullName().empty()) {
        cout << "\nReturning to main menu...\n";
        return;
    }
    for (int i = 0; i < empCount; i++) {   
        if (empList[i].getFullName() == temp.getFullName() &&
            empList[i].getContactNumber() == temp.getContactNumber()) {
            cout << "\nError: Employee already exists.\n";
            return;
        }
    }

    empList[empCount++] = temp;
    cout << "\nEmployee added successfully!\n";
}

void EmployeeManager::recordAdvancePayment() {
    if (empCount == 0) { cout << "\nNo employees available.\n"; return; }
    cout << "\nSelect employee (0 to return):\n";
    for (int i = 0; i < empCount; i++) cout << i + 1 << ". " << empList[i].getFullName() << endl;

    int choice;
    if (!(cin >> choice) || choice == 0) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "\nReturning to main menu...\n";
        return;
    }
    if (choice > 0 && choice <= empCount) empList[choice - 1].recordAdvance();
    else cout << "\nInvalid selection.\n";
}

void EmployeeManager::computeEmployeePay() {
    if (empCount == 0) { cout << "\nNo employees available.\n"; return; }
    cout << "\nSelect employee (0 to return):\n";
    for (int i = 0; i < empCount; i++) cout << i + 1 << ". " << empList[i].getFullName() << endl;

    int choice;
    if (!(cin >> choice) || choice == 0) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "\nReturning to main menu...\n";
        return;
    }
    if (choice > 0 && choice <= empCount) empList[choice - 1].computePay();
    else cout << "\nInvalid selection.\n";
}
void EmployeeManager::viewEmployees() const {
    if (empCount == 0) { cout << "No employees available.\n"; return; }
    cout << "\nEnter 0 anytime to return.\n";
    for (int i = 0; i < empCount; i++) empList[i].showSummary();
}

void EmployeeManager::saveData() const {
    ofstream file("data.txt");
    for (int i = 0; i < empCount; i++) empList[i].saveToFile(file);
}

void EmployeeManager::loadData() {
    ifstream file("data.txt");
    if (!file.is_open()) return;
    while (empCount < MAX_EMPLOYEES && empList[empCount].loadFromFile(file)) empCount++;
}

// ===== Menu =====
void Menu::displayProgramInfo() const {
    cout << "============================================\n";
    cout << "          Payroll Management System         \n";
    cout << "============================================\n";
}

void Menu::displayMainMenu() const {
    cout << "\n==============================\n";
    cout << "\n1. Add Employee\n2. Record Advance Payment\n3. Compute Daily Pay\n4. View Employee Info\n5. Save & Exit\n";
}

void Menu::handleUserChoice() {
    int choice;
    do {
        displayMainMenu();
        cout << "\nEnter choice: ";
        if (!(cin >> choice)) {
            cout << "\nInvalid input.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        switch (choice) {
            case 1: manager.addEmployee(); break;
            case 2: manager.recordAdvancePayment(); break;
            case 3: manager.computeEmployeePay(); break;
            case 4: manager.viewEmployees(); break;
            case 5: manager.saveData(); cout << "\nData saved. Exiting.\n"; break;
            default: cout << "\nInvalid choice.\n";
        }
    } while (choice != 5);
}

void Menu::run() {
    displayProgramInfo();
    manager.loadData();
    handleUserChoice();
}

// ===== main =====
int main() {
    Menu menu;
    menu.run();
    return 0;
}
