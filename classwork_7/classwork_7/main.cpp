#include <iostream>
#include <cassert>
#include "vector.hpp"
#include <fstream>
#include "student.hpp"

void testVector() {
    std::cout << "=== Vector<int> ===\n";

    Vector<int> v;
    for (int i = 1; i <= 8; ++i) v.push_back(i * 10);

    std::cout << "size=" << v.getSize()
        << "  capacity=" << v.getCapacity() << "\n";

    // operator[]
    std::cout << "v[3] = " << v[3] << "\n";

    // at() с грешен индекс
    try {
        v.at(100);
    }
    catch (const std::out_of_range& e) {
        std::cout << "at(100) throw: " << e.what() << "\n";
    }

    // pop_back
    v.pop_back();
    std::cout << "After pop_back, size=" << v.getSize() << "\n";

    // Копиращ конструктор
    Vector<int> v2 = v;
    v2.push_back(999);
    std::cout << "v.size()=" << v.getSize()
        << "  v2.size()=" << v2.getSize() << "\n";

    // operator=
    Vector<int> v3;
    v3 = v2;
    assert(v3.getSize() == v2.getSize());
    std::cout << "operator= OK\n\n";
}

void testBinaryFiles() {
    const char* FILE = "students.bin";
    std::cout << "=== Binary files ===\n";

    // 1. Запис
    Vector<Student> vec(3);
    float grades[] = { 5.5f, 4.0f, 6.0f };
    vec.push_back(Student("Ivam Petrov", grades,3));
    vec.push_back(Student("Maria Ivanova", grades,3));
    vec.push_back(Student("Peter Georgiev", grades,3));

    saveStudents(FILE, vec);
    std::cout << "Saved 3 students.\n";

    // 2. Четене
    Vector<Student> loaded = readStudents(FILE);
    std::cout << "Read " << loaded.getSize() << " students:\n";
    for (std::size_t i = 0; i < loaded.getSize(); ++i)
        std::cout << loaded[i];

    // 3. Добавяне без презареждане
    Student newS = Student("Elena Stoyanova", grades,2);
    appendStudent(FILE, newS);
    std::cout << "\nAfter appendStudent:\n";
    Vector<Student> loaded2 = readStudents(FILE);
    std::cout << "Read " << loaded2.getSize() << " students:\n";
    for (std::size_t i = 0; i < loaded2.getSize(); ++i)
        std::cout << loaded2[i];

    // 4. Търсене по име
    Student found{};
    bool ok = findStudentInFile(FILE, "Maria Ivanova", found);
    if (ok) {
        std::cout << "\nFound student:\n";
        std::cout << found <<std::endl;
    }
    else {
        std::cout << "\nStudent not found.\n";
    }

    // Търсене на несъществуващ
    bool notOk = findStudentInFile(FILE, "Unknown", found);
    std::cout << "Searching for 'Unknown': " << (notOk ? "found" : "not found") << "\n";

    // Зареждане от несъществуващ файл → празен вектор
    Vector<Student> empty = readStudents("no_such_file.bin");
    assert(empty.empty());
    std::cout << "loadStudents(Unknown) returned empty vector - OK\n";
}

int main() {
    testVector();
    testBinaryFiles();
}