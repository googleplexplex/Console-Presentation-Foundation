#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"


void Canvas_onFocus(void* elementPtr, point clickedPos);
void Canvas_onFocusLost(void* elementPtr, point clickedPos);
void Canvas_onClick(void* elementPtr, point clickedPos);
void Canvas_onLeftButtonDown(void* elementPtr, point clickedPos);
void Canvas_onLeftButtonUp(void* elementPtr, point clickedPos);
void Canvas_onRightButtonDown(void* elementPtr, point clickedPos);
void Canvas_onRightButtonUp(void* elementPtr, point clickedPos);

class Canvas : containerElement {
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

controlElement* getElementsInPos(containerElement* container, point pos)
{
	for (int i = 0; i < container->childs.count; i++)
	{
		if (container->childs[i]->entersTheArea(pos))
		{
			return container->childs[i];
		}
	}

	return NULL;
}

void Canvas_onClick(void* elementPtr, point clickedPos)
{
	controlElement* clickedElement = getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate(clickedElement->onClickSystemDelegate, (void*)clickedElement, clickedPosRelativeElement);
		clickedElement->onClickEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void Canvas_onFocus(void* elementPtr, point clickedPos)
{
	controlElement* clickedElement = getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate(clickedElement->onFocusSystemDelegate, (void*)clickedElement, clickedPosRelativeElement);
		clickedElement->onClickEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void Canvas_onFocusLost(void* elementPtr, point clickedPos)
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