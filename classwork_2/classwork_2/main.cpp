#include <iostream>
void strCpy(char* dest, const char* src) {
	while (*src) {
		*dest++ = *src++;
	}
	*dest = 0;
}
template <typename T>
class Student {
	char name[60];
	T facultyNumber;
	unsigned grades[8][32];
	unsigned curr_semester;
	unsigned grades_count[8];

public:
	Student() {

	}
	Student(const char* name, int facultyNumber) {
		strCpy(this->name, name);
		this->facultyNumber = facultyNumber;
		this->curr_semester = 0;
		for (int i = 0; i < 8; i++) {
			grades_count[i] = 0;
		}
	}
	void AddGrade(int grade) {
		this->grades[this->curr_semester][this->grades_count[curr_semester]++] = grade;
	}
	double GetTermAverage() {
		int sum = 0;
		for (int i = 0; i < grades_count[curr_semester]; i++) {
			sum += this->grades[curr_semester][i];
		}
		return (double)sum / grades_count[curr_semester];
	}
	double getAverage() {
		int sum = 0,grades_count = 0;
		for (int i = 0; i <= curr_semester; i++) {
			grades_count += this->grades_count[i];
			for (int j = 0; j < this->grades_count[i]; j++) {
				sum += grades[i][j];
			}
		}
		return (double)sum / grades_count;
	}

};
class University {
	char name[60];
	Student<int> students[128];
	unsigned students_count;

public:
	University(const char* name) {
		strCpy(this->name, name);
		this->students_count = 0;
	}
	University(const char* name, const Student<int> students[], size_t size) {
		strCpy(this->name, name);
		for (size_t i = 0; i < size; i++) {
			this->students[i] = students[i];
		}
		this->students_count = size;
	}
	double getTermAverage() {
		double sum = 0;
		size_t size = this->students_count;
		for (int i = 0; i < size; i++) {
			sum += students[i].GetTermAverage();
		}
		return sum / size;
	}

	double getAverage() {
		double sum = 0;
		size_t size = this->students_count;
		for (int i = 0; i < size; i++) {
			sum += students[i].getAverage();
		}
		return sum / size;
	}

};
int main() {
	Student<int> s1("Ivan",12);
	Student<int> s2("Ivan2",13);
	Student<int> s3("Ivan3",14);
	Student<int> s4("Ivan4",15);
	s1.AddGrade(4);
	s2.AddGrade(1);
	s3.AddGrade(7);
	s1.AddGrade(6);
	s4.AddGrade(4);
	s1.AddGrade(2);
	s2.AddGrade(4);
	Student<int> s[4] = { s1,s2,s3,s4 };
	University u("SU",s,4);
	std::cout << u.getAverage();
}