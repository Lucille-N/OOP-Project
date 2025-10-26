#include "core.h"

// ===== Employee methods =====
Employee::Employee() {
    name = "";
    contactNumber = "";
    workDaysPerWeek = 0;
    hourlyWage = 0;
    overtimeWage = 0;
    totalHoursWorked = 0;
    overtimeHours = 0;
    advancePayment = 0;
}

void Employee::inputInfo() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n=== Add Employee ===\n";
    cout << "Employee Name: ";
    getline(cin, name);
    cout << "Contact Number: ";
    getline(cin, contactNumber);

    while (true) {
        cout << "Number of Workdays per Week: ";
        if (cin >> workDaysPerWeek && workDaysPerWeek > 0) break;
        cout << "Invalid input. Must be a positive integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true) {
        cout << "Hourly Wage: ";
        if (cin >> hourlyWage && hourlyWage >= 0) break;
        cout << "Invalid input. Must be a non-negative number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true) {
        cout << "Overtime Wage (per hour): ";
        if (cin >> overtimeWage && overtimeWage >= 0) break;
        cout << "Invalid input. Must be a non-negative number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    advancePayment = 0;
    totalHoursWorked = 0;
    overtimeHours = 0;

    cout << "\nEmployee added successfully!\n";
}

void Employee::recordAdvance() {
    while (true) {
        cout << "\n=== Record Advance Payment ===\n";
        cout << "Enter amount granted: ";
        if (cin >> advancePayment && advancePayment >= 0) break;
        cout << "Invalid input. Must be non-negative.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Advance payment recorded: " << advancePayment << endl;
}

void Employee::computePay() {
    while (true) {
        cout << "\n=== Compute Weekly Pay ===\n";
        cout << "Enter total hours worked in the entire week: ";
        if (cin >> totalHoursWorked && totalHoursWorked >= 0) break;
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true) {
        cout << "Enter overtime hours worked: ";
        if (cin >> overtimeHours && overtimeHours >= 0) break;
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    double regularPay = hourlyWage * totalHoursWorked;
    double overtimePay = overtimeWage * overtimeHours;
    double totalPay = regularPay + overtimePay - advancePayment;

    cout << "\n--- Pay Summary ---\n";
    cout << "Regular Pay: " << regularPay << endl;
    cout << "Overtime Pay: " << overtimePay << endl;
    cout << "Advance Deduction: " << advancePayment << endl;
    cout << "Total Weekly Pay: " << totalPay << endl;
}

void Employee::showSummary() const {
    cout << "\n=== Employee Info ===\n";
    cout << "Name: " << name << endl;
    cout << "Contact: " << contactNumber << endl;
    cout << "Workdays per Week: " << workDaysPerWeek << endl;
    cout << "Hourly Wage: " << hourlyWage << endl;
    cout << "Overtime Wage: " << overtimeWage << endl;
    cout << "Advance Payment: " << advancePayment << endl;
}

string Employee::getName() const {
    return name;
}

bool Employee::saveToFile(ofstream &file) const {
    if (!file) return false;
    file << name << endl
         << contactNumber << endl
         << workDaysPerWeek << endl
         << hourlyWage << endl
         << overtimeWage << endl
         << advancePayment << endl;
    return true;
}

bool Employee::loadFromFile(ifstream &file) {
    if (!getline(file, name)) return false;
    if (!getline(file, contactNumber)) return false;
    if (!(file >> workDaysPerWeek)) return false;
    if (!(file >> hourlyWage)) return false;
    if (!(file >> overtimeWage)) return false;
    if (!(file >> advancePayment)) return false;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

// ===== EmployeeManager methods =====
void EmployeeManager::addEmployee() {
    Employee emp;
    emp.inputInfo();
    employees.push_back(emp);
}

void EmployeeManager::recordAdvance() {
    if (employees.empty()) {
        cout << "No employees available.\n";
        return;
    }
    cout << "\nSelect employee for advance payment:\n";
    for (size_t i = 0; i < employees.size(); i++)
        cout << i + 1 << ". " << employees[i].getName() << endl;

    int choice;
    cin >> choice;
    if (choice > 0 && choice <= employees.size())
        employees[choice - 1].recordAdvance();
    else
        cout << "Invalid selection.\n";
}

void EmployeeManager::computeEmployeePay() {
    if (employees.empty()) {
        cout << "No employees available.\n";
        return;
    }
    cout << "\nSelect employee to compute pay:\n";
    for (size_t i = 0; i < employees.size(); i++)
        cout << i + 1 << ". " << employees[i].getName() << endl;

    int choice;
    cin >> choice;
    if (choice > 0 && choice <= employees.size())
        employees[choice - 1].computePay();
    else
        cout << "Invalid selection.\n";
}

void EmployeeManager::viewEmployees() const {
    if (employees.empty()) {
        cout << "No employees available.\n";
        return;
    }
    for (const auto &emp : employees)
        emp.showSummary();
}

void EmployeeManager::loadFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) return;

    Employee emp;
    while (emp.loadFromFile(file))
        employees.push_back(emp);

    file.close();
}

void EmployeeManager::saveToFile(const string &filename) const {
    ofstream file(filename);
    for (const auto &emp : employees)
        emp.saveToFile(file);
    file.close();
}

// ===== Menu methods =====
void Menu::showMenu() const {
    cout << "\n==============================\n";
    cout << " Employee Payroll System\n";
    cout << "==============================\n";
    cout << "1. Add Employee\n";
    cout << "2. Record Advance Payment\n";
    cout << "3. Compute Weekly Pay\n";
    cout << "4. View Employee Info\n";
    cout << "5. Save & Exit\n";
}

void Menu::handleChoice() {
    manager.loadFromFile("data.txt");

    int choice;
    do {
        showMenu();
        cout << "Enter choice: ";
        if (cin >> choice) {
            switch (choice) {
                case 1: manager.addEmployee(); break;
                case 2: manager.recordAdvance(); break;
                case 3: manager.computeEmployeePay(); break;
                case 4: manager.viewEmployees(); break;
                case 5: 
                    manager.saveToFile("data.txt");
                    cout << "Data saved. Exiting program.\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } else {
            cout << "Invalid input.\n";
            cin.clear();
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (choice != 5);
}

// ===== main =====
int main() {
    Menu menu;
    menu.handleChoice();
    return 0;
}
