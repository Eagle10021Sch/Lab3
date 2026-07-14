#include "HourlyEmployee.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// Constructor passes name and baseSalary to Employee base class
HourlyEmployee::HourlyEmployee(const std::string& name, float baseSalary, float hoursWorked, float hourlyRate)
    : Employee(name, baseSalary), hoursWorked(hoursWorked), hourlyRate(hourlyRate) {}

// Calculate pay: base salary + (hours worked * hourly rate)
float HourlyEmployee::calculatePay() const {
    return getBaseSalary() + (hoursWorked * hourlyRate);
}

// Display hourly employee info
void HourlyEmployee::displayInfo() const {
    Employee::displayInfo(); // Displays name and base salary
    
    std::stringstream ss;
    ss << "Hrs: " << std::fixed << std::setprecision(1) << hoursWorked 
       << " @ $" << std::fixed << std::setprecision(2) << hourlyRate;
    
    std::cout << std::left << std::setw(12) << "Hourly"
              << std::setw(25) << ss.str()
              << "$" << std::fixed << std::setprecision(2) << calculatePay() << "\n";
}
