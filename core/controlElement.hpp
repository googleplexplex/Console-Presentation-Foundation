#pragma once
#include "helpers\dynamicArray.hpp"
#include "helpers\helpFunctions.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"

dynamicArray<void*> controlElements; //TOHIDE

class controlElement
{
public:
	point pos;
	point size;
	symbolColor background;

	onClick_EventType onClickEvent;
	//void(*onLeftButtonClick_Delegate)(void*, point); //TODO
	onFocus_EventType onFocusEvent;
	onFocusLost_EventType onFocusLostEvent;

	onClick_DelegateType onClickSystemDelegate;
	onFocus_DelegateType onFocusSystemDelegate;
	onFocusLost_DelegateType onFocusLostSystemDelegate;

	controlElement()
	{
		controlElements.add((void*)this);
	}
	void registerElement()
	{
		addElementZone({ pos, { pos.x + size.x, pos.y + size.y } });
	}
	~controlElement()
	{
		controlElements.delElement((void*)this);
	}

	virtual void Draw() = 0;
	virtual bool entersTheArea(point point) = 0;

	void setPos(int x, int y)
	{
		pos.x = x;
		pos.y = y;
	}
	void setSize(int x, int y)
	{
		size.x = x;
		size.y = y;
	}
	void setBackground(symbolColor _textFone)
	{
		background = _textFone;
	}

	point getPos()
	{
		return pos;
	}
	point getSize()
	{
		return size;
	}
	symbolColor getBackground()
	{
		return background;
	}
};

dynamicArray<controlElement*> getControlElementIn(point foundedPoint)
{
	dynamicArray<controlElement*> result;

	for (int i = 0; i < controlElements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)(controlElements[i]);

		if (presentElementPtr->entersTheArea(foundedPoint))
		{
			result.add(presentElementPtr);
		}
	}

	return result;
}

inline controlElement* getControlElement(unsigned int index)
{
	return (controlElement*)(controlElements[index]);
}

void drawAllElements()
{
	for (int i = 0; i < controlElements.count; i++)
	{
		getControlElement(i)->Draw();
	}
}