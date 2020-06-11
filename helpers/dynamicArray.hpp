#pragma once

template <typename A>
A* copy(A* _from, int _count)
{
	A* ret = new A[_count];

	for (int i = 0; i < _count; i++)
	{
		ret[i] = _from[i];
	}

	return ret;
}

template <typename A>
A* copy(const A* _from, int _count)
{
	A* ret = new A[_count];

	for (int i = 0; i < _count; i++)
	{
		ret[i] = _from[i];
	}

	return ret;
}

template<typename A> struct dynamicArray //First type - array type
{
	A* arr;
public:
	unsigned int count;
	dynamicArray() { arr = NULL; count = 0; }
	dynamicArray(A* _arr, int _count) { arr = copy(_arr, _count); count = _count; }
	dynamicArray(const A* _arr, int _count) { arr = copy(_arr, _count); count = _count; }
	dynamicArray(char* str) : dynamicArray(str, strlen(str)) {}
	dynamicArray(const char* str) : dynamicArray(str, strlen(str)) {}

	bool add(int newElementsCount)
	{
		A* temp = arr;
		arr = new A[count + newElementsCount];
		if (!arr)
			return false;
		for (int i = 0; i < count; i++)
		{
			arr[i] = temp[i];
		}
		count += newElementsCount;
		return true;
	}
	bool add()
	{
		return add(1);
	}
	bool add(A element)
	{
		if (add(1) == false)
			return false;
		arr[count - 1] = element;
		return true;
	}
	bool add(A element, int elementsCount)
	{
		if (add(elementsCount) == false)
			return false;

		for (int i = 0; i < count - elementsCount; i++)
		{
			arr[i + count - elementsCount] = element;
		}

		return true;
	}
	inline void clean()
	{
		delete[] arr;
		arr = NULL;
		count = 0;
	}
	void delLast()
	{
		if (count != 0)
			count--;
	}
	void del(unsigned int index)
	{
		for (int i = index + 1; i < count; i++)
		{
			arr[i - 1] = arr[i];
		}
		count--;
	}
	int find(A element)
	{
		for (int i = 0; i < count; i++)
		{
			if (arr[i] == element)
			{
				return i;
			}
		}
		return -1;
	}
	void del(A element)
	{
		int deletedElement = find(element);
		if (deletedElement == -1)
			return;
		del(deletedElement);
	}
	unsigned int getSize()
	{
		return (sizeof(A) * count);
	}
	A &operator[](int elementId)
	{
		return arr[elementId];
	}
	dynamicArray<A>& operator=(dynamicArray<A>& copyedArray)
	{
		arr = copy(copyedArray.arr, copyedArray.count * sizeof(A));
		count = copyedArray.count;

		return *this;
	}
	dynamicArray<A>& operator=(char* str)
	{
		count = strlen(str);
		arr = copy(str, count);

		return *this;
	}
};