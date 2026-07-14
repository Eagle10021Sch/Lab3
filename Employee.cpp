#include "Employee.h"
#include <iostream>
#include <iomanip>

// Constructor to initialize name and base salary
Employee::Employee(const std::string& name, float baseSalary)
    : name(name), baseSalary(baseSalary) {}

// Virtual destructor implementation
Employee::~Employee() {}

// Base displayInfo implementation
// Prints the name and base salary. Designed to be called by derived class displayInfo overrides.
void Employee::displayInfo() const {
    std::cout << std::left << std::setw(15) << name
              << std::fixed << std::setprecision(2)
              << std::setw(12) << baseSalary;
}

// Friend function to compare employee pays polymorphically
// Calls calculatePay() which resolves dynamically at runtime to the correct derived implementation.
bool comparePay(const Employee& lhs, const Employee& rhs) {
    return lhs.calculatePay() > rhs.calculatePay();
}
