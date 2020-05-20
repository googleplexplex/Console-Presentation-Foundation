#pragma once
#include "helpers\dynamicArray.hpp"
#include "helpers\helpFunctions.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"

void _setParent(void* _child, void* _parent);
class controlElement
{
public:
	int zIndex = 0;
	point pos;
	point size;
	symbolColor background;
	void* parent;

	onFocus_DelegateType onFocusSystemDelegate = NULL;
	onFocusLost_DelegateType onFocusLostSystemDelegate = NULL;
	onClick_DelegateType onClickSystemDelegate = NULL;
	onLeftButtonDown_DelegateType onLeftButtonDownSystemDelegate = NULL;
	onLeftButtonUp_DelegateType onLeftButtonUpSystemDelegate = NULL;
	onRightButtonDown_DelegateType onRightButtonDownSystemDelegate = NULL;
	onRightButtonUp_DelegateType onRightButtonUpSystemDelegate = NULL;

	onFocus_EventType onFocusEvent;
	onFocusLost_EventType onFocusLostEvent;
	onClick_EventType onClickEvent;
	onLeftButtonDown_EventType onLeftButtonDownEvent;
	onLeftButtonUp_EventType onLeftButtonUpEvent;
	onRightButtonDown_EventType onRightButtonDownEvent;
	onRightButtonUp_EventType onRightButtonUpEvent;

	void registerElement()
	{
		addElementZone({ pos, { pos.x + size.x, pos.y + size.y } });
	}

	virtual void Draw(rectangle drawFrame) = 0;
	virtual bool entersTheArea(point point) = 0;

	void setPos(int x, int y)
	{
		pos.x = x;
		pos.y = y;
	}
	void setSize(int x, int y)
	{
		size.x = x;
		size.y = y;
	}
	void setParent(void* parent)
	{
		_setParent(this, parent);
	}
	void setBackground(symbolColor _textFone)
	{
		background = _textFone;
	}

	point getPos()
	{
		return pos;
	}
	point getSize()
	{
		return size;
	}
	rectangle getRect()
	{
		return { pos, pos + size };
	}
	void* getParent()
	{
		return parent;
	}
	symbolColor getBackground()
	{
		return background;
	}
};