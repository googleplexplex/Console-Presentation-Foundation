#pragma once
#include "controlElement.hpp"

class containerElement : public controlElement
{
public:
	virtual void addChild(controlElement* addedChild) = 0;

	virtual void delChild(controlElement* deleteddChild) = 0;

	virtual controlElement* getChild(int index) = 0;
	virtual unsigned int getChildsCount() = 0;
}; 

void _setParent(void* _child, void* _parent)
{
	containerElement* parent = static_cast<containerElement*>(_parent);
	controlElement* child = static_cast<containerElement*>(_child);
	parent->addChild(child);
}

void addChild(containerElement* parent, dynamicArray<controlElement*>& parentChilds, controlElement* addedChild)
{
	parentChilds.add(addedChild);
	addedChild->parent = parent;
}

void delChild(containerElement* parent, dynamicArray<controlElement*>& parentChilds, controlElement* deletedChild)
{
	parentChilds.del(deletedChild);
	deletedChild->parent = parent;
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