#include <iostream>
#define SHOW_MOUSE
#include "include.hpp"
using namespace std;

class eventShowClass : public ListBox
{
public:
	eventShowClass()
		: ListBox()
	{
		onClick.del(listBox_onClick);

		for (int i = 0; i < 4; i++)
		{
			addItem("-");
		}

		onFocus.add([](void* elementPtr, point focusedMousePoint)
		{
			((eventShowClass*)elementPtr)->insertItem("onFocus", 0);
			((eventShowClass*)elementPtr)->setAllTreeInDrawQueue();
		});
		onFocusLost.add([](void* elementPtr, point focusedMousePoint)
		{
			((eventShowClass*)elementPtr)->insertItem("onFocusLost", 0);
			((eventShowClass*)elementPtr)->setAllTreeInDrawQueue();
		});
		onClick.add([](void* elementPtr, point focusedMousePoint)
		{
			((eventShowClass*)elementPtr)->insertItem("onCilick", 1);
			((eventShowClass*)elementPtr)->setAllTreeInDrawQueue();
		});
		onLeftButtonDown.add([](void* elementPtr, point focusedMousePoint)
		{
			((eventShowClass*)elementPtr)->insertItem("onLeftButtonDown", 2);
			((eventShowClass*)elementPtr)->setAllTreeInDrawQueue();
		});
		onLeftButtonUp.add([](void* elementPtr, point focusedMousePoint)
		{
			((eventShowClass*)elementPtr)->insertItem("onLeftButtonUp", 2);
			((eventShowClass*)elementPtr)->setAllTreeInDrawQueue();
		});
		onRightButtonDown.add([](void* elementPtr, point focusedMousePoint)
		{
			((eventShowClass*)elementPtr)->insertItem("onRightButtonDown", 2);
			((eventShowClass*)elementPtr)->setAllTreeInDrawQueue();
		});
		onRightButtonUp.add([](void* elementPtr, point focusedMousePoint)
		{
			((eventShowClass*)elementPtr)->insertItem("onRightButtonUp", 2);
			((eventShowClass*)elementPtr)->setAllTreeInDrawQueue();
		});
		onKeyDown.add([](void* elementPtr, char key)
		{
			((eventShowClass*)elementPtr)->insertItem("onKeyDown", 3);
			((eventShowClass*)elementPtr)->setAllTreeInDrawQueue();
		});
		onKeyUp.add([](void* elementPtr, char key)
		{
			((eventShowClass*)elementPtr)->insertItem("onKeyUp", 3);
			((eventShowClass*)elementPtr)->setAllTreeInDrawQueue();
		});
		afterDraw.add([](void* elementPtr)
		{
			for (int i = 0; i < 4; i++)
			{
				((eventShowClass*)elementPtr)->insertItem("-", i);
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