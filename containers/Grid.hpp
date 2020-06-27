#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"


void Grid_Dispatch_onFocus(void* elementPtr, point clickedPos);
void Grid_Dispatch_onFocusLost(void* elementPtr, point clickedPos);
void Grid_Dispatch_onClick(void* elementPtr, point clickedPos);
void Grid_Dispatch_onLeftButtonDown(void* elementPtr, point clickedPos);
void Grid_Dispatch_onLeftButtonUp(void* elementPtr, point clickedPos);
void Grid_Dispatch_onRightButtonDown(void* elementPtr, point clickedPos);
void Grid_Dispatch_onRightButtonUp(void* elementPtr, point clickedPos);
void Grid_Dispatch_onKeyDown(void* elementPtr, char key);
void Grid_Dispatch_onKeyUp(void* elementPtr, char key);
void Grid_Dispatch_beforeDraw(void* elementPtr);
void Grid_Dispatch_afterDraw(void* elementPtr);

struct GridElement
{
	controlElement* element;
	unsigned int RowSpan;
	unsigned int ColumnSpan;
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

		onFocus.add(Grid_Dispatch_onFocus);
		onFocusLost.add(Grid_Dispatch_onFocusLost);
		onClick.add(Grid_Dispatch_onClick);
		onLeftButtonDown.add(Grid_Dispatch_onLeftButtonDown);
		onLeftButtonUp.add(Grid_Dispatch_onLeftButtonUp);
		onRightButtonDown.add(Grid_Dispatch_onRightButtonDown);
		onRightButtonUp.add(Grid_Dispatch_onRightButtonUp);
		onKeyDown.add(Grid_Dispatch_onKeyDown);
		onKeyUp.add(Grid_Dispatch_onKeyUp);
		beforeDraw.add(Grid_Dispatch_beforeDraw);
		afterDraw.add(Grid_Dispatch_afterDraw);
	}


	//Standart container methods
	void addChild(controlElement& element, unsigned int row, unsigned int column, unsigned int RowSpan, unsigned int ColumnSpan)
	{
		if (childs.canGet(row))
		{
			if (childs[row].canGet(column))
			{
				childs[row][column] = new GridElement({ &element, RowSpan, ColumnSpan });
				childs[row][column]->element->parent = this;

				updatePositions();
				needToDraw = true;
			}
		}
	}
	void addChild(controlElement& element, unsigned int row, unsigned int column)
	{
		addChild(element, row, column, 1, 1);
	}
	void addChild(controlElement& addedChild)
	{
		addChild(addedChild, 0, 0, 1, 1);
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
					childs[i][j] = (GridElement*)(emptyGridElementPtr);

					needToDraw = true;
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
					childs[i][j] = (GridElement*)(emptyGridElementPtr);

					needToDraw = true;
				}
			}
		}
	}
	void delChild(int row, int column)
	{
		if (childs.canGet(row) && childs[row].canGet(column) && childs[row][column] != (GridElement*)(emptyGridElementPtr))
		{
			childs[row][column]->element->parent = NULL;
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
	unsigned int getChildRowSpan(int row, int column)
	{
		if (childs.canGet(row))
			if (childs[row].canGet(column))
				if (childs[row][column] != (GridElement*)(emptyGridElementPtr))
					return childs[row][column]->RowSpan;

		return 0;
	}
	unsigned int getChildColumnSpan(int row, int column)
	{
		if (childs.canGet(row))
			if (childs[row].canGet(column))
				if (childs[row][column] != (GridElement*)(emptyGridElementPtr))
					return childs[row][column]->ColumnSpan;

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


	//Drawing methods
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
				if (childs[i][j] != (GridElement*)(emptyGridElementPtr) && childs[i][j]->element->Visible && childs[i][j]->element->needToDraw)
					childs[i][j]->element->Draw(thisElementRect);
			}
		}
		
		needToDraw = false;
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


	//Distribution to elements of their position
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

					if (childs[i][j]->RowSpan == 1)
						childs[i][j]->element->size.y = presentSize.y;
					else {
						unsigned int presentSpanSize = 0;

						for (int k = 0; k < childs[i][j]->RowSpan && j + k < heights.count; k++)
						{
							presentSpanSize += heights[j + k] * onePointSize.y;
						}

						childs[i][j]->element->size.y = presentSpanSize;
					}

					if (childs[i][j]->ColumnSpan == 1)
						childs[i][j]->element->size.x = presentSize.x;
					else {
						unsigned int presentSpanSize = 0;

						for (int k = 0; k < childs[i][j]->ColumnSpan && j + k < widths.count; k++)
						{
							presentSpanSize += widths[j + k] * onePointSize.x;
						}

						childs[i][j]->element->size.x = presentSpanSize;
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
		needToDraw = true;
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
		needToDraw = true;
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


	//Additional container interaction
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
		needToDraw = true;
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
		needToDraw = true;
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
		needToDraw = true;
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
		needToDraw = true;
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
		needToDraw = true;
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
		needToDraw = true;
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
		needToDraw = true;
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


//Container events distribution
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

void Grid_Dispatch_onClick(void* elementPtr, point clickedPos)
{
	Grid* clickedGrid = static_cast<Grid*>(elementPtr);
	controlElement* clickedElement = Grid_getElementsInPos(clickedGrid, clickedPos);

	if (clickedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - clickedElement->pos;

		clickedElement->onClick.call(clickedElement, clickedPosRelativeElement);
	}
}
void Grid_Dispatch_onFocus(void* elementPtr, point clickedPos)
{
	Grid* focusedGrid = static_cast<Grid*>(elementPtr);
	controlElement* elementInFocus = Grid_getElementsInPos(focusedGrid, clickedPos);

	Default_System_OnFocus(elementPtr, clickedPos);

	if (elementInFocus != NULL)
	{
		point clickedPosRelativeElement = clickedPos - elementInFocus->pos;

		elementInFocus->onFocus.call(elementInFocus, clickedPosRelativeElement);
	}
}
void Grid_Dispatch_onFocusLost(void* elementPtr, point clickedPos)
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

			presentChild->onFocusLost.call(presentChild, focusLostPosRelativeElement);
		}
	}
}
void Grid_Dispatch_onLeftButtonDown(void* elementPtr, point clickedPos)
{
	Grid* leftButtonDownedGrid = static_cast<Grid*>(elementPtr);
	controlElement* onLeftButtonDownedElement = Grid_getElementsInPos(leftButtonDownedGrid, clickedPos);

	if (onLeftButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonDownedElement->pos;

		onLeftButtonDownedElement->onLeftButtonDown.call(onLeftButtonDownedElement, clickedPosRelativeElement);
	}
}
void Grid_Dispatch_onLeftButtonUp(void* elementPtr, point clickedPos)
{
	Grid* leftButtonUpedGrid = static_cast<Grid*>(elementPtr);
	controlElement* onLeftButtonUppedElement = Grid_getElementsInPos(leftButtonUpedGrid, clickedPos);

	if (onLeftButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onLeftButtonUppedElement->pos;

		onLeftButtonUppedElement->onLeftButtonUp.call(onLeftButtonUppedElement, clickedPosRelativeElement);
	}
}
void Grid_Dispatch_onRightButtonDown(void* elementPtr, point clickedPos)
{
	Grid* rightButtonDownedGrid = static_cast<Grid*>(elementPtr);
	controlElement* onRightButtonDownedElement = Grid_getElementsInPos(rightButtonDownedGrid, clickedPos);

	if (onRightButtonDownedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonDownedElement->pos;

		onRightButtonDownedElement->onRightButtonDown.call(onRightButtonDownedElement, clickedPosRelativeElement);
	}
}
void Grid_Dispatch_onRightButtonUp(void* elementPtr, point clickedPos)
{
	Grid* rightButtonUpedGrid = static_cast<Grid*>(elementPtr);
	controlElement* onRightButtonUppedElement = Grid_getElementsInPos(rightButtonUpedGrid, clickedPos);

	if (onRightButtonUppedElement != NULL)
	{
		point clickedPosRelativeElement = clickedPos - onRightButtonUppedElement->pos;

		onRightButtonUppedElement->onRightButtonUp.call(onRightButtonUppedElement, clickedPosRelativeElement);
	}
}

void Grid_Dispatch_onKeyDown(void* elementPtr, char key)
{
	Grid* keyDownedGrid = static_cast<Grid*>(elementPtr);

	for (int i = 0; i < keyDownedGrid->getRowsCount(); i++)
	{
		for (int j = 0; j < keyDownedGrid->getColumnsCount(); j++)
		{
			controlElement* presentChild = keyDownedGrid->getChild(i, j);
			if (presentChild == NULL)
				return;

			presentChild->onKeyDown.call(presentChild, key);
		}
	}
}

void Grid_Dispatch_onKeyUp(void* elementPtr, char key)
{
	Grid* keyDownedGrid = static_cast<Grid*>(elementPtr);

	for (int i = 0; i < keyDownedGrid->getRowsCount(); i++)
	{
		for (int j = 0; j < keyDownedGrid->getColumnsCount(); j++)
		{
			controlElement* presentChild = keyDownedGrid->getChild(i, j);
			if (presentChild == NULL)
				return;

			presentChild->onKeyUp.call(presentChild, key);
		}
	}
}

void Grid_Dispatch_beforeDraw(void* elementPtr)
{
	Grid* keyDownedGrid = static_cast<Grid*>(elementPtr);

	for (int i = 0; i < keyDownedGrid->getRowsCount(); i++)
	{
		for (int j = 0; j < keyDownedGrid->getColumnsCount(); j++)
		{
			controlElement* presentChild = keyDownedGrid->getChild(i, j);
			if (presentChild == NULL)
				return;

			presentChild->beforeDraw.call(presentChild);
		}
	}
}

void Grid_Dispatch_afterDraw(void* elementPtr)
{
	Grid* keyDownedGrid = static_cast<Grid*>(elementPtr);

	for (int i = 0; i < keyDownedGrid->getRowsCount(); i++)
	{
		for (int j = 0; j < keyDownedGrid->getColumnsCount(); j++)
		{
			controlElement* presentChild = keyDownedGrid->getChild(i, j);
			if (presentChild == NULL)
				return;

			presentChild->afterDraw.call(presentChild);
		}
	}
}