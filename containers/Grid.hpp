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
	dynamicArray<dynamicArray<controlElement*>> elements;
	point oneElementSize;
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

	void addChild(controlElement* addedChild)
	{

	}

	void delChild(controlElement* deleteddChild)
	{

	}

	controlElement* getChild(int index)
	{
		return NULL;
	}

	unsigned int getChildsCount()
	{
		return 0;
	}

	void Draw(rectangle& drawFrame)
	{
		rectangle thisElementRect = getRect();
		consolePrintRect(drawFrame, thisElementRect, filledCharacter_5_5, collectColor(black, background));

		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (elements[i][j] != NULL && elements[i][j]->Visible)
					elements[i][j]->Draw(thisElementRect);
			}
		}
	}

	void updatePositions()
	{
		oneElementSize = { size.x / getColumnsCount(), size.y / getRowsCount() };
		point presentPos;

		for (int i = 0; i < getRowsCount(); i++)
		{
			presentPos = pos;
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (elements[i][j] != NULL)
				{
					elements[i][j]->pos = presentPos;
					elements[i][j]->size = oneElementSize;
				}

				pos.x += oneElementSize.x;
			}
		}
	}

	int getRowsCount()
	{
		return elements.count;
	}
	int getColumnsCount()
	{
		return elements[0].count;
	}

	void addRow()
	{
		dynamicArray<controlElement*> addedRow;
		addedRow.add(NULL, getRowsCount() + 1);
		elements.add(addedRow);
		updatePositions();
	}
	void addColumn()
	{
		for (int i = 0; i < getRowsCount(); i++)
		{
			elements[i].add(NULL);
		}
		updatePositions();
	}
	void addControlElement(controlElement& element, int row, int column)
	{
		elements[row][column] = &element;
	}

	void delControlElement(int row, int column)
	{
		elements[row][column] = NULL;
	}
	void delRow(int rowIndex)
	{
		elements.del(rowIndex);
		updatePositions();
	}
	void delColumn(int columnIndex)
	{
		for (int i = 0; i < getRowsCount(); i++)
		{
			elements[i].del(columnIndex);
		}
		updatePositions();
	}
};

controlElement* Grid_getElementsInPos(containerElement* container, point pos)
{
	Grid* clickedGrid = static_cast<Grid*>(container);

	for (int i = 0; i < clickedGrid->getRowsCount(); i++)
	{
		for (int j = 0; j < clickedGrid->getColumnsCount(); j++)
		{
			if (clickedGrid->elements[i][j] != NULL && clickedGrid->elements[i][j]->entersTheArea(pos))
			{
				return clickedGrid->elements[i][j];
			}
		}
	}

	return NULL;
}

void Grid_onClick(void* elementPtr, point clickedPos)
{
	Grid* clickedGrid = static_cast<Grid*>(elementPtr);
	controlElement* clickedElement = Grid_getElementsInPos(clickedGrid, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate<void*, point>(clickedElement->onClickSystemDelegate, clickedElement, clickedPosRelativeElement);
		clickedElement->onClickEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void Grid_onFocus(void* elementPtr, point clickedPos)
{
	Grid* focusedGrid = static_cast<Grid*>(elementPtr);
	controlElement* elementInFocus = Grid_getElementsInPos(focusedGrid, clickedPos);

	Default_System_OnFocus(elementPtr, clickedPos);

	if (elementInFocus != NULL)
	{
		point clickedPosRelativeElement = clickedPos - elementInFocus->pos;

		callDelegate<void*, point>(elementInFocus->onFocusSystemDelegate, elementInFocus, clickedPosRelativeElement);
		elementInFocus->onFocusEvent.call(elementInFocus, clickedPosRelativeElement);
	}
}
void Grid_onFocusLost(void* elementPtr, point clickedPos)
{
	Grid* focusLostedGrid = static_cast<Grid*>(elementPtr);

	for (int i = 0; i < focusLostedGrid->getRowsCount(); i++)
	{
		for (int j = 0; j < focusLostedGrid->getColumnsCount(); j++)
		{
			controlElement* presentChild = focusLostedGrid->elements[i][j];
			if (presentChild == NULL)
				return;
			point focusLostPosRelativeElement = clickedPos - presentChild->pos;

			callDelegate<void*, point>(presentChild->onFocusLostSystemDelegate, presentChild, focusLostPosRelativeElement);
			presentChild->onFocusLostEvent.call(presentChild, focusLostPosRelativeElement);
		}
	}
}
void Grid_onLeftButtonDown(void* elementPtr, point clickedPos)
{
	Grid* leftButtonDownedGrid = static_cast<Grid*>(elementPtr);
	controlElement* onLeftButtonDownedElement = Grid_getElementsInPos(leftButtonDownedGrid, clickedPos);

	if (onLeftButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonDownedElement->pos;

		callDelegate<void*, point>(onLeftButtonDownedElement->onLeftButtonDownSystemDelegate, onLeftButtonDownedElement, clickedPosRelativeElement);
		onLeftButtonDownedElement->onLeftButtonDownEvent.call(onLeftButtonDownedElement, clickedPosRelativeElement);
	}
}
void Grid_onLeftButtonUp(void* elementPtr, point clickedPos)
{
	Grid* leftButtonUpedGrid = static_cast<Grid*>(elementPtr);
	controlElement* onLeftButtonUppedElement = Grid_getElementsInPos(leftButtonUpedGrid, clickedPos);

	if (onLeftButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonUppedElement->pos;

		callDelegate<void*, point>(onLeftButtonUppedElement->onLeftButtonUpSystemDelegate, onLeftButtonUppedElement, clickedPosRelativeElement);
		onLeftButtonUppedElement->onLeftButtonUpEvent.call(onLeftButtonUppedElement, clickedPosRelativeElement);
	}
}
void Grid_onRightButtonDown(void* elementPtr, point clickedPos)
{
	Grid* rightButtonDownedGrid = static_cast<Grid*>(elementPtr);
	controlElement* onRightButtonDownedElement = Grid_getElementsInPos(rightButtonDownedGrid, clickedPos);

	if (onRightButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonDownedElement->pos;

		callDelegate<void*, point>(onRightButtonDownedElement->onRightButtonDownSystemDelegate, onRightButtonDownedElement, clickedPosRelativeElement);
		onRightButtonDownedElement->onRightButtonDownEvent.call(onRightButtonDownedElement, clickedPosRelativeElement);
	}
}
void Grid_onRightButtonUp(void* elementPtr, point clickedPos)
{
	Grid* rightButtonUpedGrid = static_cast<Grid*>(elementPtr);
	controlElement* onRightButtonUppedElement = Grid_getElementsInPos(rightButtonUpedGrid, clickedPos);

	if (onRightButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonUppedElement->pos;

		callDelegate<void*, point>(onRightButtonUppedElement->onRightButtonUpSystemDelegate, onRightButtonUppedElement, clickedPosRelativeElement);
		onRightButtonUppedElement->onRightButtonUpEvent.call(onRightButtonUppedElement, clickedPosRelativeElement);
	}
}

void Grid_onKeyDown(void* elementPtr, char key)
{
	Grid* keyDownedGrid = static_cast<Grid*>(elementPtr);

	for (int i = 0; i < keyDownedGrid->getRowsCount(); i++)
	{
		for (int j = 0; j < keyDownedGrid->getColumnsCount(); j++)
		{
			controlElement* presentChild = keyDownedGrid->elements[i][j];
			if (presentChild == NULL)
				return;

			callDelegate<void*, char>(presentChild->onKeyDownSystemDelegate, presentChild, key);
		}
	}
}

void Grid_onKeyUp(void* elementPtr, char key)
{
	Grid* keyDownedGrid = static_cast<Grid*>(elementPtr);

	for (int i = 0; i < keyDownedGrid->getRowsCount(); i++)
	{
		for (int j = 0; j < keyDownedGrid->getColumnsCount(); j++)
		{
			controlElement* presentChild = keyDownedGrid->elements[i][j];
			if (presentChild == NULL)
				return;

			callDelegate<void*, char>(presentChild->onKeyUpSystemDelegate, presentChild, key);
		}
	}
}