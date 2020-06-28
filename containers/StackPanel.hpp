#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"


void StackPanel_Dispatch_onFocus(void* elementPtr, point clickedPos);
void StackPanel_Dispatch_onFocusLost(void* elementPtr, point clickedPos);
void StackPanel_Dispatch_onClick(void* elementPtr, point clickedPos);
void StackPanel_Dispatch_onLeftButtonDown(void* elementPtr, point clickedPos);
void StackPanel_Dispatch_onLeftButtonUp(void* elementPtr, point clickedPos);
void StackPanel_Dispatch_onRightButtonDown(void* elementPtr, point clickedPos);
void StackPanel_Dispatch_onRightButtonUp(void* elementPtr, point clickedPos);
void StackPanel_Dispatch_onKeyDown(void* elementPtr, char key);
void StackPanel_Dispatch_onKeyUp(void* elementPtr, char key);
void StackPanel_Dispatch_beforeDraw(void* elementPtr);
void StackPanel_Dispatch_afterDraw(void* elementPtr);

typedef enum stackPanelOrientationEnum
{
	Vertical = 0,
	Horizontal
};

class StackPanel : public containerElement {
	dynamicArray<controlElement*> childs;
public:
	stackPanelOrientationEnum stackPanelOrientation;
	StackPanel(stackPanelOrientationEnum _stackPanelOrientation = Vertical, symbolColor _background = black)
	{
		pos = emptyPoint;
		size = emptyPoint;
		stackPanelOrientation = _stackPanelOrientation;
		background = _background;

		onFocus += StackPanel_Dispatch_onFocus;
		onFocusLost += StackPanel_Dispatch_onFocusLost;
		onClick += StackPanel_Dispatch_onClick;
		onLeftButtonDown += StackPanel_Dispatch_onLeftButtonDown;
		onLeftButtonUp += StackPanel_Dispatch_onLeftButtonUp;
		onRightButtonDown += StackPanel_Dispatch_onRightButtonDown;
		onRightButtonUp += StackPanel_Dispatch_onRightButtonUp;
		onKeyDown += StackPanel_Dispatch_onKeyDown;
		onKeyUp += StackPanel_Dispatch_onKeyUp;
		beforeDraw += StackPanel_Dispatch_beforeDraw;
		afterDraw += StackPanel_Dispatch_afterDraw;
	}


	//Standart container methods
	void addChild(controlElement& addedChild)
	{
		childs.add(&addedChild);
		addedChild.parent = this;

		updatePositions();
		setAllTreeInDrawQueue();
	}

	void delChild(unsigned int index)
	{
		childs[index]->parent = NULL;
		childs.delElementIn(index);

		updatePositions();
		setAllTreeInDrawQueue();
	}
	void delChild(controlElement& deletedChild)
	{
		childs.del(&deletedChild);
		deletedChild.parent = NULL;

		updatePositions();
		setAllTreeInDrawQueue();
	}
	void delChild(point childPos)
	{
		for (int i = 0; i < childs.count; i++)
		{
			if (childs[i]->entersTheArea(childPos))
			{
				delChild(*(childs[i]));

				setAllTreeInDrawQueue();
				return;
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
			if(childs[i]->Visible && childs[i]->needToDraw)
				childs[i]->Draw(thisElementRect);
		}

		needToDraw = false;
	}


	//Distribution to elements of their position
	void updatePositions()
	{
		if (stackPanelOrientation == Vertical)
		{
			point posPresentChild = pos;
			for (int i = 0; i < childs.count; i++)
			{
				posPresentChild.x = size.x / 2 - childs[i]->size.x / 2;
				childs[i]->pos = posPresentChild;
				posPresentChild.y += childs[i]->size.y;
			}
		}
		else { //stackPanelOrientation == Horizontal
			point posPresentChild = pos;
			for (int i = 0; i < childs.count; i++)
			{
				posPresentChild.y = size.y / 2 - childs[i]->size.y / 2;
				childs[i]->pos = posPresentChild;
				posPresentChild.x += childs[i]->size.x;
			}
		}
	}
};


//Container events distribution
controlElement* StackPanel_getElementsInPos(StackPanel* container, point pos)
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

void StackPanel_Dispatch_onClick(void* elementPtr, point clickedPos)
{
	StackPanel* clickedStackPanel = static_cast<StackPanel*>(elementPtr);
	controlElement* clickedElement = StackPanel_getElementsInPos(clickedStackPanel, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		clickedElement->onClick.call(clickedElement, clickedPosRelativeElement);
	}
}
void StackPanel_Dispatch_onFocus(void* elementPtr, point clickedPos)
{
	StackPanel* focusedStackPanel = static_cast<StackPanel*>(elementPtr);
	controlElement* elementInFocus = StackPanel_getElementsInPos(focusedStackPanel, clickedPos);

	Default_System_OnFocus(elementPtr, clickedPos);

	if (elementInFocus != NULL)
	{
		point clickedPosRelativeElement = clickedPos - elementInFocus->pos;

		elementInFocus->onFocus.call(elementInFocus, clickedPosRelativeElement);
	}
}
void StackPanel_Dispatch_onFocusLost(void* elementPtr, point clickedPos)
{
	StackPanel* focusLostedStackPanel = static_cast<StackPanel*>(elementPtr);

	for (int i = 0; i < focusLostedStackPanel->getChildsCount(); i++)
	{
		controlElement* presentChild = focusLostedStackPanel->getChild(i);
		point focusLostPosRelativeElement = clickedPos - presentChild->pos;

		presentChild->onFocusLost.call(presentChild, focusLostPosRelativeElement);
	}
}
void StackPanel_Dispatch_onLeftButtonDown(void* elementPtr, point clickedPos)
{
	StackPanel* leftButtonDownedStackPanel = static_cast<StackPanel*>(elementPtr);
	controlElement* onLeftButtonDownedElement = StackPanel_getElementsInPos(leftButtonDownedStackPanel, clickedPos);

	if (onLeftButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonDownedElement->pos;

		onLeftButtonDownedElement->onLeftButtonDown.call(onLeftButtonDownedElement, clickedPosRelativeElement);
	}
}
void StackPanel_Dispatch_onLeftButtonUp(void* elementPtr, point clickedPos)
{
	StackPanel* leftButtonUpedStackPanel = static_cast<StackPanel*>(elementPtr);
	controlElement* onLeftButtonUppedElement = StackPanel_getElementsInPos(leftButtonUpedStackPanel, clickedPos);

	if (onLeftButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonUppedElement->pos;

		onLeftButtonUppedElement->onLeftButtonUp.call(onLeftButtonUppedElement, clickedPosRelativeElement);
	}
}
void StackPanel_Dispatch_onRightButtonDown(void* elementPtr, point clickedPos)
{
	StackPanel* rightButtonDownedStackPanel = static_cast<StackPanel*>(elementPtr);
	controlElement* onRightButtonDownedElement = StackPanel_getElementsInPos(rightButtonDownedStackPanel, clickedPos);

	if (onRightButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonDownedElement->pos;

		onRightButtonDownedElement->onRightButtonDown.call(onRightButtonDownedElement, clickedPosRelativeElement);
	}
}
void StackPanel_Dispatch_onRightButtonUp(void* elementPtr, point clickedPos)
{
	StackPanel* rightButtonUpedStackPanel = static_cast<StackPanel*>(elementPtr);
	controlElement* onRightButtonUppedElement = StackPanel_getElementsInPos(rightButtonUpedStackPanel, clickedPos);

	if (onRightButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonUppedElement->pos;

		onRightButtonUppedElement->onRightButtonUp.call(onRightButtonUppedElement, clickedPosRelativeElement);
	}
}

void StackPanel_Dispatch_onKeyDown(void* elementPtr, char key)
{
	StackPanel* keyDownedStackPanel = static_cast<StackPanel*>(elementPtr);

	for (int i = 0; i < keyDownedStackPanel->getChildsCount(); i++)
	{
		controlElement* presentChild = keyDownedStackPanel->getChild(i);

		presentChild->onKeyDown.call(presentChild, key);
	}
}

void StackPanel_Dispatch_onKeyUp(void* elementPtr, char key)
{
	StackPanel* keyUpedStackPanel = static_cast<StackPanel*>(elementPtr);

	for (int i = 0; i < keyUpedStackPanel->getChildsCount(); i++)
	{
		controlElement* presentChild = keyUpedStackPanel->getChild(i);

		presentChild->onKeyUp.call(presentChild, key);
	}
}

void StackPanel_Dispatch_beforeDraw(void* elementPtr)
{
	StackPanel* keyUpedStackPanel = static_cast<StackPanel*>(elementPtr);

	for (int i = 0; i < keyUpedStackPanel->getChildsCount(); i++)
	{
		controlElement* presentChild = keyUpedStackPanel->getChild(i);

		presentChild->beforeDraw.call(presentChild);
	}
}

void StackPanel_Dispatch_afterDraw(void* elementPtr)
{
	StackPanel* keyUpedStackPanel = static_cast<StackPanel*>(elementPtr);

	for (int i = 0; i < keyUpedStackPanel->getChildsCount(); i++)
	{
		controlElement* presentChild = keyUpedStackPanel->getChild(i);

		presentChild->afterDraw.call(presentChild);
	}
}