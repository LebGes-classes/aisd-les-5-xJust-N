#pragma once

#include "Node.h"
#include <vector>
#include <string>

template <typename T>
class PriorityQueue 
{
private:

	std::vector<Node<T>> heap;
	int size = 0;

	int indexOfParent(int i)
	{
		return (i - 1) / 2;
	}

	int indexOfLeftChild(int i)
	{
		return 2 * i + 1;
	}

	int indexOfRightChild(int i)
	{
		return 2 * i + 2;
	}

	void siftUp(int i) 
	{
		while (i > 0 && heap[indexOfParent(i)].priority < heap[i].priority) 
		{
			std::swap(heap[indexOfParent(i)], heap[i]);
			i = indexOfParent(i);
		}
	}

	void siftDown(int i) 
	{
		int maxIndex = i;
		int left = indexOfLeftChild(i);
		int right = indexOfRightChild(i);

		if (left < size && heap[left].priority > heap[maxIndex].priority) 
		{
			maxIndex = left;
		}

		if (right < size && heap[right].priority > heap[maxIndex].priority) 
		{
			maxIndex = right;
		}

		if (i != maxIndex) 
		{
			std::swap(heap[i], heap[maxIndex]);
			siftDown(maxIndex);
		}
	}


	int findIndex(T data)
	{
		for (int i = 0; i < size; i++) 
		{
			if (heap[i].data == data) 
			{
				return i;
			}
		}
		return -1;
	}

public:

	PriorityQueue() = default;
	~PriorityQueue() = default;

	void enqueue(T data, int priority) 
	{
		heap.emplace_back(data, priority);
		size++;
		siftUp(size - 1);
	}

	T dequeue() 
	{
		T rootData = heap[0].data;
		heap[0] = heap.back();
		heap.pop_back();
		size--;

		if (!isEmpty()) 
		{
			siftDown(0);
		}

		return rootData;
	}

	T peek()
	{
		return heap[0].data;
	}

	void increasePriority(T data, int prio) 
	{
		int index = findIndex(data);

		heap[index].priority += prio;
		siftUp(index);
	}

	int getSize()
	{
		return size;
	}

	bool isEmpty()
	{
		return size == 0;
	}
};