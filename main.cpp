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
			((eventShowClass*)elementPtr)->needToDraw = true;
		});
		onFocusLost.add([](void* elementPtr, point focusedMousePoint)
		{
			((eventShowClass*)elementPtr)->insertItem("onFocusLost", 0);
			((eventShowClass*)elementPtr)->needToDraw = true;
		});
		onClick.add([](void* elementPtr, point focusedMousePoint)
		{
			((eventShowClass*)elementPtr)->insertItem("onCilick", 1);
			((eventShowClass*)elementPtr)->needToDraw = true;
		});
		onLeftButtonDown.add([](void* elementPtr, point focusedMousePoint)
		{
			((eventShowClass*)elementPtr)->insertItem("onLeftButtonDown", 2);
			((eventShowClass*)elementPtr)->needToDraw = true;
		});
		onLeftButtonUp.add([](void* elementPtr, point focusedMousePoint)
		{
			((eventShowClass*)elementPtr)->insertItem("onLeftButtonUp", 2);
			((eventShowClass*)elementPtr)->needToDraw = true;
		});
		onRightButtonDown.add([](void* elementPtr, point focusedMousePoint)
		{
			((eventShowClass*)elementPtr)->insertItem("onRightButtonDown", 2);
			((eventShowClass*)elementPtr)->needToDraw = true;
		});
		onRightButtonUp.add([](void* elementPtr, point focusedMousePoint)
		{
			((eventShowClass*)elementPtr)->insertItem("onRightButtonUp", 2);
			((eventShowClass*)elementPtr)->needToDraw = true;
		});
		onKeyDown.add([](void* elementPtr, char key)
		{
			((eventShowClass*)elementPtr)->insertItem("onKeyDown", 3);
			((eventShowClass*)elementPtr)->needToDraw = true;
		});
		onKeyUp.add([](void* elementPtr, char key)
		{
			((eventShowClass*)elementPtr)->insertItem("onKeyUp", 3);
			((eventShowClass*)elementPtr)->needToDraw = true;
		});
		afterDraw.add([](void* elementPtr)
		{
			for (int i = 0; i < 4; i++)
			{
				((eventShowClass*)elementPtr)->insertItem("-", i);
			}
		});
	}

	void Draw(rectangle& drawRect)
	{
		//...
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