#pragma once
#include "helpers\dynamicArray.hpp"
#include "helpers\helpFunctions.hpp"

template <typename argType>
class event_oneDelegateArg;
template <typename fArgType, typename sArgType>
class event_twoDelegateArg;

//The delegate of on focus events should look like "void onFocus(void* element, point mousePos)"
typedef void(*onFocus_DelegateType)(void*, point);
typedef void(*onFocusLost_DelegateType)(void*, point);
//The delegate of on click event should look like "void onClick(void* element, point clickedPoint)"
typedef void(*onClick_DelegateType)(void*, point);
typedef void(*onLeftButtonDown_DelegateType)(void*, point);
typedef void(*onLeftButtonUp_DelegateType)(void*, point);
typedef void(*onRightButtonDown_DelegateType)(void*, point);
typedef void(*onRightButtonUp_DelegateType)(void*, point);
//The delegate of on keyboard event should look like "void onKeyPressed(void* element, char pressedCharset)"
typedef void(*onKeyDown_DelegateType)(void*, char);
typedef void(*onKeyUp_DelegateType)(void*, char);

typedef event_twoDelegateArg<void*, point>	onFocus_EventType;
typedef event_twoDelegateArg<void*, point>	onFocusLost_EventType;
typedef event_twoDelegateArg<void*, point>	onClick_EventType;
typedef event_twoDelegateArg<void*, point>	onLeftButtonDown_EventType;
typedef event_twoDelegateArg<void*, point>	onLeftButtonUp_EventType;
typedef event_twoDelegateArg<void*, point>	onRightButtonDown_EventType;
typedef event_twoDelegateArg<void*, point>	onRightButtonUp_EventType;
typedef event_twoDelegateArg<void*, char>	onKeyDown_EventType;
typedef event_twoDelegateArg<void*, char>	onKeyUp_EventType;


template <typename delegateArgType>
void callDelegate(void(*_delegate)(delegateArgType), delegateArgType delegateArg)
{
	if (_delegate != NULL)
		_delegate(delegateArg);
}
template <typename delegateFirstArgType, typename delegateSecondArgType>
void callDelegate(void(*_delegate)(delegateFirstArgType, delegateSecondArgType), delegateFirstArgType firstDelegateArg, delegateSecondArgType secondDelegateArg)
{
	if (_delegate != NULL)
		_delegate(firstDelegateArg, secondDelegateArg);
}

template <typename argType>
class event_oneDelegateArg
{
public:
	dynamicArray<void(*)(argType)> delegates;

	void call(argType arg)
	{
		for (int i = 0; i < delegates.count; i++)
		{
			delegates[i](arg);
		}
	}

	friend event_oneDelegateArg<argType>& operator+=(event_oneDelegateArg<argType>& left, void(*right)(argType));
	friend event_oneDelegateArg<argType>& operator-=(event_oneDelegateArg<argType>& left, void(*right)(argType));
};
template <typename argType>
event_oneDelegateArg<argType>& operator+=(event_oneDelegateArg<argType>& left, void(*right)(argType))
{
	if (right != NULL)
		left.delegates.add(right);
	return *this;
}
template <typename argType>
event_oneDelegateArg<argType>& operator-=(event_oneDelegateArg<argType>& left, void(*right)(argType))
{
	left.delegates.del(right);
	return *this;
}

template <typename fArgType, typename sArgType>
class event_twoDelegateArg
{
public:
	dynamicArray<void(*)(fArgType, sArgType)> delegates;

	void call(fArgType arg1, sArgType arg2)
	{
		for (int i = 0; i < delegates.count; i++)
		{
			delegates[i](arg1, arg2);
		}
	}

	friend event_twoDelegateArg<fArgType, sArgType>& operator+=(event_twoDelegateArg<fArgType, sArgType>& left, void(*right)(fArgType, sArgType));
	friend event_twoDelegateArg<fArgType, sArgType>& operator-=(event_twoDelegateArg<fArgType, sArgType>& left, void(*right)(fArgType, sArgType));
};
template <typename fArgType, typename sArgType>
event_twoDelegateArg<fArgType, sArgType>& operator+=(event_twoDelegateArg<fArgType, sArgType>& left, void(*right)(fArgType, sArgType))
{
	if (right != NULL)
		left.delegates.add(right);
	return *this;
}
template <typename fArgType, typename sArgType>
event_twoDelegateArg<fArgType, sArgType>& operator-=(event_twoDelegateArg<fArgType, sArgType>& left, void(*right)(fArgType, sArgType))
{
	left.delegates.del(right);
	return *this;
}