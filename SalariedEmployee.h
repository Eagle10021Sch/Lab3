#ifndef SALARIED_EMPLOYEE_H
#define SALARIED_EMPLOYEE_H

#include "Employee.h"

class SalariedEmployee : public Employee {
private:
    float bonus; // Role-specific field: fixed bonus amount

public:
    // Constructor
    SalariedEmployee(const std::string& name, float baseSalary, float bonus);

    // Override calculatePay: base salary + bonus
    float calculatePay() const override;

    // Override displayInfo: displays common information plus salaried-specific info
    void displayInfo() const override;

    // Getter for bonus
    float getBonus() const { return bonus; }
};

#endif // SALARIED_EMPLOYEE_H
