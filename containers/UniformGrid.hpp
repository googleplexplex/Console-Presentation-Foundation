#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"


void UniformGrid_Dispatch_onFocus(void* elementPtr, point clickedPos);
void UniformGrid_Dispatch_onFocusLost(void* elementPtr, point clickedPos);
void UniformGrid_Dispatch_onClick(void* elementPtr, point clickedPos);
void UniformGrid_Dispatch_onLeftButtonDown(void* elementPtr, point clickedPos);
void UniformGrid_Dispatch_onLeftButtonUp(void* elementPtr, point clickedPos);
void UniformGrid_Dispatch_onRightButtonDown(void* elementPtr, point clickedPos);
void UniformGrid_Dispatch_onRightButtonUp(void* elementPtr, point clickedPos);
void UniformGrid_Dispatch_onKeyDown(void* elementPtr, char key);
void UniformGrid_Dispatch_onKeyUp(void* elementPtr, char key);

class UniformGrid : public containerElement {
	dynamicArray<dynamicArray<controlElement*>> childs;
	point oneElementSize;
public:
	bool ShowGridLines;
	UniformGrid(unsigned int rowsCount = 0, unsigned int columnsCount = 0, bool _showGridLines = false, symbolColor _background = black)
	{
		pos = emptyPoint;
		size = emptyPoint;
		ShowGridLines = _showGridLines;
		background = _background;

		setRowsColumnsCount(rowsCount, columnsCount);

		onFocus.add(UniformGrid_Dispatch_onFocus);
		onFocusLost.add(UniformGrid_Dispatch_onFocusLost);
		onClick.add(UniformGrid_Dispatch_onClick);
		onLeftButtonDown.add(UniformGrid_Dispatch_onLeftButtonDown);
		onLeftButtonUp.add(UniformGrid_Dispatch_onLeftButtonUp);
		onRightButtonDown.add(UniformGrid_Dispatch_onRightButtonDown);
		onRightButtonUp.add(UniformGrid_Dispatch_onRightButtonUp);
		onKeyDown.add(UniformGrid_Dispatch_onKeyDown);
		onKeyUp.add(UniformGrid_Dispatch_onKeyUp);
	}


	//Standart container methods
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
					childs[i][j]->parent = this;

					updatePositions();
					addInRedrawQueue();
					return;
				}
			}
		}
	}
	void addChild(controlElement& addedChild, int row, int column)
	{
		if (childs.canGet(row))
		{
			if (childs[row].canGet(column))
			{
				childs[row][column] = &addedChild;
				childs[row][column]->parent = this;

				updatePositions();
				addInRedrawQueue();
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
				childs[i][findResult]->parent = NULL;
				childs[i][findResult] = NULL;

				addInRedrawQueue();
				return;
			}
		}
	}
	void delChild(point childPos)
	{
		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j] != NULL && childs[i][j]->entersTheArea(childPos))
				{
					childs[i][j]->parent = NULL;
					childs[i][j] = NULL;

					addInRedrawQueue();
				}
			}
		}
	}
	void delChild(int row, int column)
	{
		if (childs.canGet(row) && childs[row] != NULL
			&& childs[row].canGet(column) && childs[row][column] != NULL)
		{
			childs[row][column]->parent = NULL;
			childs[row][column] = NULL;

			addInRedrawQueue();
		}
	}

	controlElement* getChild(int rowIndex, int columnIndex)
	{
		return childs[rowIndex][columnIndex];
	}

	unsigned int getChildsCount()
	{
		unsigned int result = 0;

		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j] != NULL)
				{
					result++;
				}
			}
		}

		return result;
	}


	//Drawing methods
	void Draw()
	{
		rectangle thisElementRect = getRect();

		if (ShowGridLines)
			showGrid();
		else
			consolePrintRect(thisElementRect, filledCharacter_5_5, collectColor(black, background));

		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j] != NULL && childs[i][j]->Visible)
				{
					childs[i][j]->beforeDraw.call(childs[i][j]);
					childs[i][j]->Draw();
					childs[i][j]->afterDraw.call(childs[i][j]);
				}
			}
		}
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
				consolePrintLine(presentPos, oneElementSize.x - 1, filledCharacter_5_5, blue);
				consolePrintVerticalLine(presentPos, oneElementSize.y - 1, filledCharacter_5_5, blue);

				presentPos.x += oneElementSize.x;
			}

			presentPos.x = pos.x;
			presentPos.y += oneElementSize.y;
		}
	}


	//Distribution to elements of their position
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


	//Additional container interaction
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
		addInRedrawQueue();
	}
	void addRow()
	{
		addRows(1);
	}

	void delRow(int rowIndex)
	{
		childs.delElementIn(rowIndex);

		updatePositions();
		addInRedrawQueue();
	}

	unsigned int getRowsCount()
	{
		return childs.count;
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
		addInRedrawQueue();
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
		addInRedrawQueue();
	}

	unsigned int getColumnsCount()
	{
		return childs[0].count;
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
		addInRedrawQueue();
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

	unsigned int getRowsColumnsCount()
	{
		return getRowsCount() * getColumnsCount();
	}
	unsigned int getColumnsRowsCount()
	{
		return getRowsColumnsCount();
	}
};


//Container events distribution
controlElement* UniformGrid_getElementsInPos(containerElement* container, point pos)
{
	UniformGrid* clickedUniformGrid = static_cast<UniformGrid*>(container);

	for (int i = 0; i < clickedUniformGrid->getRowsCount(); i++)
	{
		for (int j = 0; j < clickedUniformGrid->getColumnsCount(); j++)
		{
			controlElement* presentChild = clickedUniformGrid->getChild(i, j);

			if (presentChild != NULL && presentChild->entersTheArea(pos))
			{
				return presentChild;
			}
		}
	}

	return NULL;
}

void UniformGrid_Dispatch_onClick(void* elementPtr, point clickedPos)
{
	UniformGrid* clickedUniformGrid = static_cast<UniformGrid*>(elementPtr);
	controlElement* clickedElement = UniformGrid_getElementsInPos(clickedUniformGrid, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		clickedElement->onClick.call(clickedElement, clickedPosRelativeElement);
	}
}
void UniformGrid_Dispatch_onFocus(void* elementPtr, point clickedPos)
{
	UniformGrid* focusedUniformGrid = static_cast<UniformGrid*>(elementPtr);
	controlElement* elementInFocus = UniformGrid_getElementsInPos(focusedUniformGrid, clickedPos);

	Default_System_OnFocus(elementPtr, clickedPos);

	if (elementInFocus != NULL)
	{
		point clickedPosRelativeElement = clickedPos - elementInFocus->pos;

		elementInFocus->onFocus.call(elementInFocus, clickedPosRelativeElement);
	}
}
void UniformGrid_Dispatch_onFocusLost(void* elementPtr, point clickedPos)
{
	UniformGrid* focusLostedUniformGrid = static_cast<UniformGrid*>(elementPtr);

	for (int i = 0; i < focusLostedUniformGrid->getRowsCount(); i++)
	{
		for (int j = 0; j < focusLostedUniformGrid->getColumnsCount(); j++)
		{
			controlElement* presentChild = focusLostedUniformGrid->getChild(i, j);
			if (presentChild == NULL)
				return;
			point focusLostPosRelativeElement = clickedPos - presentChild->pos;

			presentChild->onFocusLost.call(presentChild, focusLostPosRelativeElement);
		}
	}
}
void UniformGrid_Dispatch_onLeftButtonDown(void* elementPtr, point clickedPos)
{
	UniformGrid* leftButtonDownedUniformGrid = static_cast<UniformGrid*>(elementPtr);
	controlElement* onLeftButtonDownedElement = UniformGrid_getElementsInPos(leftButtonDownedUniformGrid, clickedPos);

	if (onLeftButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonDownedElement->pos;

		onLeftButtonDownedElement->onLeftButtonDown.call(onLeftButtonDownedElement, clickedPosRelativeElement);
	}
}
void UniformGrid_Dispatch_onLeftButtonUp(void* elementPtr, point clickedPos)
{
	UniformGrid* leftButtonUpedUniformGrid = static_cast<UniformGrid*>(elementPtr);
	controlElement* onLeftButtonUppedElement = UniformGrid_getElementsInPos(leftButtonUpedUniformGrid, clickedPos);

	if (onLeftButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonUppedElement->pos;

		onLeftButtonUppedElement->onLeftButtonUp.call(onLeftButtonUppedElement, clickedPosRelativeElement);
	}
}
void UniformGrid_Dispatch_onRightButtonDown(void* elementPtr, point clickedPos)
{
	UniformGrid* rightButtonDownedUniformGrid = static_cast<UniformGrid*>(elementPtr);
	controlElement* onRightButtonDownedElement = UniformGrid_getElementsInPos(rightButtonDownedUniformGrid, clickedPos);

	if (onRightButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonDownedElement->pos;

		onRightButtonDownedElement->onRightButtonDown.call(onRightButtonDownedElement, clickedPosRelativeElement);
	}
}
void UniformGrid_Dispatch_onRightButtonUp(void* elementPtr, point clickedPos)
{
	UniformGrid* rightButtonUpedUniformGrid = static_cast<UniformGrid*>(elementPtr);
	controlElement* onRightButtonUppedElement = UniformGrid_getElementsInPos(rightButtonUpedUniformGrid, clickedPos);

	if (onRightButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonUppedElement->pos;

		onRightButtonUppedElement->onRightButtonUp.call(onRightButtonUppedElement, clickedPosRelativeElement);
	}
}

void UniformGrid_Dispatch_onKeyDown(void* elementPtr, char key)
{
	UniformGrid* keyDownedUniformGrid = static_cast<UniformGrid*>(elementPtr);

	for (int i = 0; i < keyDownedUniformGrid->getRowsCount(); i++)
	{
		for (int j = 0; j < keyDownedUniformGrid->getColumnsCount(); j++)
		{
			controlElement* presentChild = keyDownedUniformGrid->getChild(i, j);

			if (presentChild != NULL)
			{
				presentChild->onKeyDown.call(presentChild, key);
			}
		}
	}
}

void UniformGrid_Dispatch_onKeyUp(void* elementPtr, char key)
{
	UniformGrid* keyDownedUniformGrid = static_cast<UniformGrid*>(elementPtr);

	for (int i = 0; i < keyDownedUniformGrid->getRowsCount(); i++)
	{
		for (int j = 0; j < keyDownedUniformGrid->getColumnsCount(); j++)
		{
			controlElement* presentChild = keyDownedUniformGrid->getChild(i, j);

			if (presentChild != NULL)
			{
				presentChild->onKeyUp.call(presentChild, key);
			}
		}
	}
}