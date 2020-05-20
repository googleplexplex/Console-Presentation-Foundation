#pragma once
#include "helpers\dynamicArray.hpp"
#include "helpers\helpFunctions.hpp"

class event_args_voidptr;
class event_args_voidptr_point;

//The delegate of on focus events should look like "void onFocus(void* element, point mousePos)"
typedef void(*onFocus_DelegateType)(void*, point);
typedef void(*onFocusLost_DelegateType)(void*, point);
//The delegate of on click event should look like "void onClick(void* element, point clickedPoint)"
typedef void(*onClick_DelegateType)(void*, point);
typedef void(*onLeftButtonDown_DelegateType)(void*, point);
typedef void(*onLeftButtonUp_DelegateType)(void*, point);
typedef void(*onRightButtonDown_DelegateType)(void*, point);
typedef void(*onRightButtonUp_DelegateType)(void*, point);

typedef event_args_voidptr			onFocus_EventType;
typedef event_args_voidptr			onFocusLost_EventType;
typedef event_args_voidptr_point	onClick_EventType;
typedef event_args_voidptr_point	onLeftButtonDown_EventType;
typedef event_args_voidptr_point	onLeftButtonUp_EventType;
typedef event_args_voidptr_point	onRightButtonDown_EventType;
typedef event_args_voidptr_point	onRightButtonUp_EventType;

void callDelegate(void(*_delegate)(void*), void* delegateArg)
{
	if (_delegate != NULL)
		_delegate(delegateArg);
}
void callDelegate(void(*_delegate)(void*, point), void* firstDelegateArg, point secondDelegateArg)
{
	if (_delegate != NULL)
		_delegate(firstDelegateArg, secondDelegateArg);
}

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
	if (right != NULL)
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
	if(right != NULL)
		left.delegates.add(right);
}
void operator-=(event_args_voidptr_point& left, void(*right)(void*, point))
{
	left.delegates.delElement(right);
}