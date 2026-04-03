#pragma once
template <typename T>
class Vector {
	T* arr;
	size_t capacity;
	size_t size;
	void copy_arr(T* dest, T* src, size_t size) {
		for (size_t i = 0; i < size; i++) {
			dest[i] = src[i];
		}
	}
	void grow() {
		if (capacity)
			capacity *= 2;
		else
			capacity = 1;
		T* new_arr = new T[capacity]{};
		copy_arr(new_arr, arr, size);
		delete[] arr;
		arr = new_arr;
	}
public:
	Vector() :arr(nullptr), capacity(0), size(0) {

	}
	explicit Vector(size_t capacity) :capacity(capacity) {
		this->arr = new T[capacity]{};
	}
	Vector(const Vector& other) {
		this->arr = new T[other.capacity]{};
		copy_arr(this->arr, other.arr, other.size);
		this->size = other.size;
		this->capacity = other.capacity;
	}
	Vector& operator=(const Vector& other) {
		if (this != &other) {
			delete[] arr;
			this->arr = new T[other.capacity]{};
			copy_arr(this->arr, other.arr, other.size);
			this->size = other.size;
			this->capacity = other.capacity;
		}
		return *this;
	}
	~Vector() {
		delete[] arr;
	}
	void push_back(const T& element) {
		if (size == capacity)
			grow();
		arr[size++] = element;
	}
	T pop_back() {
		if (size > 0)
			return arr[--size];
		else
			std::exit(1);
	}
	T& operator[] (size_t index) {
		return arr[index];
	}
	const T& operator[] (size_t index) const{
		return arr[index];
	}
	size_t getSize()const {
		return size;
	}
	size_t getCapacity()const {
		return capacity;
	}
	T& at(size_t index) {
		return arr[index];
	}
	friend std::ostream& operator <<(std::ostream& os, Vector vec) {
		for (int i = 0; i < vec.size; i++) {
			std::cout << vec[i] << " ";
		}
		std::cout << std::endl;
	}
	bool empty() {
		return size == 0;
	}
};