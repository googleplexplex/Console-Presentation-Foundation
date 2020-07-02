#include <iostream>
#define SHOW_MOUSE
#include "include.hpp"
using namespace std;

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
			thisObject.setAllTreeInDrawQueue();
		});
		onFocusLost.add([](void* elementPtr, point focusedMousePoint)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(0, "onFocusLost");
			thisObject.setAllTreeInDrawQueue();
		});
		onClick.add([](void* elementPtr, point focusedMousePoint)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(1, "onClick");
			thisObject.setAllTreeInDrawQueue();
		});
		onLeftButtonDown.add([](void* elementPtr, point focusedMousePoint)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(2, "onLeftButtonDown");
			thisObject.setAllTreeInDrawQueue();
		});
		onLeftButtonUp.add([](void* elementPtr, point focusedMousePoint)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(2, "onLeftButtonUp");
			thisObject.setAllTreeInDrawQueue();
		});
		onRightButtonDown.add([](void* elementPtr, point focusedMousePoint)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(3, "onRightButtonDown");
			thisObject.setAllTreeInDrawQueue();
		});
		onRightButtonUp.add([](void* elementPtr, point focusedMousePoint)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(3, "onRightButtonUp");
			thisObject.setAllTreeInDrawQueue();
		});
		onKeyDown.add([](void* elementPtr, char key)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(4, "onKeyDown");
			thisObject.setAllTreeInDrawQueue();
		});
		onKeyUp.add([](void* elementPtr, char key)
		{
			eventShowClass& thisObject = *((eventShowClass*)elementPtr);
			thisObject.setItem(4, "onKeyUp");
			thisObject.setAllTreeInDrawQueue();
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
	Grid mainCont(4, 5, true);
	mainCont.setWidth(2, 2);
	mainCont.setAsMainContainer();

	eventShowClass eventShow;
	eventShow.setParent(mainCont);

	eventDispatcherMainLoop();

	return 0;
}