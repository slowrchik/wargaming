#pragma once
#include <iostream>

//First
template<typename T>
class CircuralBufferFirst
{
	T* buffer;
	size_t size;
	size_t capacity;
	size_t head;
	size_t tail;

public:
	explicit CircuralBufferFirst(size_t capacity_)
		: capacity(capacity_), size(0), head(0), tail(0), buffer(new int[capacity_])
	{
	}

	~CircuralBufferFirst() {
		delete[] buffer;
	}

	bool pushItem(T item) {
		if (size == capacity)
			return false;

		buffer[tail] = item;

		tail = (tail + 1) % capacity;
		size++;

		return true;
	}

	bool getItem(T& var) {
		if (size == 0)
			return false;

		var = buffer[head];
		size--;

		head = (head + 1) % capacity;

		return true;
	}
};


//Second
template<typename T>
class CircuralBufferSecond
{
	T* head;
	T* tail;
	volatile T* readptr;
	volatile T* writeptr;
	size_t capacity;
	size_t size;

public:
	explicit CircuralBufferSecond(size_t capacity_)
		: capacity(capacity_), size(0), head(new T), tail(head + capacity_), writeptr(head), readptr(head)
	{
	}

    ~CircuralBufferSecond() {
        delete head;
    }

	bool pushItem(T item) {
		if (size == capacity)
			return false;
		*writeptr = item;
		if (writeptr + 1 >= tail)
			writeptr = head;
		else
			writeptr = writeptr + 1;
		size++;

		return true;
	}

	bool getItem(T& item) {
		if (size == 0)
			return false;
		item = *readptr;
		if (readptr + 1 >= tail)
			readptr = head;
		else
			readptr = readptr + 1;
		size--;

		return true;
	}

};