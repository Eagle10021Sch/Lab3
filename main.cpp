#include "Student.h"
#include "Employee.h"
#include "SalariedEmployee.h"
#include "HourlyEmployee.h"
#include "CommissionEmployee.h"
#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <iomanip>

// Helper validator for non-negative float inputs (like salaries, hours, rate, sales, etc.)
float getValidatedFloat(const std::string& prompt, float min = 0.0f, float max = std::numeric_limits<float>::max()) {
    std::string input;
    float value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        if (!input.empty()) {
            try {
                size_t processedChars = 0;
                value = std::stof(input, &processedChars);
                if (processedChars == input.length() && value >= min && value <= max) {
                    return value;
                }
            } catch (...) {
                // Handled if parsing fails
            }
        }
        std::cout << "Invalid input. Please enter a valid float between " << min << " and " << max << ".\n";
    }
}

// Stage 1: Student System Helper Functions
void addStudents(std::unique_ptr<Student[]>& students, int& count) {
    int maxToAdd = MAX_STUDENTS - count;
    if (maxToAdd <= 0) {
        std::cout << "Maximum student count reached. Cannot add more students.\n";
        return;
    }
    
    int numToAdd = getValidatedInt("Enter number of students to add: ", 1, maxToAdd);
    
    // Allocate new array with space for existing + new records
    std::unique_ptr<Student[]> newArray = std::make_unique<Student[]>(count + numToAdd);
    
    // Copy existing records using the deep-copy assignment operator
    for (int i = 0; i < count; ++i) {
        newArray[i] = students[i];
    }
    
    // Prompt for new student records
    for (int i = 0; i < numToAdd; ++i) {
        std::cout << "\nStudent " << (count + i + 1) << "\n";
        int id;
        while (true) {
            id = getValidatedInt("ID: ", 1, std::numeric_limits<int>::max());
            
            // Check for duplicate student IDs
            bool duplicate = false;
            for (int j = 0; j < count + i; ++j) {
                if (newArray[j].getId() == id) {
                    duplicate = true;
                    break;
                }
            }
            if (duplicate) {
                std::cout << "Warning: Duplicate ID. Please enter a different ID.\n";
            } else {
                break;
            }
        }
        
        std::string name = getValidatedName("Name: ");
        
        float tempMarks[SUBJECT_COUNT];
        for (int j = 0; j < SUBJECT_COUNT; ++j) {
            tempMarks[j] = getValidatedMark("Mark for subject " + std::to_string(j + 1) + ": ");
        }
        
        // Construct and assign student object, triggering move assignment/construction
        newArray[count + i] = Student(id, name, tempMarks);
    }
    
    // Transfers ownership to global unique_ptr, automatically freeing old memory
    students = std::move(newArray);
    count += numToAdd;
    std::cout << "Successfully added records.\n";
}

void displayStudents(const std::unique_ptr<Student[]>& students, int count) {
    if (count == 0) {
        std::cout << "No students available\n";
        return;
    }
    std::cout << "\n===== Student Records =====\n";
    std::cout << std::left << std::setw(10) << "ID" 
              << std::setw(20) << "Name" 
              << std::setw(8) << "M1" 
              << std::setw(8) << "M2" 
              << std::setw(8) << "M3" 
              << std::setw(8) << "Total" 
              << std::setw(8) << "Avg" 
              << std::setw(8) << "Grade" 
              << "Status\n";
    std::cout << "--------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < count; ++i) {
        students[i].display();
    }
}

void findHighestScorer(const std::unique_ptr<Student[]>& students, int count) {
    if (count == 0) {
        std::cout << "Warning: No students available to find highest scorer.\n";
        return;
    }
    
    const Student* highest = &students[0];
    for (int i = 1; i < count; ++i) {
        // Uses friend function compareAverage to compare student averages
        if (compareAverage(students[i], *highest)) {
            highest = &students[i];
        }
    }
    
    std::cout << "\nHighest Scorer:\n";
    std::cout << "ID: " << highest->getId() << "\nName: " << highest->getName() << "\n";
    std::cout << "Marks: " << highest->getMark(0) << " " << highest->getMark(1) << " " << highest->getMark(2) << "\n";
    std::cout << "Total: " << highest->getTotal() << ", Average: " << std::fixed << std::setprecision(2) << highest->getAverage() << "\n";
    std::cout << "Grade: " << gradeToString(highest->getGrade()) << ", Status: " << statusToString(highest->getStatus()) << "\n";
}

void displayClassSummary(const std::unique_ptr<Student[]>& students, int count) {
    if (count == 0) {
        std::cout << "Safe Message: No students available for class summary.\n";
        return;
    }
    
    float classTotal = 0;
    int passed = 0;
    int failed = 0;
    float highestAvg = 0;
    
    for (int i = 0; i < count; ++i) {
        classTotal += students[i].getAverage();
        if (students[i].getStatus() == PASS) {
            passed++;
        } else {
            failed++;
        }
        if (students[i].getAverage() > highestAvg) {
            highestAvg = students[i].getAverage();
        }
    }
    
    float classAverage = classTotal / count;
    float passRate = (static_cast<float>(passed) / count) * 100.0f;
    
    std::cout << "\n===== Class Summary =====\n";
    std::cout << "Total Students : " << count << "\n";
    std::cout << "Class Average  : " << std::fixed << std::setprecision(2) << classAverage << "\n";
    std::cout << "Passed         : " << passed << "\n";
    std::cout << "Failed         : " << failed << "\n";
    std::cout << "Highest Avg    : " << highestAvg << "\n";
    std::cout << "Pass Rate      : " << passRate << "%\n";
}

// Stage 2: Employee System Helper Functions
void addEmployee(std::vector<std::unique_ptr<Employee>>& employees) {
    std::cout << "\nChoose Employee Type:\n";
    std::cout << "1. Salaried Employee\n";
    std::cout << "2. Hourly Employee\n";
    std::cout << "3. Commission Employee\n";
    int type = getValidatedInt("Enter choice: ", 1, 3);
    
    std::string name = getValidatedName("Enter name: ");
    float baseSalary = getValidatedFloat("Enter base salary: ");
    
    if (type == 1) {
        float bonus = getValidatedFloat("Enter bonus: ");
        employees.push_back(std::make_unique<SalariedEmployee>(name, baseSalary, bonus));
    } else if (type == 2) {
        float hours = getValidatedFloat("Enter hours worked: ", 0.0f, 168.0f);
        float rate = getValidatedFloat("Enter hourly rate: ");
        employees.push_back(std::make_unique<HourlyEmployee>(name, baseSalary, hours, rate));
    } else {
        float sales = getValidatedFloat("Enter gross sales volume: ");
        float rate = getValidatedFloat("Enter commission rate (0-100%): ", 0.0f, 100.0f);
        employees.push_back(std::make_unique<CommissionEmployee>(name, baseSalary, sales, rate / 100.0f));
    }
    std::cout << "Employee record added successfully.\n";
}

void displayEmployees(const std::vector<std::unique_ptr<Employee>>& employees) {
    if (employees.empty()) {
        std::cout << "No employees available\n";
        return;
    }
    std::cout << "\n===== Employee Records =====\n";
    std::cout << std::left << std::setw(15) << "Name" 
              << std::setw(12) << "Base Salary" 
              << std::setw(12) << "Type" 
              << std::setw(25) << "Role-Specific Details" 
              << "Total Pay\n";
    std::cout << "------------------------------------------------------------------------------------\n";
    for (const auto& emp : employees) {
        emp->displayInfo(); // Polymorphic function call
    }
}

void findHighestPaidEmployee(const std::vector<std::unique_ptr<Employee>>& employees) {
    if (employees.empty()) {
        std::cout << "Warning: No employees available to find highest-paid.\n";
        return;
    }
    
    const Employee* highest = employees[0].get();
    for (size_t i = 1; i < employees.size(); ++i) {
        // Uses friend function comparePay to compare employee pay polymorphically
        if (comparePay(*employees[i], *highest)) {
            highest = employees[i].get();
        }
    }
    
    std::cout << "\nHighest-Paid Employee:\n";
    std::cout << "Name        : " << highest->getName() << "\n";
    std::cout << "Base Salary : $" << std::fixed << std::setprecision(2) << highest->getBaseSalary() << "\n";
    std::cout << "Total Pay   : $" << std::fixed << std::setprecision(2) << highest->calculatePay() << "\n";
}

int main() {
    std::unique_ptr<Student[]> students(nullptr);
    int studentCount = 0;
    
    // Stage 1 Menu Loop
    while (true) {
        std::cout << "\n===== Stage 1: Student Management System =====\n";
        std::cout << "1. Add student records\n";
        std::cout << "2. Display all students\n";
        std::cout << "3. Find highest scoring student\n";
        std::cout << "4. Display class summary\n";
        std::cout << "5. Proceed to Stage 2\n";
        
        int choice = getValidatedInt("Enter choice: ", 1, 5);
        if (choice == 5) {
            std::cout << "Transitioning to Stage 2 (Employee Inheritance System)...\n";
            break;
        }
        
        switch (choice) {
            case 1:
                addStudents(students, studentCount);
                break;
            case 2:
                displayStudents(students, studentCount);
                break;
            case 3:
                findHighestScorer(students, studentCount);
                break;
            case 4:
                displayClassSummary(students, studentCount);
                break;
            default:
                break;
        }
    }
    
    // Clean up student system memory
    students.reset();
    
    std::vector<std::unique_ptr<Employee>> employees;
    
    // Stage 2 Menu Loop
    while (true) {
        std::cout << "\n===== Stage 2: Employee Inheritance System =====\n";
        std::cout << "1. Add employee\n";
        std::cout << "2. Display all employees\n";
        std::cout << "3. Find highest-paid employee\n";
        std::cout << "4. Exit\n";
        
        int choice = getValidatedInt("Enter choice: ", 1, 4);
        if (choice == 4) {
            std::cout << "Exiting program. Goodbye!\n";
            break;
        }
        
        switch (choice) {
            case 1:
                addEmployee(employees);
                break;
            case 2:
                displayEmployees(employees);
                break;
            case 3:
                findHighestPaidEmployee(employees);
                break;
            default:
                break;
        }
    }
    
    return 0;
}
