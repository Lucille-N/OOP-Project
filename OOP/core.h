#ifndef CORE_H
#define CORE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// === Employee class ===
class Employee {
private:
    string name;
    string contactNumber;
    int workDaysPerWeek;
    double hourlyWage;
    double overtimeWage;
    double totalHoursWorked;
    double overtimeHours;
    double advancePayment;

public:
    Employee();  // constructor

    void inputInfo();
    void computePay();
    void recordAdvance();
    void showSummary() const;
    string getName() const;

    bool saveToFile(ofstream &file) const;
    bool loadFromFile(ifstream &file);
};

// === EmployeeManager class ===
class EmployeeManager {
private:
    vector<Employee> employees;

public:
    void addEmployee();
    void recordAdvance();
    void computeEmployeePay();
    void viewEmployees() const;
    void loadFromFile(const string &filename);
    void saveToFile(const string &filename) const;
};

// === Menu class ===
class Menu {
private:
    EmployeeManager manager;

public:
    void showMenu() const;
    void handleChoice();
};

#endif
