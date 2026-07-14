cmake_minimum_required(VERSION 3.10)
project(CST8219_Lab3 CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files
set(SOURCES
    main.cpp
    Student.cpp
    Employee.cpp
    SalariedEmployee.cpp
    HourlyEmployee.cpp
    CommissionEmployee.cpp
)

# Output executable
add_executable(Lab3_app ${SOURCES})
