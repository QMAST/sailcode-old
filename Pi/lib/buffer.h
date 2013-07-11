#ifndef _BUFFER_H
#define _BUFFER_H

//Defines a circular buffer.
//This will automatically 
//overwrite the oldest element in the buffer

template <class T>
class Buffer {
	const int size;
	
	Buffer(int s) : size(s), n(0);
	void add(T item);
	T pop();
	T* get();
	T peek();
	int peek(T* item);
private:
	T* buf;
	
	int n;//Index
};

#endif