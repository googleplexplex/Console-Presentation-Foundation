#pragma once
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"

#define getBorder(val, min, max) ((val) > (min) && (max) > (val))

void _setParent(void* _child, void* _parent);

//Control Element Interface
class controlElement
{
public:
	point pos;
	point size;
public:
	bool Visible = true;
	bool Handled = true;
	void* parent;
	symbolColor background;

	onFocus_EventType onFocus;
	onFocusLost_EventType onFocusLost;
	onClick_EventType onClick;
	onLeftButtonDown_EventType onLeftButtonDown;
	onLeftButtonUp_EventType onLeftButtonUp;
	onRightButtonDown_EventType onRightButtonDown;
	onRightButtonUp_EventType onRightButtonUp;
	onKeyDown_EventType onKeyDown;
	onKeyUp_EventType onKeyUp;

	virtual void Draw(rectangle& drawFrame) = 0;
	bool entersTheArea(point point)
	{
		return getBorder(point.x, pos.x, pos.x + size.x - 1)
			&& getBorder(point.y, pos.y, pos.y + size.y - 1);
	}

	void setParent(controlElement* parent)
	{
		_setParent(this, parent);
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
};