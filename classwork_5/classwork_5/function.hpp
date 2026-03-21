#pragma once
#include <iostream>
#include "maybe.hpp"
template <typename U, typename V>
class FunctionPair {
	U u;
	V v;
public:
	U getU()const {
		return u;
	}
	V& getV() {
		return v;
	}
	FunctionPair(const U& u = U(), const V& v = V()) :u(u), v(v) {

	}
};

template <typename U, typename V>
class Function {
	FunctionPair<U,V>* pairs;
	int pairCount;
	int maxSize;

	void resize() {
		maxSize *= 2;
		FunctionPair<U,V>* newPairs = new FunctionPair<U,V>[maxSize];
		for (int i = 0; i < pairCount; i++) {
			newPairs[i] = pairs[i];
		}
		delete[] pairs;
		pairs = newPairs;
	}
public:
	Function() {
		pairCount = 0;
		maxSize = 10;
		pairs = new FunctionPair<U,V>[maxSize];
	}
	Function(const Function& other):pairCount(other.pairCount), maxSize(other.maxSize){
		pairs = new FunctionPair<U, V>[maxSize];
		for (int i = 0; i < pairCount; i++) {
			pairs[i] = other.pairs[i];
		}
	}

	Function& operator=(const Function& other) {
		if (this != &other) {
			delete[] pairs;
			pairCount = other.pairCount;
			maxSize = other.maxSize;
			pairs = new FunctionPair<U, V>[maxSize];
			for (int i = 0; i < pairCount; i++) {
				pairs[i] = other.pairs[i];
			}
		}
		return *this;
	}
	
	void addPair(const U& u, const V& v) {
		if (pairCount == maxSize)
			resize();
		for (int i = 0; i < pairCount; i++) {
			if (pairs[i].getU() == u) {
				pairs[i].getV() = v;
				return;
			}
		}
		pairs[pairCount++] = FunctionPair<U, V>(u, v);
	}
	Maybe<V> getValue(const U& u) const {
		for (int i = 0; i < pairCount; i++) {
			if (pairs[i].getU() == u) {
				return Maybe<V>(pairs[i].getV());
			}
		}
		return Maybe<V>();
	}
	Maybe<V> getValue(const Maybe<U>& u) const {
		if (u)
			return getValue(u.get());
		return Maybe<V>();
	}
	bool hasKey(const U& u) const {
		return getValue(u);
	}
	friend std::ostream& operator <<(std::ostream& os, Function<U, V>& func) {
		os << "{";
		int pairCnt = func.pairCount;
		for (int i = 1; i < pairCnt; i++) {
			os << func.pairs[i-1].getU() << ":" << func.pairs[i-1].getV() << ", ";
		}
		os << func.pairs[pairCnt - 1].getU() << ":" << func.pairs[pairCnt - 1].getV();
		os << "}";
		return os;
	}
	V& operator[](const U& u) {
		if (!hasKey(u))
			std::exit(1);
		for (int i = 0; i < pairCount; i++) {
			if (pairs[i].getU() == u)
				return pairs[i].getV();
		}
	}
	Maybe<V> operator()(const U& u) {
		return getValue(u);
	}
	Maybe<V> operator()(const Maybe<U>& u) {
		return getValue(u);
	}
	Function operator+(const Function& other) {
		Function res;
		delete[] res.pairs;

		res.maxSize = this->maxSize + other.maxSize;
		res.pairs = new FunctionPair<U, V>[res.maxSize];

		int thisPairCount = this->pairCount;
		for (int i = 0; i < thisPairCount; i++) {
			U currU = pairs[i].getU();
			Maybe<V> otherMatch = other.getValue(currU);
			if (otherMatch) {
				res.pairs[res.pairCount++] = FunctionPair<U, V>(currU, pairs[i].getV() + otherMatch.get());
			}
			else {
				res.pairs[res.pairCount++] = pairs[i];
			}
		}
		int otherPairCount = other.pairCount;
		for (int i = 0; i < otherPairCount; i++) {
			Maybe<V> resMatch = res.getValue(other.pairs[i].getU());
			if (!resMatch) {
				res.pairs[res.pairCount++] = other.pairs[i];
			}
		}
		return res;
	}

	Function& operator+=(const Function& other) {
		*this = *this + other;
		return *this;
	}
	
	~Function() {
		delete[] pairs;
	}
	template <typename A, typename B, typename C>
	friend Function<A, C> operator*(const Function<A, B>& f1, const Function<B, C>& f2);
};

template <typename A, typename B, typename C>
Function<A, C> operator*(const Function<A, B>& f1, const Function<B, C>& f2) {
	Function<A, C> res;
	res.maxSize = f1.maxSize;
	for (int i = 0; i < f1.pairCount; i++) {
		Maybe<C> match = f2.getValue(f1.pairs[i].getV());
		if (match) {
			res.pairs[res.pairCount++] = FunctionPair<A, C>(f1.pairs[i].getU(), *match);
		}
	}
	return res;
}
