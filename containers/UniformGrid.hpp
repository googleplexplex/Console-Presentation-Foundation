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

struct UniformGridElement
{
	controlElement* element;
	unsigned int span;
};
const UniformGridElement emptyUniformGridElement = { NULL, 0 };
const UniformGridElement* emptyUniformGridElementPtr = &emptyUniformGridElement;

class UniformGrid : public containerElement {
	dynamicArray<dynamicArray<UniformGridElement*>> childs;
	dynamicArray<unsigned int> widths;
	dynamicArray<unsigned int> heights;
	point onePointSize;
public:
	UniformGrid(point _pos, point _size, symbolColor _background = black)
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

	void addChild(controlElement* addedChild, unsigned int span)
	{
		if (childs.count == 0)
			addRow();

		if (childs[0][0] != emptyUniformGridElementPtr)
			childs[0][0]->element->parent = NULL;

		childs[0][0] = new UniformGridElement({ addedChild, span });
		addedChild->parent = this;

		updatePositions();
	}
	void addChild(controlElement* addedChild)
	{
		addChild(addedChild, 1);
	}

	void delChild(controlElement* deletedChild)
	{
		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j]->element == deletedChild)
				{
					childs[i][j] = (UniformGridElement*)(emptyUniformGridElementPtr);
				}
			}
		}
	}

	void addControlElement(controlElement& element, unsigned int span, int row, int column)
	{
		if (childs.canGet(row))
			if (childs[row].canGet(column))
				childs[row][column] = new UniformGridElement({ &element, span });

		updatePositions();
	}
	void addControlElement(controlElement& element, int row, int column)
	{
		addControlElement(element, 1, row, column);
	}

	void delControlElement(int row, int column)
	{
		if(childs.canGet(row))
			if(childs[row].canGet(column))
				childs[row][column] = (UniformGridElement*)(emptyUniformGridElementPtr);
	}

	controlElement* getControlElement(int row, int column)
	{
		if (childs.canGet(row))
			if (childs[row].canGet(column))
				if(childs[row][column] != (UniformGridElement*)(emptyUniformGridElementPtr))
					return childs[row][column]->element;

		return NULL;
	}

	unsigned int getControlElementSpan(int row, int column)
	{
		if (childs.canGet(row))
			if (childs[row].canGet(column))
				if(childs[row][column] != (UniformGridElement*)(emptyUniformGridElementPtr))
					return childs[row][column]->span;

		return 0;
	}

	controlElement* getChild(int index)
	{
		int gettedChildRow = index / getColumnsCount();
		int gettedChildColumn = index % getColumnsCount();

		if(childs.canGet(gettedChildRow))
			if(childs[gettedChildRow].canGet(gettedChildColumn))
				if(childs[gettedChildRow][gettedChildColumn] != (UniformGridElement*)(emptyUniformGridElementPtr))
					return childs[gettedChildRow][gettedChildColumn]->element;

		return NULL;
	}

	unsigned int getChildsCount()
	{
		return getRowsCount() * getColumnsCount();
	}

	void Draw(rectangle& drawFrame)
	{
		rectangle thisElementRect = getRect();
		consolePrintRect(drawFrame, thisElementRect, filledCharacter_5_5, collectColor(black, background));
		//showGrid();

		for (int i = 0; i < getRowsCount(); i++)
		{
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j] != (UniformGridElement*)(emptyUniformGridElementPtr) && childs[i][j]->element->Visible)
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
				if (childs[i][j] != (UniformGridElement*)(emptyUniformGridElementPtr))
				{
					point presentSize = { widths[j] * onePointSize.x, heights[i] * onePointSize.y };
					childs[i][j]->element->pos = presentPos;

					if(childs[i][j]->span == 1)
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

	void setWidth(unsigned int elementIndex, unsigned int newWidth)
	{
		widths[elementIndex] = newWidth;

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
		return size / gridSizeInPoints;
	}


	int getRowsCount()
	{
		return childs.count;
	}

	int getColumnsCount()
	{
		return childs[0].count;
	}

	bool isIdentifyed()
	{
		return childs != NULL;
	}

	void addRow(unsigned int size)
	{
		dynamicArray<UniformGridElement*> addedRow;

		if (isIdentifyed())
			addedRow.set((UniformGridElement*)(emptyUniformGridElementPtr), getColumnsCount());
		else
			addedRow.set((UniformGridElement*)(emptyUniformGridElementPtr));

		childs.add(addedRow);
		heights.add(size);

		updatePositions();
	}
	void addRow()
	{
		addRow(1);
	}

	void addRows(int rowsCount, unsigned int rowsSize)
	{
		heights.add(rowsSize, rowsCount);

		if (!isIdentifyed()) //!
		{
			dynamicArray<UniformGridElement*> addedRow;
			addedRow.set((UniformGridElement*)(emptyUniformGridElementPtr));
			childs.add(addedRow);
			rowsCount--;
		}

		for (int i = 0; i < rowsCount; i++)
		{
			dynamicArray<UniformGridElement*> addedRow;
			addedRow.set((UniformGridElement*)(emptyUniformGridElementPtr), getColumnsCount());
			childs.add(addedRow);
		}

		updatePositions();
	}
	void addRows(int rowsCount)
	{
		addRows(rowsCount, 1);
	}

	void delRow(int rowIndex)
	{
		heights.delElementIn(rowIndex);
		childs.delElementIn(rowIndex);
		updatePositions();
	}

	void addColumn(unsigned int size)
	{
		if (!isIdentifyed())
			return;

		for (int i = 0; i < getRowsCount(); i++)
		{
			childs[i].add((UniformGridElement*)(emptyUniformGridElementPtr));
		}
		widths.add(size);

		updatePositions();
	}
	void addColumn()
	{
		addColumn(1);
	}

	void addColumns(int columnsCount, int columnsSize)
	{
		if (!isIdentifyed())
			return;

		for (int i = 0; i < getRowsCount(); i++)
		{
			childs[i].add((UniformGridElement*)(emptyUniformGridElementPtr), columnsCount);
		}
		widths.add(columnsSize, columnsCount);

		updatePositions();
	}
	void addColumns(int columnsCount)
	{
		addColumns(columnsCount, 1);
	}

	void delColumn(int columnIndex)
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

	void setRowsColumnsCount(int rowsCount, int columnsCount, unsigned int size)
	{
		for (int i = 0; i < rowsCount; i++)
		{
			dynamicArray<UniformGridElement*> addedRow;
			addedRow.set((UniformGridElement*)(emptyUniformGridElementPtr), columnsCount);
			childs.add(addedRow);
		}
		heights.set(size, rowsCount);
		widths.set(size, columnsCount);

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

controlElement* UniformGrid_getElementsInPos(UniformGrid* container, point pos)
{
	for (int i = 0; i < container->getRowsCount(); i++)
	{
		for (int j = 0; j < container->getColumnsCount(); j++)
		{
			controlElement* presentChild = container->getControlElement(i, j);

			if (presentChild != NULL && presentChild->entersTheArea(pos))
			{
				return presentChild;
			}
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