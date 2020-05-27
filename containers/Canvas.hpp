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

class Canvas : public containerElement {
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

	void addControlElement(controlElement* element)
	{
		addChild(element);
	}
	void delControlElement(controlElement* element)
	{
		delChild(element);
	}
};

controlElement* Canvas_getElementsInPos(containerElement* container, point pos)
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
	controlElement* clickedElement = Canvas_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate(clickedElement->onClickSystemDelegate, (void*)clickedElement, clickedPosRelativeElement);
		clickedElement->onClickEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void Canvas_onFocus(void* elementPtr, point clickedPos)
{
	Default_System_OnFocus(elementPtr, clickedPos);

	controlElement* elementInFocus = Canvas_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (elementInFocus != NULL)
	{
		point clickedPosRelativeElement = clickedPos - elementInFocus->pos;

		callDelegate(elementInFocus->onFocusSystemDelegate, (void*)elementInFocus, clickedPosRelativeElement);
		elementInFocus->onFocusEvent.call(elementInFocus, clickedPosRelativeElement);
	}
}
void Canvas_onFocusLost(void* elementPtr, point clickedPos)
{
	Canvas* canvasPtr = (Canvas*)elementPtr;
	for (int i = 0; i < canvasPtr->childs.count; i++)
	{
		controlElement* presentChild = canvasPtr->childs[i];
		point focusLostPosRelativeElement = clickedPos - presentChild->pos;

		callDelegate(presentChild->onFocusLostSystemDelegate, (void*)presentChild, focusLostPosRelativeElement);
		presentChild->onFocusLostEvent.call(presentChild, focusLostPosRelativeElement);
	}
}
void Canvas_onLeftButtonDown(void* elementPtr, point clickedPos)
{
	controlElement* onLeftButtonDownedElement = Canvas_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (onLeftButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonDownedElement->pos;

		callDelegate(onLeftButtonDownedElement->onLeftButtonDownSystemDelegate, (void*)onLeftButtonDownedElement, clickedPosRelativeElement);
		onLeftButtonDownedElement->onLeftButtonDownEvent.call(onLeftButtonDownedElement, clickedPosRelativeElement);
	}
}
void Canvas_onLeftButtonUp(void* elementPtr, point clickedPos)
{
	controlElement* onLeftButtonUppedElement = Canvas_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (onLeftButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonUppedElement->pos;

		callDelegate(onLeftButtonUppedElement->onLeftButtonUpSystemDelegate, (void*)onLeftButtonUppedElement, clickedPosRelativeElement);
		onLeftButtonUppedElement->onLeftButtonUpEvent.call(onLeftButtonUppedElement, clickedPosRelativeElement);
	}
}
void Canvas_onRightButtonDown(void* elementPtr, point clickedPos)
{
	controlElement* onRightButtonDownedElement = Canvas_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (onRightButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonDownedElement->pos;

		callDelegate(onRightButtonDownedElement->onRightButtonDownSystemDelegate, (void*)onRightButtonDownedElement, clickedPosRelativeElement);
		onRightButtonDownedElement->onRightButtonDownEvent.call(onRightButtonDownedElement, clickedPosRelativeElement);
	}
}
void Canvas_onRightButtonUp(void* elementPtr, point clickedPos)
{
	controlElement* onRightButtonUppedElement = Canvas_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (onRightButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonUppedElement->pos;

		callDelegate(onRightButtonUppedElement->onRightButtonUpSystemDelegate, (void*)onRightButtonUppedElement, clickedPosRelativeElement);
		onRightButtonUppedElement->onRightButtonUpEvent.call(onRightButtonUppedElement, clickedPosRelativeElement);
	}
}