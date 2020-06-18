#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"


void UniformGrid_onFocus(void* elementPtr, point clickedPos);
void UniformGrid_onFocusLost(void* elementPtr, point clickedPos);
void UniformGrid_onClick(void* elementPtr, point clickedPos);
void UniformGrid_onLeftButtonDown(void* elementPtr, point clickedPos);
void UniformGrid_onLeftButtonUp(void* elementPtr, point clickedPos);
void UniformGrid_onRightButtonDown(void* elementPtr, point clickedPos);
void UniformGrid_onRightButtonUp(void* elementPtr, point clickedPos);
void UniformGrid_onKeyDown(void* elementPtr, char key);
void UniformGrid_onKeyUp(void* elementPtr, char key);

class UniformGrid : public containerElement {
	dynamicArray<dynamicArray<controlElement*>> childs;
	point oneElementSize;
	bool ShowGridLines;
public:
	UniformGrid(point _pos, point _size, bool _showGridLines = false, symbolColor _background = black)
	{
		pos = _pos;
		size = _size;
		background = _background;

		childs = NULL;

		onFocusSystemDelegate = UniformGrid_onFocus;
		onFocusLostSystemDelegate = UniformGrid_onFocusLost;
		onClickSystemDelegate = UniformGrid_onClick;
		onLeftButtonDownSystemDelegate = UniformGrid_onLeftButtonDown;
		onLeftButtonUpSystemDelegate = UniformGrid_onLeftButtonUp;
		onRightButtonDownSystemDelegate = UniformGrid_onRightButtonDown;
		onRightButtonUpSystemDelegate = UniformGrid_onRightButtonUp;
		onKeyDownSystemDelegate = UniformGrid_onKeyDown;
		onKeyUpSystemDelegate = UniformGrid_onKeyUp;

		registerElement();
	}

	void addChild(controlElement& addedChild)
	{
		if (!isIdentifyed())
			addRow();

		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j] == NULL)
				{
					childs[i][j] = &addedChild;
					addedChild.parent = this;

					updatePositions();
					return;
				}
			}
		}
	}

	void delChild(controlElement& deletedChild)
	{
		int findResult = -1;
		for (int i = 0; i < childs.count; i++)
		{
			findResult = childs[i].find(&deletedChild);
			if (findResult != -1)
			{
				childs[i].delElementIn(findResult);
				deletedChild.parent = NULL;
				return;
			}
		}
	}

	void addControlElement(controlElement& element, int row, int column)
	{
		if (childs.canGet(row))
		{
			if (childs[row].canGet(column))
			{
				childs[row][column] = &element;
				updatePositions();
			}
		}
	}

	void delControlElement(int row, int column)
	{
		if (childs.canGet(row))
			if (childs[row].canGet(column))
				childs[row][column] = NULL;
	}

	controlElement* getChild(int index)
	{
		int gettedChildRow = index / getRowsCount();
		int gettedChildColumn = index % getColumnsCount();

		return childs[gettedChildRow][gettedChildColumn];
	}

	unsigned int getChildsCount()
	{
		return getRowsCount() * getColumnsCount();
	}

	void showGrid(symbolColor gridColor = blue)
	{
		oneElementSize = calculateOneElementSize();
		point presentPos = pos;
		rectangle thisElementRect = getRect();

		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				consolePrintLine(thisElementRect, presentPos, oneElementSize.x - 1, filledCharacter_5_5, blue);
				consolePrintVerticalLine(thisElementRect, presentPos, oneElementSize.y - 1, filledCharacter_5_5, blue);

				presentPos.x += oneElementSize.x;
			}

			presentPos.x = pos.x;
			presentPos.y += oneElementSize.y;
		}
	}

	void Draw(rectangle& drawFrame)
	{
		rectangle thisElementRect = getRect();

		if (ShowGridLines)
			showGrid();
		else
			consolePrintRect(drawFrame, thisElementRect, filledCharacter_5_5, collectColor(black, background));

		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j] != NULL && childs[i][j]->Visible)
					childs[i][j]->Draw(thisElementRect);
			}
		}
	}

	void updatePositions()
	{
		oneElementSize = calculateOneElementSize();
		point presentPos = pos;

		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j] != NULL)
				{
					childs[i][j]->pos = presentPos;
					childs[i][j]->size = oneElementSize;
				}

				presentPos.x += oneElementSize.x;
			}

			presentPos.x = 0;
			presentPos.y += oneElementSize.y;
		}
	}

	point getOnePointSize()
	{
		return oneElementSize;
	}

	point calculateOneElementSize()
	{
		point gridSizeInElements = { getColumnsCount(), getRowsCount() };
		return size / gridSizeInElements;
	}


	unsigned int getRowsCount()
	{
		return childs.count;
	}

	unsigned int getColumnsCount()
	{
		return childs[0].count;
	}

	bool isIdentifyed()
	{
		return childs != NULL;
	}

	void addRows(int rowsCount)
	{
		if (!isIdentifyed())
		{
			dynamicArray<controlElement*> addedRow;
			addedRow.add(NULL);
			childs.add(addedRow);
			rowsCount--;
		}

		for (int i = 0; i < rowsCount; i++)
		{
			dynamicArray<controlElement*> addedRow;
			addedRow.add(NULL, getColumnsCount());
			childs.add(addedRow);
		}

		updatePositions();
	}
	void addRow()
	{
		addRows(1);
	}

	void delRow(int rowIndex)
	{
		childs.delElementIn(rowIndex);
		updatePositions();
	}

	void addColumns(int columnsCount)
	{
		if (!isIdentifyed())
			return;

		for (int i = 0; i < getRowsCount(); i++)
		{
			childs[i].add(NULL, columnsCount);
		}

		updatePositions();
	}
	void addColumn()
	{
		addColumns(1);
	}

	void delColumn(int columnIndex)
	{
		if (!isIdentifyed())
			return;

		for (int i = 0; i < getRowsCount(); i++)
		{
			childs[i].delElementIn(columnIndex);
		}

		updatePositions();
	}

	void setRowsColumnsCount(int rowsCount, int columnsCount, unsigned int size)
	{
		for (int i = 0; i < rowsCount; i++)
		{
			dynamicArray<controlElement*> addedRow;
			addedRow.set(NULL, columnsCount);
			childs.add(addedRow);
		}

		updatePositions();
	}
	void setRowsColumnsCount(int rowsCount, int columnsCount)
	{
		setRowsColumnsCount(rowsCount, columnsCount, 1);
	}
	void setColumnsRowsCount(int columnsCount, int rowsCount, unsigned int size)
	{
		setRowsColumnsCount(rowsCount, columnsCount, size);
	}
	void setColumnsRowsCount(int columnsCount, int rowsCount)
	{
		setRowsColumnsCount(rowsCount, columnsCount, 1);
	}
};

controlElement* UniformGrid_getElementsInPos(containerElement* container, point pos)
{
	UniformGrid* clickedUniformGrid = static_cast<UniformGrid*>(container);

	for (int i = 0; i < clickedUniformGrid->getChildsCount(); i++)
	{
		controlElement* presentChild = clickedUniformGrid->getChild(i);

		if (presentChild != NULL && presentChild->entersTheArea(pos))
		{
			return presentChild;
		}
	}

	return NULL;
}

void UniformGrid_onClick(void* elementPtr, point clickedPos)
{
	UniformGrid* clickedUniformGrid = static_cast<UniformGrid*>(elementPtr);
	controlElement* clickedElement = UniformGrid_getElementsInPos(clickedUniformGrid, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		callDelegate<void*, point>(clickedElement->onClickSystemDelegate, clickedElement, clickedPosRelativeElement);
		clickedElement->onClickEvent.call(clickedElement, clickedPosRelativeElement);
	}
}
void UniformGrid_onFocus(void* elementPtr, point clickedPos)
{
	UniformGrid* focusedUniformGrid = static_cast<UniformGrid*>(elementPtr);
	controlElement* elementInFocus = UniformGrid_getElementsInPos(focusedUniformGrid, clickedPos);

	Default_System_OnFocus(elementPtr, clickedPos);

	if (elementInFocus != NULL)
	{
		point clickedPosRelativeElement = clickedPos - elementInFocus->pos;

		callDelegate<void*, point>(elementInFocus->onFocusSystemDelegate, elementInFocus, clickedPosRelativeElement);
		elementInFocus->onFocusEvent.call(elementInFocus, clickedPosRelativeElement);
	}
}
void UniformGrid_onFocusLost(void* elementPtr, point clickedPos)
{
	UniformGrid* focusLostedUniformGrid = static_cast<UniformGrid*>(elementPtr);

	for (int i = 0; i < focusLostedUniformGrid->getChildsCount(); i++)
	{
		controlElement* presentChild = focusLostedUniformGrid->getChild(i);
		if (presentChild == NULL)
			return;
		point focusLostPosRelativeElement = clickedPos - presentChild->pos;

		callDelegate<void*, point>(presentChild->onFocusLostSystemDelegate, presentChild, focusLostPosRelativeElement);
		presentChild->onFocusLostEvent.call(presentChild, focusLostPosRelativeElement);
	}
}
void UniformGrid_onLeftButtonDown(void* elementPtr, point clickedPos)
{
	UniformGrid* leftButtonDownedUniformGrid = static_cast<UniformGrid*>(elementPtr);
	controlElement* onLeftButtonDownedElement = UniformGrid_getElementsInPos(leftButtonDownedUniformGrid, clickedPos);

	if (onLeftButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonDownedElement->pos;

		callDelegate<void*, point>(onLeftButtonDownedElement->onLeftButtonDownSystemDelegate, onLeftButtonDownedElement, clickedPosRelativeElement);
		onLeftButtonDownedElement->onLeftButtonDownEvent.call(onLeftButtonDownedElement, clickedPosRelativeElement);
	}
}
void UniformGrid_onLeftButtonUp(void* elementPtr, point clickedPos)
{
	UniformGrid* leftButtonUpedUniformGrid = static_cast<UniformGrid*>(elementPtr);
	controlElement* onLeftButtonUppedElement = UniformGrid_getElementsInPos(leftButtonUpedUniformGrid, clickedPos);

	if (onLeftButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonUppedElement->pos;

		callDelegate<void*, point>(onLeftButtonUppedElement->onLeftButtonUpSystemDelegate, onLeftButtonUppedElement, clickedPosRelativeElement);
		onLeftButtonUppedElement->onLeftButtonUpEvent.call(onLeftButtonUppedElement, clickedPosRelativeElement);
	}
}
void UniformGrid_onRightButtonDown(void* elementPtr, point clickedPos)
{
	UniformGrid* rightButtonDownedUniformGrid = static_cast<UniformGrid*>(elementPtr);
	controlElement* onRightButtonDownedElement = UniformGrid_getElementsInPos(rightButtonDownedUniformGrid, clickedPos);

	if (onRightButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonDownedElement->pos;

		callDelegate<void*, point>(onRightButtonDownedElement->onRightButtonDownSystemDelegate, onRightButtonDownedElement, clickedPosRelativeElement);
		onRightButtonDownedElement->onRightButtonDownEvent.call(onRightButtonDownedElement, clickedPosRelativeElement);
	}
}
void UniformGrid_onRightButtonUp(void* elementPtr, point clickedPos)
{
	UniformGrid* rightButtonUpedUniformGrid = static_cast<UniformGrid*>(elementPtr);
	controlElement* onRightButtonUppedElement = UniformGrid_getElementsInPos(rightButtonUpedUniformGrid, clickedPos);

	if (onRightButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonUppedElement->pos;

		callDelegate<void*, point>(onRightButtonUppedElement->onRightButtonUpSystemDelegate, onRightButtonUppedElement, clickedPosRelativeElement);
		onRightButtonUppedElement->onRightButtonUpEvent.call(onRightButtonUppedElement, clickedPosRelativeElement);
	}
}

void UniformGrid_onKeyDown(void* elementPtr, char key)
{
	UniformGrid* keyDownedUniformGrid = static_cast<UniformGrid*>(elementPtr);

	for (int i = 0; i < keyDownedUniformGrid->getChildsCount(); i++)
	{
		controlElement* presentChild = keyDownedUniformGrid->getChild(i);
		if (presentChild == NULL)
			return;

		callDelegate<void*, char>(presentChild->onKeyDownSystemDelegate, presentChild, key);
	}
}

void UniformGrid_onKeyUp(void* elementPtr, char key)
{
	UniformGrid* keyDownedUniformGrid = static_cast<UniformGrid*>(elementPtr);

	for (int i = 0; i < keyDownedUniformGrid->getChildsCount(); i++)
	{
		controlElement* presentChild = keyDownedUniformGrid->getChild(i);
		if (presentChild == NULL)
			return;

		callDelegate<void*, char>(presentChild->onKeyUpSystemDelegate, presentChild, key);
	}
}