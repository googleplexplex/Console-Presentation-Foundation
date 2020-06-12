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

template<typename T> struct dynamicArray //First type - array type
{
	T* arr;
public:
	unsigned int count;
	dynamicArray() { arr = NULL; count = 0; }
	dynamicArray(const T& element) { arr = element; count = 1; }
	dynamicArray(T* _arr, int _count) { arr = copy(_arr, _count); count = _count; }
	dynamicArray(const T* _arr, int _count) { arr = copy(_arr, _count); count = _count; }
	dynamicArray(const char* str) { count = strlen(str); arr = copy(str, count); }

	bool add(int newElementsCount)
	{
		T* temp = arr;
		arr = new T[count + newElementsCount];
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
	bool add(T element)
	{
		if (add(1) == false)
			return false;
		arr[count - 1] = element;
		return true;
	}
	bool add(T element, int elementsCount)
	{
		int prevCount = count;
		if (add(elementsCount) == false)
			return false;

		for (int i = 0; i < elementsCount; i++)
		{
			arr[prevCount + i] = element;
		}

		return true;
	}

	void set(T element, int elementsCount)
	{
		delete arr;

		arr = new T[elementsCount];
		for (int i = 0; i < elementsCount; i++)
		{
			arr[i] = element;
		}
		count = elementsCount;
	}
	void set(T element)
	{
		delete arr;

		arr = new T();
		arr[0] = element;
		count = 1;
	}

	inline void clean()
	{
		delete[] arr;
		arr = NULL;
		count = 0;
	}

	int find(T element)
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
	void del(T element)
	{
		int deletedElement = find(element);
		if (deletedElement == -1)
			return;
		del(deletedElement);
	}

	unsigned int getSize()
	{
		return (sizeof(T) * count);
	}

	T &operator[](int elementId)
	{
		return arr[elementId];
	}
	dynamicArray<T>& operator=(dynamicArray<T>& copyedArray)
	{
		arr = copy(copyedArray.arr, copyedArray.count * sizeof(T));
		count = copyedArray.count;

		return *this;
	}
	template <typename B>
	dynamicArray<T>& operator=(const B* newArr)
	{
		delete arr;
		arr = newArr;
		count = 0;

		return *this;
	}
	dynamicArray<T>& operator=(decltype(NULL) settedNull)
	{
		delete arr;
		arr = (T*)settedNull;
		count = 0;

		return *this;
	}
	template <typename B>
	bool operator==(const B& ptr)
	{
		return ((void*)arr == (void*)ptr);
	}
	template <typename B>
	bool operator!=(const B& ptr)
	{
		return ((void*)arr != (void*)ptr);
	}
};