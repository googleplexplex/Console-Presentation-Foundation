#pragma once
#include "helpers\dynamicArray.hpp"
#include "helpers\helpFunctions.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"

void _setParent(void* _child, void* _parent);
class controlElement
{
public:
	point pos;
	point size;
	bool Visible = true;
	bool Handled = true;
	void* parent;
	symbolColor background;

	onFocus_DelegateType onFocusSystemDelegate = NULL;
	onFocusLost_DelegateType onFocusLostSystemDelegate = NULL;
	onClick_DelegateType onClickSystemDelegate = NULL;
	onLeftButtonDown_DelegateType onLeftButtonDownSystemDelegate = NULL;
	onLeftButtonUp_DelegateType onLeftButtonUpSystemDelegate = NULL;
	onRightButtonDown_DelegateType onRightButtonDownSystemDelegate = NULL;
	onRightButtonUp_DelegateType onRightButtonUpSystemDelegate = NULL;
	onKeyDown_DelegateType onKeyDownSystemDelegate = NULL;
	onKeyUp_DelegateType onKeyUpSystemDelegate = NULL;

	onFocus_EventType onFocusEvent;
	onFocusLost_EventType onFocusLostEvent;
	onClick_EventType onClickEvent;
	onLeftButtonDown_EventType onLeftButtonDownEvent;
	onLeftButtonUp_EventType onLeftButtonUpEvent;
	onRightButtonDown_EventType onRightButtonDownEvent;
	onRightButtonUp_EventType onRightButtonUpEvent;
	onKeyDown_EventType onKeyDownEvent;
	onKeyUp_EventType onKeyUpEvent;

	void registerElement()
	{
		addElementZone(getRect());
	}

	virtual void Draw(rectangle& drawFrame) = 0;
	bool entersTheArea(point point)
	{
		return getBorder(point.x, pos.x, pos.x + size.x - 1)
			&& getBorder(point.y, pos.y, pos.y + size.y - 1);
	}

	void setPos(unsigned int x, unsigned int y)
	{
		pos.x = x;
		pos.y = y;
	}
	void setSize(unsigned int x, unsigned int y)
	{
		size.x = x;
		size.y = y;
	}
	void setParent(controlElement* parent)
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