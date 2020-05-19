#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"


void Canvas_onFocus(void* elementPtr);
void Canvas_onFocusLost(void* elementPtr);
void Canvas_onClick(void* elementPtr, point clickedPos);
void Canvas_onLeftButtonDown(void* elementPtr, point clickedPos);
void Canvas_onLeftButtonUp(void* elementPtr, point clickedPos);
void Canvas_onRightButtonDown(void* elementPtr, point clickedPos);
void Canvas_onRightButtonUp(void* elementPtr, point clickedPos);

class Canvas : controlElement {
	dynamicArray<controlElement*> elements;
public:
	Canvas(point _pos, point _size, symbolColor _background = black)
	{
		pos = _pos;
		size = _size;
		background = _background;

		onFocusSystemDelegate = Canvas_onFocus;
		onFocusLostSystemDelegate = Canvas_onFocusLost;
		onClickSystemDelegate = Canvas_onClick;
		onLeftButtonDownSystemDelegate = Canvas_onLeftButtonDown;
		onLeftButtonUpSystemDelegate = Canvas_onLeftButtonUp;
		onRightButtonDownSystemDelegate = Canvas_onRightButtonDown;
		onRightButtonUpSystemDelegate = Canvas_onRightButtonUp;

		registerElement();
	}

	void Draw(rectangle drawFrame)
	{
		consoleCursorInfo save;
		save.getAndReset();

		setSymbolFullColor(background);
		for (int i = 0; i < size.y; i++)
		{
			setTo(pos.x, pos.y + i);
			consolePrintLine(drawFrame, size.x, filledCharacter_5_5);
		}
		setStandartSymbolsColor();

		for (int i = 0; i < childs.count; i++)
		{
			childs[i]->Draw(getRect());
		}

		save.apply();
	}
	bool entersTheArea(point point)
	{
		return getBorder(point.x, pos.x, pos.x + size.x - 1)
			&& getBorder(point.y, pos.y, pos.y + size.y - 1);
	}

	void addControlElement(controlElement* element)
	{
		addChild(element);
	}
	void delControlElement(controlElement* element)
	{
		delChild(element);
	}
};

void Canvas_onClick(void* elementPtr, point clickedPos)
{
	//...
}
void Canvas_onFocus(void* elementPtr)
{
	//...
}
void Canvas_onFocusLost(void* elementPtr)
{
	//...
}
void Canvas_onLeftButtonDown(void* elementPtr, point clickedPos)
{
	//...
}
void Canvas_onLeftButtonUp(void* elementPtr, point clickedPos)
{
	//...
}
void Canvas_onRightButtonDown(void* elementPtr, point clickedPos)
{
	//...
}
void Canvas_onRightButtonUp(void* elementPtr, point clickedPos)
{
	//...
}