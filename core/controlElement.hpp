#pragma once
#include "helpers\dynamicArray.hpp"

dynamicArray<void*> controlElements; //TOHIDE

class controlElement
{
public:
	POINT pos;
	POINT size;
	void(*onClick_Delegate)(void*, POINT); //The delegate should look like this "void onClick(void* obj, POINT clickedPoint)"
	//void(*onLeftButtonClick_Delegate)(void*, POINT);
	void(*onFocus_Delegate)(void*);
	void(*onFocusLost_Delegate)(void*);

	controlElement()
	{
		controlElements.add((void*)this);
	}
	~controlElement()
	{
		controlElements.delElement((void*)this);
	}

	virtual void Draw() = 0;
	virtual bool entersTheArea(POINT point) = 0;
};

dynamicArray<controlElement*> getControlElementIn(POINT foundedPoint)
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