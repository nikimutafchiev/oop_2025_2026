#include <iostream>

template <typename T>
void print(const T arr[], size_t size) {
	for (size_t i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

template <typename T>
T sum(const T arr[], size_t size) {
	if (size == 0)
		return T();
	T res = arr[0];
	for (size_t i = 1; i < size; i++) {
		res += arr[i];
	}
	return res;
}

template <typename T>
T max(const T arr[], size_t size) {
	if (size == 0)
		return T();
	T max = arr[0];
	for (int i = 1; i < size; i++) {
		if (max < arr[i])
			max = arr[i];
	}
	return max;
}

template <typename T>
T* filter(const T arr[], size_t size, T k, size_t& filtered_size) {
	filtered_size = 0;
	for (size_t i = 0; i < size; i++) {
		if (arr[i] > k)
			filtered_size++;
	}
	T* res = new T[filtered_size];
	size_t index = 0;
	for (size_t i = 0; i < size; i++) {
		if (arr[i] > k)
			res[index++] = arr[i];
	}
	return res;
}
//int main() {
//	int arr1[] = { 1,2,3,4,5 };
//	char arr2[] = "absdba";
//	print(arr1, 5);
//	print(arr2, 6);
//
//	std::cout << sum(arr1, 4);
//
//	std::cout << max(arr2, 6);
//
//	size_t filter_size;
//	char* res = filter(arr2, 5, 'a', filter_size);
//	print(res, filter_size);
//}