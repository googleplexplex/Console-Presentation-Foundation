#pragma once
#include "helpers\dynamicArray.hpp"
#include "helpers\helpFunctions.hpp"
#include "core\event.hpp"

dynamicArray<void*> controlElements; //TOHIDE

class controlElement
{
public:
	point pos;
	point size;
	//The delegate of on click event should look like "void onClick(void* obj, point clickedPoint)"
	onClickEvent onClickEvent;
	//void(*onLeftButtonClick_Delegate)(void*, point); //TODO
	//The delegate of on focus events should look like "void onFocus(void* obj)"
	onFocusEvent onFocusEvent;
	onFocusLostEvent onFocusLostEvent;

	controlElement()
	{
		controlElements.add((void*)this);
	}
	~controlElement()
	{
		controlElements.delElement((void*)this);
	}

	virtual void Draw() = 0;
	virtual bool entersTheArea(point point) = 0;
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