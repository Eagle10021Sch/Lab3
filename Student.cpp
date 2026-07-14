#include "Student.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

// Default constructor - delegates to initializer-list constructor
Student::Student() : Student(0, "Unnamed", {0.0f, 0.0f, 0.0f}) {}

// Delegating constructor
Student::Student(int id, const std::string& name) : Student(id, name, {0.0f, 0.0f, 0.0f}) {}

// Parameterized constructor using raw array
Student::Student(int id, const std::string& name, const float* marksArray)
    : id(id), name(name), marks(std::make_unique<float[]>(SUBJECT_COUNT)),
      total(0.0f), average(0.0f), status(FAIL), grade(Grade::F) {
    if (marksArray) {
        for (int i = 0; i < SUBJECT_COUNT; ++i) {
            this->marks[i] = marksArray[i];
        }
    } else {
        for (int i = 0; i < SUBJECT_COUNT; ++i) {
            this->marks[i] = 0.0f;
        }
    }
    recalculate();
}

// Initializer-list constructor
Student::Student(int id, const std::string& name, std::initializer_list<float> marksList)
    : id(id), name(name), marks(std::make_unique<float[]>(SUBJECT_COUNT)),
      total(0.0f), average(0.0f), status(FAIL), grade(Grade::F) {
    int i = 0;
    for (float mark : marksList) {
        if (i < SUBJECT_COUNT) {
            this->marks[i] = mark;
            i++;
        }
    }
    // Pad remaining subjects with 0.0f if list is too short
    for (; i < SUBJECT_COUNT; ++i) {
        this->marks[i] = 0.0f;
    }
    recalculate();
}

// Copy constructor (deep copy)
Student::Student(const Student& other)
    : id(other.id), name(other.name), marks(std::make_unique<float[]>(SUBJECT_COUNT)),
      total(other.total), average(other.average), status(other.status), grade(other.grade) {
    if (other.marks) {
        for (int i = 0; i < SUBJECT_COUNT; ++i) {
            this->marks[i] = other.marks[i];
        }
    }
}

// Move constructor
Student::Student(Student&& other) noexcept
    : id(other.id), name(std::move(other.name)), marks(std::move(other.marks)),
      total(other.total), average(other.average), status(other.status), grade(other.grade) {
    other.id = 0;
    other.total = 0.0f;
    other.average = 0.0f;
    other.status = FAIL;
    other.grade = Grade::F;
}

// Copy assignment operator (deep copy)
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        total = other.total;
        average = other.average;
        status = other.status;
        grade = other.grade;
        
        if (!marks) {
            marks = std::make_unique<float[]>(SUBJECT_COUNT);
        }
        
        if (other.marks) {
            for (int i = 0; i < SUBJECT_COUNT; ++i) {
                marks[i] = other.marks[i];
            }
        } else {
            for (int i = 0; i < SUBJECT_COUNT; ++i) {
                marks[i] = 0.0f;
            }
        }
    }
    return *this;
}

// Move assignment operator
Student& Student::operator=(Student&& other) noexcept {
    if (this != &other) {
        id = other.id;
        name = std::move(other.name);
        marks = std::move(other.marks);
        total = other.total;
        average = other.average;
        status = other.status;
        grade = other.grade;

        other.id = 0;
        other.total = 0.0f;
        other.average = 0.0f;
        other.status = FAIL;
        other.grade = Grade::F;
    }
    return *this;
}

// Destructor
Student::~Student() {}

// Recursive function to calculate total mark
float Student::calculateTotalRecursive(int index) const {
    if (index >= SUBJECT_COUNT) {
        return 0.0f;
    }
    return (marks ? marks[index] : 0.0f) + calculateTotalRecursive(index + 1);
}

// Recalculates averages, grades, and status
void Student::recalculate() {
    total = calculateTotalRecursive(0);
    average = total / static_cast<float>(SUBJECT_COUNT);
    status = (average >= PASS_THRESHOLD) ? PASS : FAIL;
    
    if (average >= 80.0f) grade = Grade::A;
    else if (average >= 70.0f) grade = Grade::B;
    else if (average >= 60.0f) grade = Grade::C;
    else if (average >= 50.0f) grade = Grade::D;
    else grade = Grade::F;
}

// Print formatted student row
void Student::display() const {
    std::cout << std::left << std::setw(10) << id
              << std::setw(20) << name
              << std::fixed << std::setprecision(2)
              << std::setw(8) << (marks ? marks[0] : 0.0f)
              << std::setw(8) << (marks ? marks[1] : 0.0f)
              << std::setw(8) << (marks ? marks[2] : 0.0f)
              << std::setw(8) << total
              << std::setw(8) << average
              << std::setw(8) << gradeToString(grade)
              << statusToString(status) << "\n";
}

// Update all marks
void Student::updateMarks(const float* newMarks) {
    if (newMarks && marks) {
        for (int i = 0; i < SUBJECT_COUNT; ++i) {
            marks[i] = newMarks[i];
        }
        recalculate();
    }
}

// Update single mark by index
void Student::updateMarks(int index, float newMark) {
    if (index >= 0 && index < SUBJECT_COUNT && marks) {
        marks[index] = newMark;
        recalculate();
    }
}

// Safely retrieve mark value at index
float Student::getMark(int index) const {
    if (index >= 0 && index < SUBJECT_COUNT && marks) {
        return marks[index];
    }
    return 0.0f;
}

// Compare student averages (friend function)
bool compareAverage(const Student& lhs, const Student& rhs) {
    return lhs.average > rhs.average;
}

// Convert status enum to string
std::string statusToString(Status status) {
    return (status == PASS) ? "PASS" : "FAIL";
}

// Convert grade enum class to string
std::string gradeToString(Grade grade) {
    switch (grade) {
        case Grade::A: return "A";
        case Grade::B: return "B";
        case Grade::C: return "C";
        case Grade::D: return "D";
        case Grade::F: return "F";
    }
    return "Unknown";
}

// Whitespace trim helper
std::string trim(const std::string& text) {
    auto start = text.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    auto end = text.find_last_not_of(" \t\n\r");
    return text.substr(start, end - start + 1);
}

// Returns true if string is empty or contains only whitespace
bool isBlank(const std::string& text) {
    return trim(text).empty();
}

// Validates integer inputs
int getValidatedInt(const std::string& prompt, int min, int max) {
    std::string input;
    int value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        
        if (input.empty()) {
            std::cout << "Invalid input. Please enter an integer between " << min << " and " << max << ".\n";
            continue;
        }
        
        bool isNumeric = true;
        for (size_t i = 0; i < input.length(); ++i) {
            if (!std::isdigit(input[i]) && !(i == 0 && input[i] == '-')) {
                isNumeric = false;
                break;
            }
        }
        
        if (isNumeric) {
            try {
                value = std::stoi(input);
                if (value >= min && value <= max) {
                    return value;
                }
            } catch (...) {}
        }
        
        std::cout << "Invalid input. Please enter an integer between " << min << " and " << max << ".\n";
    }
}

// Validates marks input [0, 100]
float getValidatedMark(const std::string& prompt) {
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
                if (processedChars == input.length() && value >= 0.0f && value <= 100.0f) {
                    return value;
                }
            } catch (...) {}
        }
        std::cout << "Invalid input. Marks must be between 0 and 100.\n";
    }
}

// Validates non-empty names
std::string getValidatedName(const std::string& prompt) {
    std::string name;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, name);
        if (!isBlank(name)) {
            return trim(name);
        }
        std::cout << "Name cannot be empty or just whitespace. Please try again.\n";
    }
}
