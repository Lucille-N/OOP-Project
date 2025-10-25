#include <iostream>
using namespace std;

class Person (
public:
  String name;
  double salary;

  Person() {
    name = "";
    salary = 0;
  }

  void setData(string n, double s) {
      name = n;
      salary = s;
  }

  void display() {
      cout << "Name: " << name << ", Salary: " << salary << endl;
  }

};

class Payroll {
public:
  Person employees[10];
  int count;

  Payroll() {
    count = 0;
  }

  void addEmployee(string name, double salary) {
      if (count < 10) {
          employees[count].setData(name,salary);
          count++;
      } else {
          cout << "Payroll full!" << endl;
      }
  }

}

  void displayAll() {
      for (int i = 0; i < count; i++)
          employees[i].display();
}

};
