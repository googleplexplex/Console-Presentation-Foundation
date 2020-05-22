#pragma once
#include "controlElement.hpp"

class containerElement : public controlElement
{
public:
	dynamicArray<controlElement*> childs;

	void addChild(controlElement* addedChild)
	{
		childs.add(addedChild);
		addedChild->parent = this;
	}
	void addChild(containerElement* addedChild)
	{
		childs.add(addedChild);
		addedChild->parent = this;
	}
	void delChild(controlElement* deleteddChild)
	{
		childs.delElement(deleteddChild);
		deleteddChild->parent = this;
	}
	void delChild(containerElement* deleteddChild)
	{
		childs.delElement(deleteddChild);
		deleteddChild->parent = this;
	}

	controlElement* getChild(int index)
	{
		return childs[index];
	}
}; 
void _setParent(void* _child, void* _parent)
{
	((containerElement*)_parent)->childs.add((controlElement*)_child);
	((controlElement*)_child)->parent = _parent;
}


containerElement* mainContainer;
void setMainContainer(containerElement* newMainContainer)
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