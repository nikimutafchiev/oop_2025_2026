#include <iostream>
#include "vector.hpp"
struct Student {
    char name[64];
    float grades[10];
    int gradeCount;
    Student() = default;
    Student(const char* name, float grades[], int gradeCount);
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

std::ostream& saveStudent(std::ostream& os, const Student& student);
void saveStudents(const char* filename, Vector<Student>& students);
Student readStudent(std::istream& is);
Vector<Student> readStudents(const char* filename);
void appendStudent(const char* filename, const Student& student);
bool findStudentInFile(const char* filename, const char* name, Student& st);