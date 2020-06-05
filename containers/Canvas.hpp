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
void Canvas_onKeyDown(void* elementPtr, char key);
void Canvas_onKeyUp(void* elementPtr, char key);

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
		onKeyDownSystemDelegate = Canvas_onKeyDown;
		onKeyUpSystemDelegate = Canvas_onKeyUp;

		registerElement();
	}

	void Draw(rectangle& drawFrame)
	{
		rectangle thisElementRect = getRect();
		if (Visible)
			consolePrintRect(drawFrame, thisElementRect, filledCharacter_5_5, collectColor(black, background));

		for (int i = 0; i < childs.count; i++)
		{
			if(childs[i]->Visible)
				childs[i]->Draw(thisElementRect);
		}
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
	if (((controlElement*)elementPtr)->Handled == false)
		return;

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
	if (((controlElement*)elementPtr)->Handled == false)
		return;

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
	if (((controlElement*)elementPtr)->Handled == false)
		return;

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
	if (((controlElement*)elementPtr)->Handled == false)
		return;

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
	if (((controlElement*)elementPtr)->Handled == false)
		return;

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
	if (((controlElement*)elementPtr)->Handled == false)
		return;

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
	if (((controlElement*)elementPtr)->Handled == false)
		return;

	controlElement* onRightButtonUppedElement = Canvas_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (onRightButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonUppedElement->pos;

		callDelegate(onRightButtonUppedElement->onRightButtonUpSystemDelegate, (void*)onRightButtonUppedElement, clickedPosRelativeElement);
		onRightButtonUppedElement->onRightButtonUpEvent.call(onRightButtonUppedElement, clickedPosRelativeElement);
	}
}

void Canvas_onKeyDown(void* elementPtr, char key)
{
	Canvas* container = (Canvas*)elementPtr;

	if (container->Handled == false)
		return;
	
	for (int i = 0; i < container->childs.count; i++)
	{
		controlElement* presentChild = container->childs[i];
		callDelegate(presentChild->onKeyDownSystemDelegate, (void*)presentChild, key);
	}
}

void Canvas_onKeyUp(void* elementPtr, char key)
{
	Canvas* container = (Canvas*)elementPtr;

	if (container->Handled == false)
		return;

	for (int i = 0; i < container->childs.count; i++)
	{
		controlElement* presentChild = container->childs[i];
		callDelegate(presentChild->onKeyUpSystemDelegate, (void*)presentChild, key);
	}
}