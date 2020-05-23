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
	controlElement* clickedElement = StackPanel_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate(clickedElement->onFocusSystemDelegate, (void*)clickedElement, clickedPosRelativeElement);
		clickedElement->onFocusEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void StackPanel_onFocusLost(void* elementPtr, point clickedPos)
{
	controlElement* clickedElement = StackPanel_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate(clickedElement->onFocusLostSystemDelegate, (void*)clickedElement, clickedPosRelativeElement);
		clickedElement->onFocusLostEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void StackPanel_onLeftButtonDown(void* elementPtr, point clickedPos)
{
	controlElement* clickedElement = StackPanel_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate(clickedElement->onLeftButtonDownSystemDelegate, (void*)clickedElement, clickedPosRelativeElement);
		clickedElement->onLeftButtonDownEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void StackPanel_onLeftButtonUp(void* elementPtr, point clickedPos)
{
	controlElement* clickedElement = StackPanel_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate(clickedElement->onLeftButtonUpSystemDelegate, (void*)clickedElement, clickedPosRelativeElement);
		clickedElement->onLeftButtonUpEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void StackPanel_onRightButtonDown(void* elementPtr, point clickedPos)
{
	controlElement* clickedElement = StackPanel_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate(clickedElement->onRightButtonDownSystemDelegate, (void*)clickedElement, clickedPosRelativeElement);
		clickedElement->onRightButtonDownEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void StackPanel_onRightButtonUp(void* elementPtr, point clickedPos)
{
	controlElement* clickedElement = StackPanel_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate(clickedElement->onRightButtonUpSystemDelegate, (void*)clickedElement, clickedPosRelativeElement);
		clickedElement->onRightButtonUpEvent.call(clickedElement, clickedPosRelativeElement);
	}
}