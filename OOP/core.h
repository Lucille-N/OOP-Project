#ifndef CORE_H
#define CORE_H
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

const int MAX_EMPLOYEES = 20;

class Employee {
private:
    string firstName;
    string lastName;
    string middleName;
    string contactNumber;
    double hourlyWage;
    double overtimeWage;
    double expectedHoursPerDay;
    double advancePayment;

public:
    Employee();

    void inputInfo();
    void recordAdvance();
    void computePay();
    void showSummary() const;
    string getFullName() const;
    string getContactNumber() const;

    bool saveToFile(ofstream &file) const;
    bool loadFromFile(ifstream &file);
};

class EmployeeManager {
private:
    Employee empList[MAX_EMPLOYEES];
    int empCount;

public:
    EmployeeManager();
    void addEmployee();
    void recordAdvancePayment();
    void computeEmployeePay();
    void viewEmployees() const;
    void saveData() const;
    void loadData();
};

class Menu {
private:
    EmployeeManager manager;

public:
    void displayProgramInfo() const;
    void displayMainMenu() const;
    void handleUserChoice();
    void run();
};

#endif
