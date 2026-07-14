#include "SalariedEmployee.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// Constructor passes name and baseSalary to Employee base class
SalariedEmployee::SalariedEmployee(const std::string& name, float baseSalary, float bonus)
    : Employee(name, baseSalary), bonus(bonus) {}

// Calculate pay for salaried employee: base salary + bonus
float SalariedEmployee::calculatePay() const {
    return getBaseSalary() + bonus;
}

// Display salaried employee info
void SalariedEmployee::displayInfo() const {
    Employee::displayInfo(); // Displays name and base salary
    
    std::stringstream ss;
    ss << "Bonus: $" << std::fixed << std::setprecision(2) << bonus;
    
    std::cout << std::left << std::setw(12) << "Salaried"
              << std::setw(25) << ss.str()
              << "$" << std::fixed << std::setprecision(2) << calculatePay() << "\n";
}
