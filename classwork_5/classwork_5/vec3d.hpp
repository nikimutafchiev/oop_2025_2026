#pragma once
#include <iostream>
class vec3d {
public:
	double x, y, z;
	vec3d(double x = 0, double y = 0, double z = 0) :x(x), y(y), z(z) {

	}
	vec3d operator+(const vec3d other)const {
		return vec3d(x + other.x, y + other.y, z + other.z);
	}
	vec3d operator-(const vec3d other)const {
		return vec3d(x - other.x, y - other.y, z - other.z);
	}
	vec3d operator*(const vec3d other) const {
		return vec3d(x * other.x, y * other.y, z * other.z);
	}
	vec3d operator/(const vec3d other)const {
		if (abs(other.x) < DBL_EPSILON || abs(other.y) < DBL_EPSILON || abs(other.z) < DBL_EPSILON)
		{
			std::cerr << "Division by zero" << std::endl;
			std::exit(1);
		}
		return vec3d(x / other.x, y / other.y, z / other.z);
	}

	vec3d operator*(double num) const {
		return vec3d(x * num, y * num, z * num);
	}
	vec3d operator/(double num) const {
		if (abs(num) < DBL_EPSILON)
		{
			std::cerr << "Division by zero" << std::endl;
			std::exit(1);
		}
		return vec3d(x / num, y / num, z / num);
	}
	friend vec3d operator*(double val, const vec3d& v) {
		return v * val;
	}
	double dot(const vec3d& other) const {
		return x * other.x + y * other.y + z * other.z;
	}
	double lengthSquared() const {
		return dot(*this);
	}
	double length() const {
		return sqrt(lengthSquared());
	}
	vec3d& normalize() {
		*this = *this / this->length();
		return *this;
	}
	bool isZeroEps()const {
		return x < DBL_EPSILON && y < DBL_EPSILON && z < DBL_EPSILON;
	}
	bool operator==(const vec3d& other) {
		return abs(x - other.x) < DBL_EPSILON && abs(y - other.y) < DBL_EPSILON && abs(z - other.z) < DBL_EPSILON;
	}
	bool operator!=(const vec3d& other) {
		return !(*this == other);
	}
	explicit operator bool() {
		return !isZeroEps();
	}
	friend std::ostream& operator << (std::ostream& os, const vec3d& vec) {
		return os << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
	}
	friend std::istream& operator >> (std::istream& is, vec3d& vec) {
		return is >> vec.x >> vec.y >> vec.z;
	}
};