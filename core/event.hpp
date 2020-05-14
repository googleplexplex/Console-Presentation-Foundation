#pragma once
#include "helpers\dynamicArray.hpp"
#include <windows.h>

class event_args_voidptr;
class event_args_voidptr_point;

typedef void(*onFocusEvent_DelegateType)(void*);
typedef void(*onClickEvent_DelegateType)(void*, POINT);

typedef event_args_voidptr			onFocusEvent;
typedef event_args_voidptr			onFocusLostEvent;
typedef event_args_voidptr_point	onClickEvent;


class event_args_voidptr
{
public:
	dynamicArray<void(*)(void*)> delegates;

	void call(void* arg)
	{
		for (int i = 0; i < delegates.count; i++)
		{
			delegates[i](arg);
		}
	}

	friend void operator+=(event_args_voidptr& left, void(*right)(void*));
	friend void operator-=(event_args_voidptr& left, void(*right)(void*));
};
void operator+=(event_args_voidptr& left, void(*right)(void*))
{
	left.delegates.add(right);
}
void operator-=(event_args_voidptr& left, void(*right)(void*))
{
	left.delegates.delElement(right);
}

class event_args_voidptr_point
{
public:
	dynamicArray<void(*)(void*, POINT)> delegates;

	void call(void* arg1, POINT arg2)
	{
		for (int i = 0; i < delegates.count; i++)
		{
			delegates[i](arg1, arg2);
		}
	}

	friend void operator+=(event_args_voidptr_point& left, void(*right)(void*, POINT));
	friend void operator-=(event_args_voidptr_point& left, void(*right)(void*, POINT));
};
void operator+=(event_args_voidptr_point& left, void(*right)(void*, POINT))
{
	left.delegates.add(right);
}
void operator-=(event_args_voidptr_point& left, void(*right)(void*, POINT))
{
	left.delegates.delElement(right);
}