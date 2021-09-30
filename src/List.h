#pragma once

#include <assert.h>
#include <string>

template <typename E>
class List {
private:
	void operator = (const List&) {}
	List(const List&) {}

public:

	List() = default;
	virtual void start() const = 0;
	virtual void end() const = 0;
	virtual bool hasNext() const = 0;
	virtual bool hasPrev() const = 0;
	virtual E getNext() const = 0;
	virtual E getPrev() const = 0;
	virtual E get(const int& i) const = 0;
	virtual void add(const E& it) = 0;
	virtual E remove() = 0;
	virtual void insert(const int& i, const E& it) = 0;

	virtual int size() const = 0;
	virtual void clear() = 0;
};





constexpr auto defaultSize = 10;

template <typename E>
class Alist : public List<E>
{
private:
	int listSize;
	int capacity;
	mutable int cursor;
	E* arr;

public:
	Alist(int cap = defaultSize)
	{
		arr = new E[cap];
		capacity = cap;
		listSize = 0;
		cursor = 0;
	}


	~Alist()
	{
		delete[] arr;
	}

	void start() const override;
	void end() const override;
	bool hasNext() const override;
	bool hasPrev() const override;
	E getNext() const override;
	E getPrev() const override;
	E get(const int& i) const override;
	void add(const E& it) override;
	E remove() override;
	E remove(const int& i);
	void insert(const int& i, const E& it) override;

	int size() const override;
	void clear() override;

	std::string toString() const;

 };

/////////////////////////////////////////
//////-------Implementation----------////
/////////////////////////////////////////

template<typename E>
inline void Alist<E>::start() const
{
	cursor = 0;
}

template<typename E>
inline void Alist<E>::end() const
{
	cursor = listSize - 1;
}

template<typename E>
inline bool Alist<E>::hasNext() const
{
	return cursor < listSize;
}

template<typename E>
inline bool Alist<E>::hasPrev() const
{
	return cursor > -1;
}

template<typename E>
inline E Alist<E>::getNext() const
{
	return arr[cursor++];
}

template<typename E>
inline E Alist<E>::getPrev() const
{
	return arr[cursor--];
}

template<typename E>
inline E Alist<E>::get(const int& i) const
{
	assert(i > -1 && i < listSize, "out of bound");
	return arr[i];
}

template<typename E>
inline void Alist<E>::add(const E& it)
{
	if (listSize < capacity)
	{
		arr[listSize++] = it;
		return;
	}

	// create a new array 
	E* temp = arr;
	int cap = capacity * 2;
	arr = new E[cap];

	// copy
	for (int i = 0; i < capacity; i++) {
		arr[i] = temp[i];
	}

	delete[] temp;
	capacity = cap;
	
	// now add item at last position
	arr[listSize++] = it;
}

template<typename E>
inline E Alist<E>::remove()
{
	assert(listSize > 0, "list is empty");
	return arr[listSize--];
}

template<typename E>
inline E Alist<E>::remove(const int& i)
{
	E it = arr[i];
	// fill the gap 
	for (int k = i; k < listSize - 1; k++)
		arr[k] = arr[k + 1];

	return it;
}

template<typename E>
inline void Alist<E>::insert(const int& i, const E& it)
{
	assert(i > -1 && i < listSize, "out of bound error");

	// make room 
	for (int k = listSize - 1; k > i; k--)
		arr[k + 1] = arr[k];

	arr[i] = it;
}

template<typename E>
inline int Alist<E>::size() const
{
	return listSize;
}

template<typename E>
inline void Alist<E>::clear()
{
	delete[] arr;
	capacity = defaultSize;
	listSize = 0;
	arr = new E[capacity];
}

template<typename E>
inline std::string Alist<E>::toString() const
{
	std::string str = std::string("listSize = ") + listSize +
		"\n capacity = " + capacity + "\n";

	for (int i = 0; i < listSize; i++)
	{
		if (i = 0) {
			str.append("[");
			str.append(arr[i]);
			continue;
		}

		str.append(", ").append(arr[i]);
	} 

	str.append("]");
	return str;
}
