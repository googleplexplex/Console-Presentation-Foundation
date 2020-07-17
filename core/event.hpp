#pragma once
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"

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
//The delegate of text box event should look like "void onTextChanged(void* element)"
typedef void(*onTextChanged_DelegateType)(void*);
//The delegate of draw event should look like "void beforeDraw(void* element)"
typedef void(*beforeDraw_DelegateType)(void*);
typedef void(*afterDraw_DelegateType)(void*);
//The delegate of position/size editing event should look like "void onResize(void* element)"
typedef void(*onResize_DelegateType)(void*);
typedef void(*onMoved_DelegateType)(void*);

typedef event_twoDelegateArg<void*, point>	onFocus_EventType;
typedef event_twoDelegateArg<void*, point>	onFocusLost_EventType;
typedef event_twoDelegateArg<void*, point>	onClick_EventType;
typedef event_twoDelegateArg<void*, point>	onLeftButtonDown_EventType;
typedef event_twoDelegateArg<void*, point>	onLeftButtonUp_EventType;
typedef event_twoDelegateArg<void*, point>	onRightButtonDown_EventType;
typedef event_twoDelegateArg<void*, point>	onRightButtonUp_EventType;
typedef event_twoDelegateArg<void*, char>	onKeyDown_EventType;
typedef event_twoDelegateArg<void*, char>	onKeyUp_EventType;
typedef event_oneDelegateArg<void*>			onTextChanged_EventType;
typedef event_oneDelegateArg<void*>			beforeDraw_EventType;
typedef event_oneDelegateArg<void*>			afterDraw_EventType;
typedef event_oneDelegateArg<void*>			onResize_EventType;
typedef event_oneDelegateArg<void*>			onMoved_EventType;


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
	void add(void(*addedDelegate)(argType))
	{
		if (addedDelegate != NULL)
			delegates.add(addedDelegate);
	}
	void del(void(*deletedDelegate)(argType))
	{
		delegates.del(deletedDelegate);
	}

	event_oneDelegateArg<argType>& operator+=(void(*right)(argType)) noexcept
	{
		add(right);
		return *this;
	}

	event_oneDelegateArg<argType>& operator-=(void(*right)(argType)) noexcept
	{
		del(right);
		return *this;
	}

	event_oneDelegateArg<argType>& operator()(argType arg)
	{
		call(arg);
	}
};

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

	void add(void(*addedDelegate)(fArgType, sArgType))
	{
		if (addedDelegate != NULL)
			delegates.add(addedDelegate);
	}
	void del(void(*deletedDelegate)(fArgType, sArgType))
	{
		delegates.del(deletedDelegate);
	}

	event_twoDelegateArg<fArgType, sArgType>& operator+=(void(*right)(fArgType, sArgType)) noexcept
	{
		add(right);
		return *this;
	}
	event_twoDelegateArg<fArgType, sArgType>& operator-=(void(*right)(fArgType, sArgType)) noexcept
	{
		del(right);
		return *this;
	}

	event_twoDelegateArg<fArgType, sArgType>& operator()(fArgType arg1, sArgType arg2)
	{
		call(arg1, arg2);
	}
};