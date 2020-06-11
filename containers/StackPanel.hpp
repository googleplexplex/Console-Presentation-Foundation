#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"


void StackPanel_onFocus(void* elementPtr, point clickedPos);
void StackPanel_onFocusLost(void* elementPtr, point clickedPos);
void StackPanel_onClick(void* elementPtr, point clickedPos);
void StackPanel_onLeftButtonDown(void* elementPtr, point clickedPos);
void StackPanel_onLeftButtonUp(void* elementPtr, point clickedPos);
void StackPanel_onRightButtonDown(void* elementPtr, point clickedPos);
void StackPanel_onRightButtonUp(void* elementPtr, point clickedPos);
void StackPanel_onKeyDown(void* elementPtr, char key);
void StackPanel_onKeyUp(void* elementPtr, char key);

typedef enum stackPanelOrientationEnum
{
	Vertical = 0,
	Horizontal
};

class StackPanel : public containerElement {
	dynamicArray<controlElement*> childs;
public:
	stackPanelOrientationEnum stackPanelOrientation;
	identifySetterOf(stackPanelOrientation)
	identifyGetterOf(stackPanelOrientation)
	StackPanel(point _pos, point _size, stackPanelOrientationEnum _stackPanelOrientation = Vertical, symbolColor _background = black)
	{
		pos = _pos;
		size = _size;
		stackPanelOrientation = _stackPanelOrientation;
		background = _background;

		onFocusSystemDelegate = StackPanel_onFocus;
		onFocusLostSystemDelegate = StackPanel_onFocusLost;
		onClickSystemDelegate = StackPanel_onClick;
		onLeftButtonDownSystemDelegate = StackPanel_onLeftButtonDown;
		onLeftButtonUpSystemDelegate = StackPanel_onLeftButtonUp;
		onRightButtonDownSystemDelegate = StackPanel_onRightButtonDown;
		onRightButtonUpSystemDelegate = StackPanel_onRightButtonUp;
		onKeyDownSystemDelegate = StackPanel_onKeyDown;
		onKeyUpSystemDelegate = StackPanel_onKeyUp;

		registerElement();
	}

	void addChild(controlElement* addedChild)
	{
		childs.add(addedChild);
		addedChild->parent = this;
	}

	void delChild(controlElement* deletedChild)
	{
		childs.del(deletedChild);
		deletedChild->parent = NULL;
	}

	controlElement* getChild(int index)
	{
		return childs[index];
	}

	unsigned int getChildsCount()
	{
		return childs.count;
	}

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
	void addControlElement(controlElement* element)
	{
		addChild(element);
		updatePositions();
	}
	void addElement(int rowIndex)
	{
		addControlElement(childs[rowIndex]);
	}
	void delControlElement(controlElement* element)
	{
		delChild(element);
		updatePositions();
	}
	void delElement(int rowIndex)
	{
		delControlElement(childs[rowIndex]);
	}

	int getRowsCount()
	{
		return childs.count;
	}
	controlElement* getRowElement(int rowIndex)
	{
		return childs[rowIndex];
	}
};

controlElement* StackPanel_getElementsInPos(containerElement* container, point pos)
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

void StackPanel_onClick(void* elementPtr, point clickedPos)
{
	StackPanel* clickedStackPanel = static_cast<StackPanel*>(elementPtr);
	controlElement* clickedElement = StackPanel_getElementsInPos(clickedStackPanel, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate<void*, point>(clickedElement->onClickSystemDelegate, clickedElement, clickedPosRelativeElement);
		clickedElement->onClickEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void StackPanel_onFocus(void* elementPtr, point clickedPos)
{
	StackPanel* focusedStackPanel = static_cast<StackPanel*>(elementPtr);
	controlElement* elementInFocus = StackPanel_getElementsInPos(focusedStackPanel, clickedPos);

	Default_System_OnFocus(elementPtr, clickedPos);

	if (elementInFocus != NULL)
	{
		point clickedPosRelativeElement = clickedPos - elementInFocus->pos;

		callDelegate<void*, point>(elementInFocus->onFocusSystemDelegate, elementInFocus, clickedPosRelativeElement);
		elementInFocus->onFocusEvent.call(elementInFocus, clickedPosRelativeElement);
	}
}
void StackPanel_onFocusLost(void* elementPtr, point clickedPos)
{
	StackPanel* focusLostedStackPanel = static_cast<StackPanel*>(elementPtr);

	for (int i = 0; i < focusLostedStackPanel->getChildsCount(); i++)
	{
		controlElement* presentChild = focusLostedStackPanel->getChild(i);
		point focusLostPosRelativeElement = clickedPos - presentChild->pos;

		callDelegate<void*, point>(presentChild->onFocusLostSystemDelegate, presentChild, focusLostPosRelativeElement);
		presentChild->onFocusLostEvent.call(presentChild, focusLostPosRelativeElement);
	}
}
void StackPanel_onLeftButtonDown(void* elementPtr, point clickedPos)
{
	StackPanel* leftButtonDownedStackPanel = static_cast<StackPanel*>(elementPtr);
	controlElement* onLeftButtonDownedElement = StackPanel_getElementsInPos(leftButtonDownedStackPanel, clickedPos);

	if (onLeftButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonDownedElement->pos;

		callDelegate<void*, point>(onLeftButtonDownedElement->onLeftButtonDownSystemDelegate, onLeftButtonDownedElement, clickedPosRelativeElement);
		onLeftButtonDownedElement->onLeftButtonDownEvent.call(onLeftButtonDownedElement, clickedPosRelativeElement);
	}
}
void StackPanel_onLeftButtonUp(void* elementPtr, point clickedPos)
{
	StackPanel* leftButtonUpedStackPanel = static_cast<StackPanel*>(elementPtr);
	controlElement* onLeftButtonUppedElement = StackPanel_getElementsInPos(leftButtonUpedStackPanel, clickedPos);

	if (onLeftButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonUppedElement->pos;

		callDelegate<void*, point>(onLeftButtonUppedElement->onLeftButtonUpSystemDelegate, onLeftButtonUppedElement, clickedPosRelativeElement);
		onLeftButtonUppedElement->onLeftButtonUpEvent.call(onLeftButtonUppedElement, clickedPosRelativeElement);
	}
}
void StackPanel_onRightButtonDown(void* elementPtr, point clickedPos)
{
	StackPanel* rightButtonDownedStackPanel = static_cast<StackPanel*>(elementPtr);
	controlElement* onRightButtonDownedElement = StackPanel_getElementsInPos(rightButtonDownedStackPanel, clickedPos);

	if (onRightButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonDownedElement->pos;

		callDelegate<void*, point>(onRightButtonDownedElement->onRightButtonDownSystemDelegate, onRightButtonDownedElement, clickedPosRelativeElement);
		onRightButtonDownedElement->onRightButtonDownEvent.call(onRightButtonDownedElement, clickedPosRelativeElement);
	}
}
void StackPanel_onRightButtonUp(void* elementPtr, point clickedPos)
{
	StackPanel* rightButtonUpedStackPanel = static_cast<StackPanel*>(elementPtr);
	controlElement* onRightButtonUppedElement = StackPanel_getElementsInPos(rightButtonUpedStackPanel, clickedPos);

	if (onRightButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonUppedElement->pos;

		callDelegate<void*, point>(onRightButtonUppedElement->onRightButtonUpSystemDelegate, onRightButtonUppedElement, clickedPosRelativeElement);
		onRightButtonUppedElement->onRightButtonUpEvent.call(onRightButtonUppedElement, clickedPosRelativeElement);
	}
}

void StackPanel_onKeyDown(void* elementPtr, char key)
{
	StackPanel* keyDownedStackPanel = static_cast<StackPanel*>(elementPtr);

	for (int i = 0; i < keyDownedStackPanel->getChildsCount(); i++)
	{
		controlElement* presentChild = keyDownedStackPanel->getChild(i);
		callDelegate<void*, char>(presentChild->onKeyDownSystemDelegate, presentChild, key);
	}
}

void StackPanel_onKeyUp(void* elementPtr, char key)
{
	StackPanel* keyUpedStackPanel = static_cast<StackPanel*>(elementPtr);

	for (int i = 0; i < keyUpedStackPanel->getChildsCount(); i++)
	{
		controlElement* presentChild = keyUpedStackPanel->getChild(i);
		callDelegate(presentChild->onKeyUpSystemDelegate, (void*)presentChild, key);
	}
}