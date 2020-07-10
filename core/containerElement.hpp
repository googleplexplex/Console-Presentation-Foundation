#pragma once
#include "controlElement.hpp"

//Container Interface
class containerElement : public controlElement
{
public:
	virtual void addChild(controlElement& addedElement) = 0;
	virtual void delChild(controlElement& deletedChild) = 0;
	virtual unsigned int getChildsCount() = 0;

	friend void setMainContainer(containerElement& newMainContainer);
	void setAsMainContainer()
	{
		setMainContainer(*this);
	}
}; 

void _setParent(void* _child, void* _parent)
{
	containerElement* parent = static_cast<containerElement*>(_parent);
	controlElement* child = static_cast<containerElement*>(_child);
	parent->addChild(*child);
}


containerElement* mainContainer = NULL;
void setMainContainer(containerElement& newMainContainer)
{
	mainContainer = &newMainContainer;
	mainContainer->pos = { 0, 0 };
	mainContainer->size = toPoint(getConsoleSize());
	mainContainer->parent = NULL;
}

void drawAllElements()
{
	if (mainContainer == NULL)
		return;

	if(mainContainer->Visible)
		mainContainer->Draw();
}

void redrawAllElements()
{
	for (int i = 0; i < elementsToRedraw.count; i++)
	{
		if (elementsToRedraw[i] != NULL && elementsToRedraw[i]->Visible)
		{
			elementsToRedraw[i]->Draw();
		}
	}

	elementsToRedraw.clean();
}