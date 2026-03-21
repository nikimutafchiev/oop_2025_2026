#pragma once
#include <iostream>
#include <cassert>
template <typename T>
class Maybe {
public:
	T* value;

	Maybe() {
		value = nullptr;
	}
	Maybe(T t) {
		value = new T;
		*value = t;
	}
	Maybe(const Maybe& other) {
		if (other.hasValue()) {
			value = new T;
			*value = *other.value;
		}
		else {
			value = nullptr;
		}
	}
	bool hasValue() const {
		return value;
	}
	T get() const {
		assert(hasValue());
		return *value;
	}
	void reset() {
		if (hasValue()) {
			delete value;
		}
		value = nullptr;
	}
	Maybe& operator=(const Maybe& other) {
		if (other.hasValue()) {
			if (!hasValue()) {
				value = new T;
			}
			*value = *other.value;
		}
		else {
			reset();
		}
		return *this;
	}
	explicit operator bool() {
		return hasValue();
	}
	friend T& operator*(const Maybe& maybe) {
		if (!maybe.hasValue())
			std::exit(1);
		return *maybe.value;
	}
	T& operator->() {
		if (!hasValue())
			std::exit(1);
		return *value;
	}
	~Maybe() {
		reset();
	}
};