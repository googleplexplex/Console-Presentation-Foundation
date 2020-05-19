#pragma once
#include "helpers\dynamicArray.hpp"
#include "helpers\helpFunctions.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"

#define GetterOf(type, element)\
type get##element()\
{\
return element;\
}
#define SetterOf(type, element)\
void set##element(type setted##element)\
{\
element = setted##element;\
}

class controlElement
{
public:
	int zIndex = 0;
	point pos;
	point size;
	symbolColor background;

	onFocus_DelegateType onFocusSystemDelegate = NULL;
	onFocusLost_DelegateType onFocusLostSystemDelegate = NULL;
	onClick_DelegateType onClickSystemDelegate = NULL;
	onLeftButtonDown_DelegateType onLeftButtonDownSystemDelegate = NULL;
	onLeftButtonUp_DelegateType onLeftButtonUpSystemDelegate = NULL;
	onRightButtonDown_DelegateType onRightButtonDownSystemDelegate = NULL;
	onRightButtonUp_DelegateType onRightButtonUpSystemDelegate = NULL;

	onFocus_EventType onFocusEvent;
	onFocusLost_EventType onFocusLostEvent;
	onClick_EventType onClickEvent;
	onLeftButtonDown_EventType onLeftButtonDownEvent;
	onLeftButtonUp_EventType onLeftButtonUpEvent;
	onRightButtonDown_EventType onRightButtonDownEvent;
	onRightButtonUp_EventType onRightButtonUpEvent;

	controlElement* parent;
	dynamicArray<controlElement*> childs;

	void registerElement()
	{
		addElementZone({ pos, { pos.x + size.x, pos.y + size.y } });
	}

	virtual void Draw(rectangle drawFrame) = 0;
	virtual bool entersTheArea(point point) = 0;

	void setParent(controlElement* _parent)
	{
		_parent->childs.add(this);
		parent = _parent;
	}
	void addChild(controlElement* addedChild)
	{
		childs.add(addedChild);
		addedChild->parent = this;
	}
	void delChild(controlElement* addedChild)
	{
		childs.delElement(addedChild);
		addedChild->parent = this;
	}
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

	controlElement* getParent()
	{
		return parent;
	}
	controlElement* getChild(int index)
	{
		return childs[index];
	}
	point getPos()
	{
		return pos;
	}
	point getSize()
	{
		return size;
	}
	rectangle getRect()
	{
		return { pos, pos + size };
	}
	symbolColor getBackground()
	{
		return background;
	}
};

controlElement* mainContainer;
void setMainContainer(controlElement* newMainContainer)
{
	mainContainer = newMainContainer;
	mainContainer->pos = { 0, 0 };
	mainContainer->size = toPoint(getConsoleSize());
	mainContainer->parent = NULL;
}

void drawAllElements()
{
	mainContainer->Draw(mainContainer->getRect());
}