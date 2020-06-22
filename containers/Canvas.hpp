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
	dynamicArray<controlElement*> childs;
public:
	Canvas(symbolColor _background = black)
	{
		pos = emptyPoint;
		size = emptyPoint;
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


	//Standart container methods
	void addChild(controlElement& addedChild, point childPos)
	{
		childs.add(&addedChild);
		addedChild.parent = this;
		addedChild.pos = pos + childPos;
	}
	void addChild(controlElement& addedChild)
	{
		addChild(addedChild, { 0, 0 });
	}

	void delChild(controlElement& deletedChild)
	{
		childs.del(&deletedChild);
		deletedChild.parent = NULL;
		deletedChild.pos = { 0, 0 };
	}
	void delChild(point deletedElementPos)
	{
		for (int i = 0; i < childs.count; i++)
		{
			if (childs[i]->entersTheArea(deletedElementPos))
			{
				delChild(*(childs[i]));
			}
		}
	}

	controlElement* getChild(int index)
	{
		return childs[index];
	}
	unsigned int getChildsCount()
	{
		return childs.count;
	}


	//Drawing methods
	void Draw(rectangle& drawFrame)
	{
		rectangle thisElementRect = getRect();
		consolePrintRect(drawFrame, thisElementRect, filledCharacter_5_5, collectColor(black, background));

		for (int i = 0; i < childs.count; i++)
		{
			if(childs[i]->Visible)
				childs[i]->Draw(thisElementRect);
		}
	}
};


//Container events distribution
controlElement* Canvas_getElementsInPos(Canvas* container, point pos)
{
	for (int i = 0; i < container->getChildsCount(); i++)
	{
		controlElement* presentChild = container->getChild(i);
		if (presentChild->entersTheArea(pos))
		{
			return presentChild;
		}
	}

	return NULL;
}

void Canvas_onClick(void* elementPtr, point clickedPos)
{
	Canvas* clickedCanvas = static_cast<Canvas*>(elementPtr);
	controlElement* clickedElement = Canvas_getElementsInPos(clickedCanvas, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate<void*, point>(clickedElement->onClickSystemDelegate, clickedElement, clickedPosRelativeElement);
		clickedElement->onClickEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void Canvas_onFocus(void* elementPtr, point clickedPos)
{
	Canvas* focusedCanvas = static_cast<Canvas*>(elementPtr);
	controlElement* elementInFocus = Canvas_getElementsInPos(focusedCanvas, clickedPos);

	Default_System_OnFocus(elementPtr, clickedPos);

	if (elementInFocus != NULL)
	{
		point clickedPosRelativeElement = clickedPos - elementInFocus->pos;

		callDelegate<void*, point>(elementInFocus->onFocusSystemDelegate, focusedCanvas, clickedPosRelativeElement);
		elementInFocus->onFocusEvent.call(elementInFocus, clickedPosRelativeElement);
	}
}
void Canvas_onFocusLost(void* elementPtr, point clickedPos)
{
	Canvas* focusLostCanvas = static_cast<Canvas*>(elementPtr);

	for (int i = 0; i < focusLostCanvas->getChildsCount(); i++)
	{
		controlElement* presentChild = focusLostCanvas->getChild(i);
		point focusLostPosRelativeElement = clickedPos - presentChild->pos;

		callDelegate<void*, point>(presentChild->onFocusLostSystemDelegate, presentChild, focusLostPosRelativeElement);
		presentChild->onFocusLostEvent.call(presentChild, focusLostPosRelativeElement);
	}
}
void Canvas_onLeftButtonDown(void* elementPtr, point clickedPos)
{
	Canvas* leftButtonDownedCanvas = static_cast<Canvas*>(elementPtr);
	controlElement* onLeftButtonDownedElement = Canvas_getElementsInPos(leftButtonDownedCanvas, clickedPos);

	if (onLeftButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonDownedElement->pos;

		callDelegate<void*, point>(onLeftButtonDownedElement->onLeftButtonDownSystemDelegate, onLeftButtonDownedElement, clickedPosRelativeElement);
		onLeftButtonDownedElement->onLeftButtonDownEvent.call(onLeftButtonDownedElement, clickedPosRelativeElement);
	}
}
void Canvas_onLeftButtonUp(void* elementPtr, point clickedPos)
{
	Canvas* leftButtonUpedCanvas = static_cast<Canvas*>(elementPtr);
	controlElement* onLeftButtonUppedElement = Canvas_getElementsInPos(leftButtonUpedCanvas, clickedPos);

	if (onLeftButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonUppedElement->pos;

		callDelegate<void*, point>(onLeftButtonUppedElement->onLeftButtonUpSystemDelegate, onLeftButtonUppedElement, clickedPosRelativeElement);
		onLeftButtonUppedElement->onLeftButtonUpEvent.call(onLeftButtonUppedElement, clickedPosRelativeElement);
	}
}
void Canvas_onRightButtonDown(void* elementPtr, point clickedPos)
{
	Canvas* rightButtonDownedCanvas = static_cast<Canvas*>(elementPtr);
	controlElement* onRightButtonDownedElement = Canvas_getElementsInPos(rightButtonDownedCanvas, clickedPos);

	if (onRightButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonDownedElement->pos;

		callDelegate<void*, point>(onRightButtonDownedElement->onRightButtonDownSystemDelegate, onRightButtonDownedElement, clickedPosRelativeElement);
		onRightButtonDownedElement->onRightButtonDownEvent.call(onRightButtonDownedElement, clickedPosRelativeElement);
	}
}
void Canvas_onRightButtonUp(void* elementPtr, point clickedPos)
{
	Canvas* rightButtonUpedCanvas = static_cast<Canvas*>(elementPtr);
	controlElement* onRightButtonUppedElement = Canvas_getElementsInPos(rightButtonUpedCanvas, clickedPos);

	if (onRightButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonUppedElement->pos;

		callDelegate<void*, point>(onRightButtonUppedElement->onRightButtonUpSystemDelegate, onRightButtonUppedElement, clickedPosRelativeElement);
		onRightButtonUppedElement->onRightButtonUpEvent.call(onRightButtonUppedElement, clickedPosRelativeElement);
	}
}

void Canvas_onKeyDown(void* elementPtr, char key)
{
	Canvas* keyDownedCanvas = static_cast<Canvas*>(elementPtr);
	
	for (int i = 0; i < keyDownedCanvas->getChildsCount(); i++)
	{
		controlElement* presentChild = keyDownedCanvas->getChild(i);
		callDelegate<void*, char>(presentChild->onKeyDownSystemDelegate, presentChild, key);
	}
}

void Canvas_onKeyUp(void* elementPtr, char key)
{
	Canvas* keyUpedCanvas = static_cast<Canvas*>(elementPtr);

	for (int i = 0; i < keyUpedCanvas->getChildsCount(); i++)
	{
		controlElement* presentChild = keyUpedCanvas->getChild(i);
		callDelegate<void*, char>(presentChild->onKeyUpSystemDelegate, presentChild, key);
	}
}