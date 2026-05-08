#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

template <typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;
	Node() = default;
	Node(T data, Node* prev, Node*next) :data(data),prev(prev),next(next){}
};
template <typename T>
class ListIterator {
	Node<T> *curr;
public:
	ListIterator(Node<T>* node) {
		curr = node;
	}
	ListIterator& operator++() {
		curr = curr->next;
		return *this;
	}
	ListIterator operator++(int) {
		ListIterator copy = *this;
		curr = curr->next;
		return copy;
	}
	T operator*() {
		return curr->data;
	}
	bool operator==(const ListIterator& other) const{
		return curr == other.curr;
	}
	bool operator!=(const ListIterator& other) const{
		return curr != other.curr;
	}
};
template <typename T>
class DoubleLinkedList {
	Node<T>* head;
	Node<T>* tail;
	unsigned node_count;
public:
	DoubleLinkedList() {
		head = tail = nullptr;
		node_count = 0;
	}
	//DoubleLinkedList(const DoubleLinkedList& other) {

	//	for (Node* node:other) {

	//	}
	//}
	void push_front(const T& data) {
		Node<T>* node = new Node<T>(data, nullptr , head);
		if (!node_count)
			tail = head;
		else
			head->prev = node;

		head = node;
		node_count++;
	}
	T pop_front() {
		if (!node_count) {
			std::exit(1);
		}
		
		Node<T>* res = head;
		T data = res->data;
		head = head->next;
		if(head)
			head->prev = nullptr;
		node_count--;
		if (!node_count)
			tail = nullptr;
		delete res;
		return data;
	}
	void push_back(const T& data) {
		Node<T>* node = new Node<T>(data,tail,nullptr);
		if (!node_count)
			head = node;
		else
			tail->next = node;
		tail = node;

		node_count++;
	}
	T pop_back() {
		if (!node_count) {
			std::exit(1);
		}

		Node<T>* res = tail;
		T data = res->data;
		tail = tail->prev;

		if(tail)
			tail->prev = nullptr;
		node_count--;

		if (!node_count)
			head = nullptr;
		delete res;
		return data;
	}
	size_t size()const {
		return node_count;
	}
	ListIterator<T> begin(){
		return ListIterator<T>(head);
	}
	ListIterator<T> end() {
		return ListIterator<T>(tail);
	}
};
TEST_CASE("Test iterator operators") {
	DoubleLinkedList<int> dll,dll2;
	dll.push_back(12);
	dll.push_back(14);
	dll2.push_back(1);
	SUBCASE("*") {
		CHECK(*dll.begin() == 12);
		CHECK(*dll.end() == 14);
	}
	SUBCASE("++") {
		CHECK(*dll.begin()++ == 12);
		CHECK(*++dll.begin() == 14);
	}
	SUBCASE("==") {
		CHECK(dll.begin() == dll.begin());
		CHECK(dll.end() == dll.end());
	}
	SUBCASE("!=") {
		CHECK(dll.end() != dll.begin());
		CHECK(dll.begin() != dll.end());
		CHECK(dll2.begin() != dll.begin());
	}
}

