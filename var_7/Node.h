#pragma once

template <typename T>
struct Node {
	int priority;
	T data;

	Node(const T& d, int p) : data(d), priority(p) {}
	~Node() {}
};
