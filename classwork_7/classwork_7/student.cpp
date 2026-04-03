#include <iostream>
#include "student.hpp"
#include <fstream>    

Student::Student(const char* name, float grades[], int gradeCount) :gradeCount(gradeCount) {
    strcpy_s(this->name, strlen(name) + 1, name);
    for (int i = 0; i < gradeCount; i++) {
        this->grades[i] = grades[i];
    }
}
std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "{" << s.name << ", [ ";
    for (int i = 0; i < s.gradeCount; i++) {
        os << s.grades[i] << " ";
    }
    os << "]," << s.gradeCount << "}";
    return os;
}

std::ostream& saveStudent(std::ostream& os, const Student& student) {
    return os.write((const char*)&student, sizeof(Student));
}
void saveStudents(const char* filename, Vector<Student>& students) {
    std::ofstream os(filename, std::ios::binary);
    size_t size = students.getSize();
    os.write((const char*)&size, sizeof(size_t));
    for (size_t i = 0; i < size; i++) {
        saveStudent(os, students[i]);
    }
}
Student readStudent(std::istream& is) {
    Student student;
    is.read((char*)&student, sizeof(Student));
    return student;
}
Vector<Student> readStudents(const char* filename) {
    std::ifstream is(filename, std::ios::binary);
    size_t size = 0;
    is.read((char*)&size, sizeof(size_t));
    Vector<Student> students(size);
    for (size_t i = 0; i < size; i++) {
        students.push_back(readStudent(is));
    }
    return students;
}
void appendStudent(const char* filename, const Student& student) {
    std::fstream fs(filename, std::ios::binary | std::ios::in | std::ios::out);
    size_t size = 0;
    fs.read((char*)&size, sizeof(size_t));

    size++;
    fs.seekp(0, std::ios::beg);
    fs.write((const char*)&size, sizeof(size_t));

    fs.seekp(0, std::ios::end);
    fs.write((const char*)&student, sizeof(Student));
    fs.close();
}


bool findStudentInFile(const char* filename, const char* name, Student& st) {
    std::ifstream is(filename, std::ios::binary);
    size_t size = 0;
    is.read((char*)&size, sizeof(size_t));
    for (int i = 0; i < size; i++) {
        Student s = readStudent(is);
        if (!strcmp(s.name, name)) {
            st = s;
            return true;
        }
    }
    return false;
}