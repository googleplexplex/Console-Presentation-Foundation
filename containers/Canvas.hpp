#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"


void Canvas_Dispatch_onFocus(void* elementPtr, point clickedPos);
void Canvas_Dispatch_onFocusLost(void* elementPtr, point clickedPos);
void Canvas_Dispatch_onClick(void* elementPtr, point clickedPos);
void Canvas_Dispatch_onLeftButtonDown(void* elementPtr, point clickedPos);
void Canvas_Dispatch_onLeftButtonUp(void* elementPtr, point clickedPos);
void Canvas_Dispatch_onRightButtonDown(void* elementPtr, point clickedPos);
void Canvas_Dispatch_onRightButtonUp(void* elementPtr, point clickedPos);
void Canvas_Dispatch_onKeyDown(void* elementPtr, char key);
void Canvas_Dispatch_onKeyUp(void* elementPtr, char key);

class Canvas : public containerElement {
	dynamicArray<controlElement*> childs;
public:
	Canvas(symbolColor _background = black)
	{
		pos = emptyPoint;
		size = emptyPoint;
		background = _background;

		onFocus.add(Canvas_Dispatch_onFocus);
		onFocusLost.add(Canvas_Dispatch_onFocusLost);
		onClick.add(Canvas_Dispatch_onClick);
		onLeftButtonDown.add(Canvas_Dispatch_onLeftButtonDown);
		onLeftButtonUp.add(Canvas_Dispatch_onLeftButtonUp);
		onRightButtonDown.add(Canvas_Dispatch_onRightButtonDown);
		onRightButtonUp.add(Canvas_Dispatch_onRightButtonUp);
		onKeyDown.add(Canvas_Dispatch_onKeyDown);
		onKeyUp.add(Canvas_Dispatch_onKeyUp);
	}


	//Standart container methods
	void addChild(controlElement& addedChild, point childPos)
	{
		childs.add(&addedChild);
		addedChild.parent = this;
		addedChild.pos = pos + childPos;

		setAllTreeInDrawQueue();
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

		setAllTreeInDrawQueue();
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
	void Draw()
	{
		rectangle thisElementRect = getRect();
		consolePrintRect(thisElementRect, filledCharacter_5_5, collectColor(black, background));

		for (int i = 0; i < childs.count; i++)
		{
			if (childs[i]->Visible && childs[i]->needToDraw)
			{
				childs[i]->beforeDraw.call(childs[i]);
				childs[i]->Draw();
				childs[i]->afterDraw.call(childs[i]);
			}
		}

		needToDraw = false;
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

void Canvas_Dispatch_onClick(void* elementPtr, point clickedPos)
{
	Canvas* clickedCanvas = static_cast<Canvas*>(elementPtr);
	controlElement* clickedElement = Canvas_getElementsInPos(clickedCanvas, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		clickedElement->onClick.call(clickedElement, clickedPosRelativeElement);
	}
}
void Canvas_Dispatch_onFocus(void* elementPtr, point clickedPos)
{
	Canvas* focusedCanvas = static_cast<Canvas*>(elementPtr);
	controlElement* elementInFocus = Canvas_getElementsInPos(focusedCanvas, clickedPos);

	Default_System_OnFocus(elementPtr, clickedPos);

	if (elementInFocus != NULL)
	{
		point clickedPosRelativeElement = clickedPos - elementInFocus->pos;

		elementInFocus->onFocus.call(elementInFocus, clickedPosRelativeElement);
	}
}
void Canvas_Dispatch_onFocusLost(void* elementPtr, point clickedPos)
{
	Canvas* focusLostCanvas = static_cast<Canvas*>(elementPtr);

	for (int i = 0; i < focusLostCanvas->getChildsCount(); i++)
	{
		controlElement* presentChild = focusLostCanvas->getChild(i);
		point focusLostPosRelativeElement = clickedPos - presentChild->pos;

		presentChild->onFocusLost.call(presentChild, focusLostPosRelativeElement);
	}
}
void Canvas_Dispatch_onLeftButtonDown(void* elementPtr, point clickedPos)
{
	Canvas* leftButtonDownedCanvas = static_cast<Canvas*>(elementPtr);
	controlElement* onLeftButtonDownedElement = Canvas_getElementsInPos(leftButtonDownedCanvas, clickedPos);

	if (onLeftButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonDownedElement->pos;

		onLeftButtonDownedElement->onLeftButtonDown.call(onLeftButtonDownedElement, clickedPosRelativeElement);
	}
}
void Canvas_Dispatch_onLeftButtonUp(void* elementPtr, point clickedPos)
{
	Canvas* leftButtonUpedCanvas = static_cast<Canvas*>(elementPtr);
	controlElement* onLeftButtonUppedElement = Canvas_getElementsInPos(leftButtonUpedCanvas, clickedPos);

	if (onLeftButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonUppedElement->pos;

		onLeftButtonUppedElement->onLeftButtonUp.call(onLeftButtonUppedElement, clickedPosRelativeElement);
	}
}
void Canvas_Dispatch_onRightButtonDown(void* elementPtr, point clickedPos)
{
	Canvas* rightButtonDownedCanvas = static_cast<Canvas*>(elementPtr);
	controlElement* onRightButtonDownedElement = Canvas_getElementsInPos(rightButtonDownedCanvas, clickedPos);

	if (onRightButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonDownedElement->pos;

		onRightButtonDownedElement->onRightButtonDown.call(onRightButtonDownedElement, clickedPosRelativeElement);
	}
}
void Canvas_Dispatch_onRightButtonUp(void* elementPtr, point clickedPos)
{
	Canvas* rightButtonUpedCanvas = static_cast<Canvas*>(elementPtr);
	controlElement* onRightButtonUppedElement = Canvas_getElementsInPos(rightButtonUpedCanvas, clickedPos);

	if (onRightButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonUppedElement->pos;

		onRightButtonUppedElement->onRightButtonUp.call(onRightButtonUppedElement, clickedPosRelativeElement);
	}
}

void Canvas_Dispatch_onKeyDown(void* elementPtr, char key)
{
	Canvas* keyDownedCanvas = static_cast<Canvas*>(elementPtr);
	
	for (int i = 0; i < keyDownedCanvas->getChildsCount(); i++)
	{
		controlElement* presentChild = keyDownedCanvas->getChild(i);

		presentChild->onKeyDown.call(presentChild, key);
	}
}

void Canvas_Dispatch_onKeyUp(void* elementPtr, char key)
{
	Canvas* keyUpedCanvas = static_cast<Canvas*>(elementPtr);

	for (int i = 0; i < keyUpedCanvas->getChildsCount(); i++)
	{
		controlElement* presentChild = keyUpedCanvas->getChild(i);

		presentChild->onKeyUp.call(presentChild, key);
	}
}
