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

struct GridElement
{
	controlElement* element;
	unsigned int span;
};
const GridElement emptyGridElement = { NULL, 0 };
const GridElement* emptyGridElementPtr = &emptyGridElement;

class Grid : public containerElement {
	dynamicArray<dynamicArray<GridElement*>> childs;
	dynamicArray<unsigned int> widths;
	dynamicArray<unsigned int> heights;
	point onePointSize;
public:
	bool ShowGridLines;
	Grid(unsigned int rowsCount = 0, unsigned int columnsCount = 0, bool _showGridLines = false, symbolColor _background = black)
	{
		pos = emptyPoint;
		size = emptyPoint;
		ShowGridLines = _showGridLines;
		background = _background;

		setRowsColumnsCount(rowsCount, columnsCount);

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

	void addChild(controlElement& element, unsigned int span, int row, int column)
	{
		if (childs.canGet(row))
		{
			if (childs[row].canGet(column))
			{
				childs[row][column] = new GridElement({ &element, span });
				childs[row][column]->element->parent = this;
			}
		}

		updatePositions();
	}
	void addChild(controlElement& element, int row, int column)
	{
		addChild(element, 1, row, column);
	}
	void addChild(controlElement& addedChild, unsigned int span)
	{
		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j] != emptyGridElementPtr)
				{
					childs[i][j] = new GridElement({ &addedChild, span });
					childs[i][j]->element->parent = this;

					updatePositions();
					return;
				}
			}
		}
	}
	void addChild(controlElement& addedChild)
	{
		addChild(addedChild, 1);
	}

	void delChild(controlElement& deletedChild)
	{
		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j]->element == &deletedChild)
				{
					childs[i][j]->element->parent = NULL;
					childs[i][j]->span = 0;
					childs[i][j] = (GridElement*)(emptyGridElementPtr);
				}
			}
		}
	}
	void delChild(point childPos)
	{
		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j] != (GridElement*)(emptyGridElementPtr) && childs[i][j]->element->entersTheArea(childPos))
				{
					childs[i][j]->element->parent = NULL;
					childs[i][j]->span = 0;
					childs[i][j] = (GridElement*)(emptyGridElementPtr);
				}
			}
		}
	}
	void delChild(int row, int column)
	{
		if (childs.canGet(row) && childs[row].canGet(column) && childs[row][column] != (GridElement*)(emptyGridElementPtr))
		{
			childs[row][column]->element->parent = NULL;
			childs[row][column]->span = 0;
			childs[row][column] = (GridElement*)(emptyGridElementPtr);
		}
	}

	controlElement* getChild(int row, int column)
	{
		if (childs.canGet(row))
			if (childs[row].canGet(column))
				if (childs[row][column] != (GridElement*)(emptyGridElementPtr))
					return childs[row][column]->element;

		return NULL;
	}
	unsigned int getChildSpan(int row, int column)
	{
		if (childs.canGet(row))
			if (childs[row].canGet(column))
				if (childs[row][column] != (GridElement*)(emptyGridElementPtr))
					return childs[row][column]->span;

		return 0;
	}
	unsigned int getChildsCount()
	{
		unsigned int result = 0;

		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j] != (GridElement*)(emptyGridElementPtr))
				{
					result++;
				}
			}
		}

		return result;
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
				if (childs[i][j] != (GridElement*)(emptyGridElementPtr) && childs[i][j]->element->Visible)
					childs[i][j]->element->Draw(thisElementRect);
			}
		}
	}

	void showGrid(symbolColor gridColor = blue)
	{
		onePointSize = calculateOnePointSize();
		point presentPos = pos;
		rectangle thisElementRect = getRect();

		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				point presentSize = { widths[j] * onePointSize.x, heights[i] * onePointSize.y };

				consolePrintLine(thisElementRect, presentPos, presentSize.x - 1, filledCharacter_5_5, blue);
				consolePrintVerticalLine(thisElementRect, presentPos, presentSize.y - 1, filledCharacter_5_5, blue);

				presentPos.x += widths[j] * onePointSize.x;
			}

			presentPos.x = pos.x;
			presentPos.y += heights[i] * onePointSize.y;
		}
	}


	void updatePositions()
	{
		onePointSize = calculateOnePointSize();
		point presentPos = pos;

		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j] != (GridElement*)(emptyGridElementPtr))
				{
					point presentSize = { widths[j] * onePointSize.x, heights[i] * onePointSize.y };
					childs[i][j]->element->pos = presentPos;

					if (childs[i][j]->span == 1)
						childs[i][j]->element->size = presentSize;
					else {
						point presentSpanSize = { 0, heights[i] * onePointSize.y };

						for (int k = 0; k < childs[i][j]->span && j + k < widths.count; k++)
						{
							presentSpanSize.x += widths[j + k] * onePointSize.x;
						}

						childs[i][j]->element->size = presentSpanSize;
					}
				}

				presentPos.x += widths[j] * onePointSize.x;
			}

			presentPos.x = 0;
			presentPos.y += heights[i] * onePointSize.y;
		}
	}

	void setHeight(unsigned int elementIndex, unsigned int newHeight)
	{
		heights[elementIndex] = newHeight;

		updatePositions();
	}

	unsigned int getHeight(unsigned int elementIndex)
	{
		return heights[elementIndex];
	}

	unsigned int getHeightsSum()
	{
		unsigned int result = 0;

		for (int i = 0; i < heights.count; i++)
		{
			result += heights[i];
		}

		return result;
	}

	void setWidth(unsigned int elementIndex, unsigned int newWidth)
	{
		widths[elementIndex] = newWidth;

		updatePositions();
	}

	unsigned int getWidth(unsigned int elementIndex)
	{
		return widths[elementIndex];
	}

	unsigned int getWidthsSum()
	{
		unsigned int result = 0;

		for (int i = 0; i < widths.count; i++)
		{
			result += widths[i];
		}

		return result;
	}

	point getOnePointSize()
	{
		return onePointSize;
	}

	point calculateOnePointSize()
	{
		point gridSizeInPoints = { getWidthsSum(), getHeightsSum() };
		if (gridSizeInPoints.x == 0 || gridSizeInPoints.y == 0)
			return emptyPoint;

		return size / gridSizeInPoints;
	}


	bool isIdentifyed()
	{
		return childs != NULL;
	}

	void addRow(unsigned int size)
	{
		dynamicArray<GridElement*> addedRow;

		if (isIdentifyed())
			addedRow.set((GridElement*)(emptyGridElementPtr), getColumnsCount());
		else
			addedRow.set((GridElement*)(emptyGridElementPtr));

		childs.add(addedRow);
		heights.add(size);

		updatePositions();
	}
	void addRow()
	{
		addRow(1);
	}

	void addRows(unsigned int rowsCount, unsigned int rowsSize)
	{
		heights.add(rowsSize, rowsCount);

		if (!isIdentifyed()) //!
		{
			dynamicArray<GridElement*> addedRow;
			addedRow.set((GridElement*)(emptyGridElementPtr));
			childs.add(addedRow);
			rowsCount--;
		}

		for (int i = 0; i < rowsCount; i++)
		{
			dynamicArray<GridElement*> addedRow;
			addedRow.set((GridElement*)(emptyGridElementPtr), getColumnsCount());
			childs.add(addedRow);
		}

		updatePositions();
	}
	void addRows(unsigned int rowsCount)
	{
		addRows(rowsCount, 1);
	}

	void delRow(unsigned int rowIndex)
	{
		heights.delElementIn(rowIndex);
		childs.delElementIn(rowIndex);
		updatePositions();
	}

	unsigned int getRowsCount()
	{
		return childs.count;
	}


	void addColumn(unsigned int size)
	{
		if (!isIdentifyed())
			return;

		for (int i = 0; i < getRowsCount(); i++)
		{
			childs[i].add((GridElement*)(emptyGridElementPtr));
		}
		widths.add(size);

		updatePositions();
	}
	void addColumn()
	{
		addColumn(1);
	}

	void addColumns(unsigned int columnsCount, unsigned int columnsSize)
	{
		if (!isIdentifyed())
			return;

		for (int i = 0; i < getRowsCount(); i++)
		{
			childs[i].add((GridElement*)(emptyGridElementPtr), columnsCount);
		}
		widths.add(columnsSize, columnsCount);

		updatePositions();
	}
	void addColumns(unsigned int columnsCount)
	{
		addColumns(columnsCount, 1);
	}

	void delColumn(unsigned int columnIndex)
	{
		if (!isIdentifyed())
			return;

		for (int i = 0; i < getRowsCount(); i++)
		{
			childs[i].delElementIn(columnIndex);
		}
		widths.delElementIn(columnIndex);

		updatePositions();
	}

	unsigned int getColumnsCount()
	{
		return childs[0].count;
	}


	void setRowsColumnsCount(unsigned int rowsCount, unsigned int columnsCount, unsigned int size)
	{
		for (int i = 0; i < rowsCount; i++)
		{
			dynamicArray<GridElement*> addedRow;
			addedRow.set((GridElement*)(emptyGridElementPtr), columnsCount);
			childs.add(addedRow);
		}
		heights.set(size, rowsCount);
		widths.set(size, columnsCount);

		updatePositions();
	}
	void setRowsColumnsCount(unsigned int rowsCount, unsigned int columnsCount)
	{
		setRowsColumnsCount(rowsCount, columnsCount, 1);
	}
	void setColumnsRowsCount(unsigned int columnsCount, unsigned int rowsCount, unsigned int size)
	{
		setRowsColumnsCount(rowsCount, columnsCount, size);
	}
	void setColumnsRowsCount(unsigned int columnsCount, unsigned int rowsCount)
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

controlElement* Grid_getElementsInPos(Grid* container, point pos)
{
	for (int i = 0; i < container->getRowsCount(); i++)
	{
		for (int j = 0; j < container->getColumnsCount(); j++)
		{
			controlElement* presentChild = container->getChild(i, j);

			if (presentChild != NULL && presentChild->entersTheArea(pos))
			{
				return presentChild;
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
			controlElement* presentChild = focusLostedGrid->getChild(i, j);
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
			controlElement* presentChild = keyDownedGrid->getChild(i, j);
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
			controlElement* presentChild = keyDownedGrid->getChild(i, j);
			if (presentChild == NULL)
				return;

			callDelegate<void*, char>(presentChild->onKeyUpSystemDelegate, presentChild, key);
		}
	}
}