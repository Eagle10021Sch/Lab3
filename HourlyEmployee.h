#ifndef HOURLY_EMPLOYEE_H
#define HOURLY_EMPLOYEE_H

#include "Employee.h"

class HourlyEmployee : public Employee {
private:
    float hoursWorked; // Role-specific field: hours worked
    float hourlyRate;  // Role-specific field: hourly pay rate

public:
    // Constructor
    HourlyEmployee(const std::string& name, float baseSalary, float hoursWorked, float hourlyRate);

    // Override calculatePay: base salary + (hours worked * hourly rate)
    float calculatePay() const override;

    // Override displayInfo: displays common information plus hourly-specific info
    void displayInfo() const override;

    // Getters
    float getHoursWorked() const { return hoursWorked; }
    float getHourlyRate() const { return hourlyRate; }
};

#endif // HOURLY_EMPLOYEE_H
