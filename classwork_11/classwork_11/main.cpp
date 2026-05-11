#include <iostream>
#include <vector>
#include <functional>


template <typename U, typename V>
class LazyMap {
	const std::vector<U>& source;
	const std::function<V(U)> func;
public:

	class LazyMapIterator{
		std::vector<U>::const_iterator it;
		const std::function<V(U)>& f;

		V cache;
		bool is_calculated;
	public:
		LazyMapIterator(std::vector<U>::const_iterator it,const std::function<V(U)>& f):it(it),f(f),cache(V()),is_calculated(false) {

		}
		V operator*() {
			if (!is_calculated) {
				cache = f(*it);
				is_calculated = true;
			}
			return cache;
		}
		bool operator!=(const LazyMapIterator& other) const{
			return it != other.it;
		}
		LazyMapIterator& operator++() {
			++it;
			is_calculated = false;
			return *this;
		}
		LazyMapIterator operator++(int) {
			LazyMapIterator old = *this;
			operator++();
			return old;
		}
	};
	LazyMap(std::vector<U>& v, std::function<V(U)> f):source(v),func(f) {
	
	}
	V operator[](unsigned index) const{
		if (index >= source.size())
			std::exit(1);
		return func(source.at(index));
	}
	LazyMapIterator begin() const {
		return LazyMapIterator(source.begin(),func);
	}
	LazyMapIterator end() const {
		return LazyMapIterator(source.end(),func);
	}
};

int main() {
	std::vector<int> v = { 1, 2, 3 };
	auto f = [](int x) { return x * x; };
	LazyMap<int, int> lazyMap(v, f);
	for (auto it = lazyMap.begin(); it != lazyMap.end(); it++) {
		std::cout << *it << " " << *it + 1 << " " << *it + 2;
	}
}