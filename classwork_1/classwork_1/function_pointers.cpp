#include <iostream>

void print12() {
	std::cout << 12;
}


void loop(void (*f) (void), const int n) {
	for (int i = 0; i < n; i++)
		f();
}


int mulBy2(int x) {
	return x * 2;
}
int repeat(int (*f) (int), int x0, int n) {
	if (n == 0)
		return x0;
	return repeat(f, f(x0), n - 1);
}
void swap(int& a, int& b) {
	int temp = b;
	b = a;
	a = temp;
}
bool compareBigger(int a, int b) {
	return a > b;
}
bool compareSmaller(int a, int b) {
	return a < b;
}
void sort(int arr[], size_t size, bool (*comparator) (int, int) ) {
	for (int i = 0; i < size; i++) {
		for (int j = size-1; j > i; j--) {
			if (!comparator(arr[j], arr[j - 1]))
				swap(arr[j], arr[j - 1]);
		}
	}
}
int main() {
	int arr[] = { 1,2,8,124,111,0 };
	//loop(print12, 5);
	//std::cout << repeat(mulBy2, 3, 5);
	sort(arr, 6, compareSmaller);
}