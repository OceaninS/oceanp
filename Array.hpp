#pragma once
#ifndef _ARRAY_

template<class T> class Array {
private:
	int length;
	int capacity;
	T* address;

public:
	Array(int capacity) {
		this->capacity = capacity;
		this->length = 0;
		this->address = new T[capacity];
	};
	Array(const Array& array) {
		this->capacity = array.capacity;
		this->length = array.length;
		this->address = new T[array.capacity];
		for (size_t index = 0; index != this->length; index++) {
			this->address[index] = array.address[index];
		}
	};
	~Array() {
		if (this->address != nullptr) {
			delete[] this->address;
			this->address = nullptr;
		}
	};
	Array& operator=(const Array& array) {
		if (this->address != nullptr) {
			delete[] this->address;
			this->address = nullptr;
			this->capacity = 0;
			this->length = 0;
		}
		this->capacity = array.capacity;
		this->length = array.length;
		this->address = new T[array.capacity];
		for (size_t index = 0; index != this->length; index++) {
			this->address[index] = array.address[index];
		}
		return *this;
	};
	T& operator[](int index) {
		if(this->length == 0 || index < 0 || index > this->length - 1) throw "Illegal index";
		return this->address[index];
	};
	Array& push(const T& item) {
		if (this->length == this->capacity) return *this;
		this->address[this->length] = item;
		this->length++;
		return *this;
	};
	Array& pop() {
		if (this->length == 0) return *this;
		this->length--;
		return *this;
	};
	int getLength() {
		return this->length;
	};
	int getCapacity() {
		return this->capacity;
	};
};

#endif // !_Array_