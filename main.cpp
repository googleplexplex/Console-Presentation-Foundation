#define SHOW_MOUSE
#include "include.hpp"

class eventShowClass : public ListBox
{
public:
	eventShowClass()
	{
		onClick.del(listBox_onClick);

		for (int i = 0; i < 5; i++)
		{
			addItem("-");
		}

		onFocus.add([](void* elementPtr, point focusedMousePoint)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(0, "onFocus");
			thisObject.addInRedrawQueue();
		});
		onFocusLost.add([](void* elementPtr, point focusedMousePoint)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(0, "onFocusLost");
			thisObject.addInRedrawQueue();
		});
		onClick.add([](void* elementPtr, point focusedMousePoint)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(1, "onClick");
			thisObject.addInRedrawQueue();
		});
		onLeftButtonDown.add([](void* elementPtr, point focusedMousePoint)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(2, "onLeftButtonDown");
			thisObject.addInRedrawQueue();
		});
		onLeftButtonUp.add([](void* elementPtr, point focusedMousePoint)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(2, "onLeftButtonUp");
			thisObject.addInRedrawQueue();
		});
		onRightButtonDown.add([](void* elementPtr, point focusedMousePoint)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(3, "onRightButtonDown");
			thisObject.addInRedrawQueue();
		});
		onRightButtonUp.add([](void* elementPtr, point focusedMousePoint)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(3, "onRightButtonUp");
			thisObject.addInRedrawQueue();
		});
		onKeyDown.add([](void* elementPtr, char key)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(4, "onKeyDown");
			thisObject.addInRedrawQueue();
		});
		onKeyUp.add([](void* elementPtr, char key)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(4, "onKeyUp");
			thisObject.addInRedrawQueue();
		});
		afterDraw.add([](void* elementPtr)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			for (int i = 0; i < 5; i++)
			{
				thisObject.setItem(i, "-");
			}
		});
	}
};


int main(void)
{
	Grid mainGrid(4, 5, true);
	mainGrid.setWidth(2, 2);
	mainGrid.setAsMainContainer();

	Button buttonExample((char*)"Button", [](void* elementPtr, point clickPos)
		{
			Button& thisObject = *((Button*)elementPtr);
			
			if (thisObject.background != blue)
				thisObject.setBackground(blue);
			else
				thisObject.setBackground(red);
		});
	buttonExample.setParent(mainGrid);

	eventShowClass eventShow;
	eventShow.setParent(mainGrid);

	eventDispatcherMainLoop();

	return 0;
}