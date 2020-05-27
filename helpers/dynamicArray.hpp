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
	bool add(int elementsCount, A element)
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
	void del(A element)
	{
		for (int i = 0; i < count; i++)
		{
			if (arr[i] == element)
			{
				for (int j = i + 1; j < count; j++)
				{
					arr[j - 1] = arr[j];
				}
			}
		}
		count--;
	}
	unsigned int getSize()
	{
		return (sizeof(A) * count);
	}
	A &operator[](int elementId)
	{
		return arr[elementId];
	}
	dynamicArray<A> getCopyOf(dynamicArray<A>& copyedArray)
	{
		arr = copy(copyedArray.arr, copyedArray.count * sizeof(A));
		count = copyedArray.count;

		return result;
	}
};