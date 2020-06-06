#pragma once
#include "controlElement.hpp"

class containerElement : public controlElement
{
public:
	dynamicArray<controlElement*> childs;

	virtual void addControlElement(controlElement* element) = 0;
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
	virtual void delControlElement(controlElement* element) = 0;
	void delChild(controlElement* deleteddChild)
	{
		childs.del(deleteddChild);
		deleteddChild->parent = this;
	}
	void delChild(containerElement* deleteddChild)
	{
		childs.del(deleteddChild);
		deleteddChild->parent = this;
	}

	controlElement* getChild(int index)
	{
		return childs[index];
	}
}; 
void _setParent(void* _child, void* _parent)
{
	containerElement* parent = static_cast<containerElement*>(_parent);
	controlElement* child = static_cast<containerElement*>(_child);
	parent->addControlElement(child);
}

containerElement* mainContainer;
void setMainContainer(containerElement& newMainContainer)
{
	mainContainer = &newMainContainer;
	mainContainer->pos = { 0, 0 };
	mainContainer->size = toPoint(getConsoleSize());
	mainContainer->parent = NULL;
}

void drawAllElements()
{
	rectangle mainContainerRect = mainContainer->getRect();
	if(mainContainer->Visible)
		mainContainer->Draw(mainContainerRect);
}