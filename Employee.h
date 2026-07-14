#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

// Abstract Base Class representing an Employee
class Employee {
private:
    std::string name;      // Encapsulated employee name
    float baseSalary;      // Encapsulated base salary component

public:
    // Constructor
    Employee(const std::string& name, float baseSalary);

    // Virtual destructor
    // Crucial for an abstract base class to ensure that the derived class's 
    // destructor is called first when deleting through a base pointer, preventing resource leaks.
    virtual ~Employee();

    // Pure virtual function
    // Forces derived classes to provide their own logic to calculate pay.
    virtual float calculatePay() const = 0;

    // Virtual displayInfo function
    // Renders common fields and can be overridden by subclasses to add specific fields.
    virtual void displayInfo() const;

    // Encapsulated Getters
    std::string getName() const { return name; }
    float getBaseSalary() const { return baseSalary; }

    // Friend function to compare employee pays polymorphically
    // Direct access allows comparing employee pays via calculatePay() polymorphically.
    friend bool comparePay(const Employee& lhs, const Employee& rhs);
};

#endif // EMPLOYEE_H
