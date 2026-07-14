#ifndef STUDENT_H
#define STUDENT_H

#include <initializer_list>
#include <memory>
#include <string>

enum Status { FAIL, PASS };
enum class Grade { A, B, C, D, F };

constexpr int SUBJECT_COUNT = 3;
constexpr float PASS_THRESHOLD = 50.0f;
constexpr int MAX_STUDENTS = 1000;

class Student {
private:
  int id;
  std::string name;
  std::unique_ptr<float[]> marks; // Dynamic array managed by unique_ptr
  float total;
  float average;
  Status status;
  Grade grade;
  // Recursive helper function to calculate total marks
  float calculateTotalRecursive(int index) const;

  // Updates totals, status, and grade
  void recalculate();

public:
  // Constructors
  Student();
  Student(int id, const std::string &name, const float *marksArray);

  // Copy constructor (Deep Copy)
  // Allocates a new array and copies the elements to produce independent data.
  Student(const Student &other);

  // Move constructor
  Student(Student &&other) noexcept;

  // Initializer-list constructor
  Student(int id, const std::string &name,
          std::initializer_list<float> marksList);
  Student(int id, const std::string &name); // Delegating constructor

  // Assignment operators
  Student &operator=(const Student &other);     // Copy assignment
  Student &operator=(Student &&other) noexcept; // Move assignment

  virtual ~Student(); // Virtual destructor

  virtual void display() const; // Virtual display function

  // Overloaded mark updates
  void updateMarks(const float *newMarks);
  void updateMarks(int index, float newMark);

  // Getters
  int getId() const { return id; }
  std::string getName() const { return name; }
  float getTotal() const { return total; }
  float getAverage() const { return average; }
  Status getStatus() const { return status; }
  Grade getGrade() const { return grade; }
  float getMark(int index) const;

  // Friend comparison function
  friend bool compareAverage(const Student &lhs, const Student &rhs);
};

// Formatting helpers
std::string statusToString(Status status);
std::string gradeToString(Grade grade);

// Input Validation helpers
int getValidatedInt(const std::string &prompt, int min, int max);
float getValidatedMark(const std::string &prompt);
std::string getValidatedName(const std::string &prompt);
std::string trim(const std::string &text);
bool isBlank(const std::string &text);

#endif // STUDENT_H
