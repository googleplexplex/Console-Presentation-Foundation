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
public:
	UniformGrid(point _pos, point _size, symbolColor _background = black)
	{
		pos = _pos;
		size = _size;
		background = _background;

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

	void addChild(controlElement* addedChild)
	{
		childs[0][0] = addedChild;
		addedChild->parent = this;
	}

	void delChild(controlElement* deletedChild)
	{
		int findResult = -1;
		for (int i = 0; i < childs.count; i++)
		{
			findResult = childs[i].find(deletedChild);
			if (findResult != -1)
			{
				childs[i].del(findResult);
				deletedChild->parent = NULL;
				return;
			}
		}
	}

	controlElement* getChild(int index)
	{
		int gettedChildRow = index / getColumnsCount();
		int gettedChildColumn = index % getColumnsCount();

		return childs[gettedChildRow][gettedChildColumn];
	}

	unsigned int getChildsCount()
	{
		return getRowsCount() * getColumnsCount();
	}

	void Draw(rectangle& drawFrame)
	{
		rectangle thisElementRect = getRect();
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
		oneElementSize = { size.x / getColumnsCount(), size.y / getRowsCount() };
		point presentPos;

		for (int i = 0; i < getRowsCount(); i++)
		{
			presentPos = pos;
			for (int j = 0; j < getColumnsCount(); j++)
			{
				if (childs[i][j] != NULL)
				{
					childs[i][j]->pos = presentPos;
					childs[i][j]->size = oneElementSize;
				}

				pos.x += oneElementSize.x;
			}
		}
	}

	int getRowsCount()
	{
		return childs.count;
	}
	int getColumnsCount()
	{
		return childs[0].count;
	}

	void addRow()
	{
		dynamicArray<controlElement*> addedRow;
		addedRow.add(NULL, getRowsCount() + 1);
		childs.add(addedRow);
		updatePositions();
	}
	void addColumn()
	{
		for (int i = 0; i < getRowsCount(); i++)
		{
			childs[i].add(NULL);
		}
		updatePositions();
	}
	void addControlElement(controlElement& element, int row, int column)
	{
		childs[row][column] = &element;
	}

	void delControlElement(int row, int column)
	{
		childs[row][column] = NULL;
	}
	void delRow(int rowIndex)
	{
		childs.del(rowIndex);
		updatePositions();
	}
	void delColumn(int columnIndex)
	{
		for (int i = 0; i < getRowsCount(); i++)
		{
			childs[i].del(columnIndex);
		}
		updatePositions();
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