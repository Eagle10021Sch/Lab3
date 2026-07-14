#include "CommissionEmployee.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// Constructor passes name and baseSalary to Employee base class
CommissionEmployee::CommissionEmployee(const std::string& name, float baseSalary, float sales, float commissionRate)
    : Employee(name, baseSalary), sales(sales), commissionRate(commissionRate) {}

// Calculate pay: base salary + (sales * commission rate)
float CommissionEmployee::calculatePay() const {
    return getBaseSalary() + (sales * commissionRate);
}

// Display commission employee info
void CommissionEmployee::displayInfo() const {
    Employee::displayInfo(); // Displays name and base salary
    
    std::stringstream ss;
    ss << "Sales: $" << std::fixed << std::setprecision(2) << sales 
       << " @ " << std::fixed << std::setprecision(1) << (commissionRate * 100.0f) << "%";
    
    std::cout << std::left << std::setw(12) << "Commission"
              << std::setw(25) << ss.str()
              << "$" << std::fixed << std::setprecision(2) << calculatePay() << "\n";
}
