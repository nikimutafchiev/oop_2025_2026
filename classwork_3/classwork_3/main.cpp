#include <iostream>
//1
class Agent {

	static unsigned count;
public:
	Agent() {
		count++;
	}
	Agent(const Agent& other) {
		count++;
	}
	static unsigned getCount() {
		return count;
	}
	~Agent() {
		count--;
	}
};
unsigned Agent::count = 0;

//2
class Dipper {
	const unsigned id;
	static unsigned count;

public:
	Dipper() :id(count + 1) {
		count++;
	}
	Dipper(const Dipper& other) :id(count + 1) {
		count++;
	}
	Dipper& operator=(const Dipper&) {
		return *this;
	}
	unsigned getNumber() const {
		return id;
	}
};
unsigned Dipper::count = 0;

class Str {
	char* str;
	static char* strCat(const char* s1, const char* s2) {
		unsigned str1Len = strlen(s1), str2Len = strlen(s2);
		char* resStr = new char[str1Len + str2Len + 1];

		strcpy(resStr, s1);
		strcpy(resStr + str1Len, s2);
		return resStr;
	}
	void swap(Str& other) {
		using std::swap;

		swap(this->str, other.str);
	}
public:
	Str() = default;
	Str(const char* str) {

		this->str = new char[strlen(str) + 1];
		strcpy(this->str, str);
	}
	Str(const Str& other) {
		this->str = new char[strlen(other.str) + 1];
		strcpy(this->str, other.str);
	}
	void setStr(char* s) {
		this->str = s;
	}
	Str& operator=(const Str& other) {
		Str copy(other);
		swap(copy);

		return *this;
	}
	char* c_str() const {
		return this->str;
	}
	~Str() {
		delete[] this->str;
	}
	unsigned length() const {
		return strlen(this->str);
	}
	static Str cat(const Str& str1, const Str& str2) {

		char* resStr = strCat(str1.str, str2.str);
		Str res;
		res.setStr(resStr);

		return res;
	}
	static int cmp(const Str& str1, const Str& str2) {
		return strcmp(str1.str, str2.str);
	}
	Str cat(const Str& other) {
		char* resStr = strCat(this->str, other.str);

		Str res;
		res.setStr(resStr);

		return res;
	}

	int cmp(const Str& other) const {
		return strcmp(this->str, other.str);
	}
};

class Matrix {
	const int columns, rows;
	double** arr;

	bool isValidPosition(int row, int col)const {
		return row >= 0 && row < rows && col >= 0 && col < columns;
	}
	static double multipliedCell(const Matrix& mat1, const Matrix& mat2, int i, int j) {
		double res = 0;
		int size = mat1.getCols();

		for (int k = 0; k < size; k++) {
			res += mat1.getValue(i, k) * mat2.getValue(k, j);
		}
		return res;
	}
	void initMatrix() {
		arr = new double* [rows] {};
		for (int i = 0; i < rows; i++) {
			arr[i] = new double [columns] {};
		}
	}
public:
	Matrix(int rows, int columns) :columns(columns), rows(rows) {
		initMatrix();
	}

	Matrix(const Matrix& other) :columns(other.getCols()), rows(other.getRows()) {
		initMatrix();
	}
	Matrix(std::initializer_list<std::initializer_list<double>> matrix) :rows(matrix.size()), columns((*matrix.begin()).size()) {
		initMatrix();
		int rowIndex = 0;
		for (std::initializer_list row : matrix) {
			setRow(rowIndex++, row);
		}
	}
	~Matrix() {
		for (int i = 0; i < rows; i++) {
			delete[] arr[i];
		}
		delete[] arr;
	}
	int getRows() const {
		return rows;
	}
	int getCols() const {
		return columns;
	}
	void setValue(int row, int col, double value) {
		if (!isValidPosition(row, col)) {
			std::cerr << "Index out of bonds" << std::endl;
			std::exit(1);
		}
		arr[row][col] = value;
	}

	double getValue(int row, int col) const {
		if (!isValidPosition(row, col)) {
			std::cerr << "Index out of bonds" << std::endl;
			std::exit(1);
		}
		return arr[row][col];
	}

	double& at(int row, int col) const {
		if (!isValidPosition(row, col)) {
			std::cerr << "Index out of bonds" << std::endl;
			std::exit(1);
		}
		return arr[row][col];
	}
	void print() const {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				std::cout << arr[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	static Matrix identity(int size) {
		if (size < 1) {
			std::cerr << "Size must be greater than 0";
			std::exit(1);
		}
		Matrix res(size, size);
		for (int i = 0; i < size; i++) {
			res.setValue(i, i, 1);
		}
		return res;
	}
	static Matrix add(const Matrix& mat1, const Matrix& mat2) {
		int rows1 = mat1.getRows(), rows2 = mat2.getRows(), cols1 = mat1.getCols(), cols2 = mat2.getCols();

		if (rows1 != rows2 || cols1 != cols2) {
			std::cerr << "Incompatible matrices";
			std::exit(1);
		}

		Matrix res(rows1, cols1);
		for (int i = 0; i < rows1; i++) {
			for (int j = 0; j < cols1; j++) {
				res.setValue(i, j, mat1.getValue(i, j) + mat2.getValue(i, j));
			}
		}
		return res;
	}
	static Matrix multiply(const Matrix& mat1, const Matrix& mat2) {
		int rows1 = mat1.getRows(), rows2 = mat2.getRows(), cols1 = mat1.getCols(), cols2 = mat2.getCols();
		if (cols1 != rows2) {
			std::cerr << "Incompatible matrices";
			std::exit(1);
		}

		Matrix res(rows1, cols2);

		for (int i = 0; i < rows1; i++) {
			for (int j = 0; j < cols2; j++) {
				res.setValue(i, j, multipliedCell(mat1, mat2, i, j));
			}
		}

		return res;
	}

	void setRow(int rowIndex, std::initializer_list<double> row) {
		if (rowIndex<0 || rowIndex>rows) {
			std::cerr << "Invalid index";
			std::exit(1);
		}
		if (row.size() > columns) {
			std::cerr << "Too many initializer values";
			std::exit(1);
		}
		int colIndex = 0;
		for (int cellValue : row) {
			this->setValue(rowIndex, colIndex++, cellValue);
		}
		for (int i = colIndex; i < columns; i++) {
			this->setValue(rowIndex, i, 0);
		}
	}
};
int main() {
	Matrix mat1(2, 3), mat2(2, 3);

	mat1.setValue(0, 0, 1.0);
	mat1.setValue(0, 1, 2.0);
	mat1.setValue(0, 2, 3.0);
	mat1.setValue(1, 0, 4.0);
	mat1.setValue(1, 1, 5.0);
	mat1.setValue(1, 2, 6.0);

	mat2.setValue(0, 0, 7.0);
	mat2.setValue(0, 1, 8.0);
	mat2.setValue(0, 2, 9.0);
	mat2.setValue(1, 0, 10.0);
	mat2.setValue(1, 1, 11.0);
	mat2.setValue(1, 2, 12.0);

	std::cout << "Matrix 1:" << std::endl;
	mat1.print();

	mat1.setRow(1, { 14.0,15.0,16.0 });
	std::cout << "Matrix 1.1:" << std::endl;
	mat1.print();

	Matrix sum = Matrix::add(mat1, mat2);
	std::cout << "Sum of matrices:" << std::endl;
	sum.print();

	Matrix identity = Matrix::identity(3);
	std::cout << "Identity matrix of size 3:" << std::endl;
	identity.print();

	Matrix mat = {
{1.0, 2.0, 3.0},
{4.0, 5.0, 6.0},
{7.0, 8.0, 9.0},
		{12.0},{}
	};
	std::cout << "Matrix: " << std::endl;
	mat.print();

	return 0;

}