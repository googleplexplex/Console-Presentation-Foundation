#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"


void Grid_onFocus(void* elementPtr, point clickedPos);
void Grid_onFocusLost(void* elementPtr, point clickedPos);
void Grid_onClick(void* elementPtr, point clickedPos);
void Grid_onLeftButtonDown(void* elementPtr, point clickedPos);
void Grid_onLeftButtonUp(void* elementPtr, point clickedPos);
void Grid_onRightButtonDown(void* elementPtr, point clickedPos);
void Grid_onRightButtonUp(void* elementPtr, point clickedPos);
void Grid_onKeyDown(void* elementPtr, char key);
void Grid_onKeyUp(void* elementPtr, char key);

class Grid : public containerElement {
public:
	Grid(point _pos, point _size, symbolColor _background = black)
	{
		pos = _pos;
		size = _size;
		background = _background;

		onFocusSystemDelegate = Grid_onFocus;
		onFocusLostSystemDelegate = Grid_onFocusLost;
		onClickSystemDelegate = Grid_onClick;
		onLeftButtonDownSystemDelegate = Grid_onLeftButtonDown;
		onLeftButtonUpSystemDelegate = Grid_onLeftButtonUp;
		onRightButtonDownSystemDelegate = Grid_onRightButtonDown;
		onRightButtonUpSystemDelegate = Grid_onRightButtonUp;
		onKeyDownSystemDelegate = Grid_onKeyDown;
		onKeyUpSystemDelegate = Grid_onKeyUp;

		registerElement();
	}

	void Draw(rectangle drawFrame)
	{
		consoleCursorInfo save;
		save.getAndReset();

		if (Visible)
		{
			setSymbolFullColor(background);
			for (int i = 0; i < size.y; i++)
			{
				setTo(pos.x, pos.y + i);
				consolePrintLine(drawFrame, size.x, filledCharacter_5_5);
			}
			setStandartSymbolsColor();
		}

		for (int i = 0; i < childs.count; i++)
		{
			if (childs[i]->Visible)
				childs[i]->Draw(getRect());
		}

		save.apply();
	}

	void updatePositions()
	{
		//...
	}

	void addControlElement(controlElement* element, int row, int column)
	{
		//...
		updatePositions();
	}
	void addRow()
	{
		//...
		updatePositions();
	}
	void addColumn()
	{
		//...
		updatePositions();
	}
	void delControlElement(controlElement* element, int row, int column)
	{
		//...
		updatePositions();
	}
	void delRow(int row)
	{
		//...
		updatePositions();
	}
	void delColumn(int column)
	{
		//...
		updatePositions();
	}

	void setRowsCount(int count)
	{
		//...
	}
	void setColumnsCount(int count)
	{
		//...
	}

	int getRowsCount()
	{
		//...
	}
	int getColumnsCount()
	{
		//...
	}
};

controlElement* Grid_getElementsInPos(containerElement* container, point pos)
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

void Grid_onClick(void* elementPtr, point clickedPos)
{
	if (((controlElement*)elementPtr)->Handled == false)
		return;

	controlElement* clickedElement = Grid_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate(clickedElement->onClickSystemDelegate, (void*)clickedElement, clickedPosRelativeElement);
		clickedElement->onClickEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void Grid_onFocus(void* elementPtr, point clickedPos)
{
	if (((controlElement*)elementPtr)->Handled == false)
		return;

	Default_System_OnFocus(elementPtr, clickedPos);

	controlElement* elementInFocus = Grid_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (elementInFocus != NULL)
	{
		point clickedPosRelativeElement = clickedPos - elementInFocus->pos;

		callDelegate(elementInFocus->onFocusSystemDelegate, (void*)elementInFocus, clickedPosRelativeElement);
		elementInFocus->onFocusEvent.call(elementInFocus, clickedPosRelativeElement);
	}
}
void Grid_onFocusLost(void* elementPtr, point clickedPos)
{
	if (((controlElement*)elementPtr)->Handled == false)
		return;

	Grid* GridPtr = (Grid*)elementPtr;
	for (int i = 0; i < GridPtr->childs.count; i++)
	{
		controlElement* presentChild = GridPtr->childs[i];
		point focusLostPosRelativeElement = clickedPos - presentChild->pos;

		callDelegate(presentChild->onFocusLostSystemDelegate, (void*)presentChild, focusLostPosRelativeElement);
		presentChild->onFocusLostEvent.call(presentChild, focusLostPosRelativeElement);
	}
}
void Grid_onLeftButtonDown(void* elementPtr, point clickedPos)
{
	if (((controlElement*)elementPtr)->Handled == false)
		return;

	controlElement* onLeftButtonDownedElement = Grid_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (onLeftButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonDownedElement->pos;

		callDelegate(onLeftButtonDownedElement->onLeftButtonDownSystemDelegate, (void*)onLeftButtonDownedElement, clickedPosRelativeElement);
		onLeftButtonDownedElement->onLeftButtonDownEvent.call(onLeftButtonDownedElement, clickedPosRelativeElement);
	}
}
void Grid_onLeftButtonUp(void* elementPtr, point clickedPos)
{
	if (((controlElement*)elementPtr)->Handled == false)
		return;

	controlElement* onLeftButtonUppedElement = Grid_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (onLeftButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonUppedElement->pos;

		callDelegate(onLeftButtonUppedElement->onLeftButtonUpSystemDelegate, (void*)onLeftButtonUppedElement, clickedPosRelativeElement);
		onLeftButtonUppedElement->onLeftButtonUpEvent.call(onLeftButtonUppedElement, clickedPosRelativeElement);
	}
}
void Grid_onRightButtonDown(void* elementPtr, point clickedPos)
{
	if (((controlElement*)elementPtr)->Handled == false)
		return;

	controlElement* onRightButtonDownedElement = Grid_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (onRightButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonDownedElement->pos;

		callDelegate(onRightButtonDownedElement->onRightButtonDownSystemDelegate, (void*)onRightButtonDownedElement, clickedPosRelativeElement);
		onRightButtonDownedElement->onRightButtonDownEvent.call(onRightButtonDownedElement, clickedPosRelativeElement);
	}
}
void Grid_onRightButtonUp(void* elementPtr, point clickedPos)
{
	if (((controlElement*)elementPtr)->Handled == false)
		return;

	controlElement* onRightButtonUppedElement = Grid_getElementsInPos((containerElement*)elementPtr, clickedPos);

	if (onRightButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonUppedElement->pos;

		callDelegate(onRightButtonUppedElement->onRightButtonUpSystemDelegate, (void*)onRightButtonUppedElement, clickedPosRelativeElement);
		onRightButtonUppedElement->onRightButtonUpEvent.call(onRightButtonUppedElement, clickedPosRelativeElement);
	}
}

void Grid_onKeyDown(void* elementPtr, char key)
{
	Grid* container = (Grid*)elementPtr;

	if (container->Handled == false)
		return;

	for (int i = 0; i < container->childs.count; i++)
	{
		controlElement* presentChild = container->childs[i];
		callDelegate(presentChild->onKeyDownSystemDelegate, (void*)presentChild, key);
	}
}

void Grid_onKeyUp(void* elementPtr, char key)
{
	Grid* container = (Grid*)elementPtr;

	if (container->Handled == false)
		return;

	for (int i = 0; i < container->childs.count; i++)
	{
		controlElement* presentChild = container->childs[i];
		callDelegate(presentChild->onKeyUpSystemDelegate, (void*)presentChild, key);
	}
}