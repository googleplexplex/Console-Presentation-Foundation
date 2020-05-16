#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"


void Canvas_onClick(void* elementPtr, point clickedPos);
void Canvas_onFocus(void* elementPtr);
void Canvas_onFocusLost(void* elementPtr);

class Canvas : controlElement {
	dynamicArray<controlElement*> elements;
	symbolColor background;
public:
	Canvas(point _pos, point _size, symbolColor _background = black, onClick_DelegateType _onClick = NULL, onFocus_DelegateType _onFocus = NULL, onFocusLost_DelegateType _onFocusLost = NULL)
	{
		pos = _pos;
		size = _size;
		background = _background;

		onClickSystemDelegate = NULL;
		onFocusSystemDelegate = NULL;
		onFocusLostSystemDelegate = NULL;

		onClickEvent += _onClick;
		onFocusEvent += _onFocus;
		onFocusLostEvent += _onFocusLost;

		registerElement();
	}

	void Draw()
	{
		consoleCursorInfo save;
		save.getAndReset();

		//...

		save.apply();
	}
	bool entersTheArea(point point)
	{
		return getBorder(point.x, pos.x, pos.x + size.x - 1)
			&& getBorder(point.y, pos.y, pos.y + size.y - 1);
	}
};

void Canvas_onClick(void* elementPtr, point clickedPos)
{
	//...
}
void Canvas_onFocus(void* elementPtr)
{
	//...
}
void Canvas_onFocusLost(void* elementPtr)
{
	//...
}