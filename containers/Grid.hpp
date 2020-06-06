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
	dynamicArray<Canvas*> elements; //?
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

	void Draw(rectangle& drawFrame)
	{
		rectangle thisElementRect = getRect();
		consolePrintRect(drawFrame, thisElementRect, filledCharacter_5_5, collectColor(black, background));

		for (int i = 0; i < childs.count; i++)
		{
			if (childs[i]->Visible)
				childs[i]->Draw(thisElementRect);
		}
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

	for (int i = 0; i < focusLostedGrid->childs.count; i++)
	{
		controlElement* presentChild = focusLostedGrid->childs[i];
		point focusLostPosRelativeElement = clickedPos - presentChild->pos;

		callDelegate<void*, point>(presentChild->onFocusLostSystemDelegate, presentChild, focusLostPosRelativeElement);
		presentChild->onFocusLostEvent.call(presentChild, focusLostPosRelativeElement);
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

	for (int i = 0; i < keyDownedGrid->childs.count; i++)
	{
		controlElement* presentChild = keyDownedGrid->childs[i];
		callDelegate<void*, char>(presentChild->onKeyDownSystemDelegate, presentChild, key);
	}
}

void Grid_onKeyUp(void* elementPtr, char key)
{
	Grid* keyDownedGrid = static_cast<Grid*>(elementPtr);

	for (int i = 0; i < keyDownedGrid->childs.count; i++)
	{
		controlElement* presentChild = keyDownedGrid->childs[i];
		callDelegate<void*, char>(presentChild->onKeyUpSystemDelegate, presentChild, key);
	}
}