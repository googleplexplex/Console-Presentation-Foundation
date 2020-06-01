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
	/*void addEmptyRow()
	{
		addChild((controlElement*)NULL);
	}*/
	void addElement(int rowIndex)
	{
		addControlElement(childs[rowIndex]);
	}
	/*void setElement(controlElement* element, int rowIndex)
	{
		//...
	}*/
	void delControlElement(controlElement* element)
	{
		delChild(element);
		updatePositions();
	}
	/*void delRow(int rowIndex)
	{
		delChild(childs[rowIndex]);
	}*/
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
	for (int i = 0; i < container->childs.count; i++)
	{
		if (container->childs[i]->entersTheArea(pos))
		{
			return container->childs[i];
		}
	}

	return NULL;
}

void StackPanel_onClick(void* elementPtr, point clickedPos)
{
	controlElement* clickedElement = StackPanel_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate(clickedElement->onClickSystemDelegate, (void*)clickedElement, clickedPosRelativeElement);
		clickedElement->onClickEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void StackPanel_onFocus(void* elementPtr, point clickedPos)
{
	Default_System_OnFocus(elementPtr, clickedPos);

	controlElement* elementInFocus = StackPanel_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (elementInFocus != NULL)
	{
		point clickedPosRelativeElement = clickedPos - elementInFocus->pos;

		callDelegate(elementInFocus->onFocusSystemDelegate, (void*)elementInFocus, clickedPosRelativeElement);
		elementInFocus->onFocusEvent.call(elementInFocus, clickedPosRelativeElement);
	}
}
void StackPanel_onFocusLost(void* elementPtr, point clickedPos)
{
	StackPanel* stackPanelPtr = (StackPanel*)elementPtr;
	for (int i = 0; i < stackPanelPtr->childs.count; i++)
	{
		controlElement* presentChild = stackPanelPtr->childs[i];
		point focusLostPosRelativeElement = clickedPos - presentChild->pos;

		callDelegate(presentChild->onFocusLostSystemDelegate, (void*)presentChild, focusLostPosRelativeElement);
		presentChild->onFocusLostEvent.call(presentChild, focusLostPosRelativeElement);
	}
}
void StackPanel_onLeftButtonDown(void* elementPtr, point clickedPos)
{
	controlElement* onLeftButtonDownedElement = StackPanel_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (onLeftButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonDownedElement->pos;

		callDelegate(onLeftButtonDownedElement->onLeftButtonDownSystemDelegate, (void*)onLeftButtonDownedElement, clickedPosRelativeElement);
		onLeftButtonDownedElement->onLeftButtonDownEvent.call(onLeftButtonDownedElement, clickedPosRelativeElement);
	}
}
void StackPanel_onLeftButtonUp(void* elementPtr, point clickedPos)
{
	controlElement* onLeftButtonUppedElement = StackPanel_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (onLeftButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonUppedElement->pos;

		callDelegate(onLeftButtonUppedElement->onLeftButtonUpSystemDelegate, (void*)onLeftButtonUppedElement, clickedPosRelativeElement);
		onLeftButtonUppedElement->onLeftButtonUpEvent.call(onLeftButtonUppedElement, clickedPosRelativeElement);
	}
}
void StackPanel_onRightButtonDown(void* elementPtr, point clickedPos)
{
	controlElement* onRightButtonDownedElement = StackPanel_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (onRightButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonDownedElement->pos;

		callDelegate(onRightButtonDownedElement->onRightButtonDownSystemDelegate, (void*)onRightButtonDownedElement, clickedPosRelativeElement);
		onRightButtonDownedElement->onRightButtonDownEvent.call(onRightButtonDownedElement, clickedPosRelativeElement);
	}
}
void StackPanel_onRightButtonUp(void* elementPtr, point clickedPos)
{
	controlElement* onRightButtonUppedElement = StackPanel_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (onRightButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonUppedElement->pos;

		callDelegate(onRightButtonUppedElement->onRightButtonUpSystemDelegate, (void*)onRightButtonUppedElement, clickedPosRelativeElement);
		onRightButtonUppedElement->onRightButtonUpEvent.call(onRightButtonUppedElement, clickedPosRelativeElement);
	}
}

void StackPanel_onKeyDown(void* elementPtr, char key)
{
	StackPanel* container = (StackPanel*)elementPtr;

	for (int i = 0; i < container->childs.count; i++)
	{
		controlElement* presentChild = container->childs[i];
		callDelegate(presentChild->onKeyDownSystemDelegate, (void*)presentChild, key);
	}
}

void StackPanel_onKeyUp(void* elementPtr, char key)
{
	StackPanel* container = (StackPanel*)elementPtr;

	for (int i = 0; i < container->childs.count; i++)
	{
		controlElement* presentChild = container->childs[i];
		callDelegate(presentChild->onKeyUpSystemDelegate, (void*)presentChild, key);
	}
}