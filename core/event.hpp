#pragma once
#include "helpers\dynamicArray.hpp"
#include "helpers\helpFunctions.hpp"

class event_args_voidptr;
class event_args_voidptr_point;

typedef void(*onFocusEvent_DelegateType)(void*);
typedef void(*onClickEvent_DelegateType)(void*, point);

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
	dynamicArray<void(*)(void*, point)> delegates;

	void call(void* arg1, point arg2)
	{
		for (int i = 0; i < delegates.count; i++)
		{
			delegates[i](arg1, arg2);
		}
	}

	friend void operator+=(event_args_voidptr_point& left, void(*right)(void*, point));
	friend void operator-=(event_args_voidptr_point& left, void(*right)(void*, point));
};
void operator+=(event_args_voidptr_point& left, void(*right)(void*, point))
{
	left.delegates.add(right);
}
void operator-=(event_args_voidptr_point& left, void(*right)(void*, point))
{
	left.delegates.delElement(right);
}