#ifndef COMMISSION_EMPLOYEE_H
#define COMMISSION_EMPLOYEE_H

#include "Employee.h"

class CommissionEmployee : public Employee {
private:
    float sales;          // Role-specific field: gross sales volume
    float commissionRate; // Role-specific field: commission rate (e.g. 0.05 for 5%)

public:
    // Constructor
    CommissionEmployee(const std::string& name, float baseSalary, float sales, float commissionRate);

    // Override calculatePay: base salary + (sales * commission rate)
    float calculatePay() const override;

    // Override displayInfo: displays common information plus commission-specific info
    void displayInfo() const override;

    // Getters
    float getSales() const { return sales; }
    float getCommissionRate() const { return commissionRate; }
};

#endif // COMMISSION_EMPLOYEE_H
