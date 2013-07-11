#ifndef _BUFFER_H
#define _BUFFER_H

//Defines a circular buffer.
//This will automatically 
//overwrite the oldest element in the buffer

template <class T>
class Buffer {
public:
	const int size;
	
	Buffer(int s);
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