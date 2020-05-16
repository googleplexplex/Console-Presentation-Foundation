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

	//The delegate of on click event should look like "void onClick(void* element, point clickedPoint)"
	onClick_EventType onClickEvent;
	//void(*onLeftButtonClick_Delegate)(void*, point); //TODO
	//The delegate of on focus events should look like "void onFocus(void* element)"
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