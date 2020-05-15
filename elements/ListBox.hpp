#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"
#include "helpers\dynamicArray.hpp"


void listBox_onClick(void* listBoxPtr, point clickedPos);

class ListBox : controlElement {
	dynamicArray<char*> items;
	int selectedItem = -1;
	symbolColor itemTextColor;
	symbolColor itemFoneColor;
	symbolColor selectedItemTextColor;
	symbolColor selectedItemFoneColor;
	symbolColor backgroundColor;
public:
	ListBox(point _pos, int _sizex, int _elementsCount, symbolColor _itemTextColor = white, symbolColor _itemFoneColor = black, symbolColor _selectedItemTextColor = black, symbolColor _selectedItemFoneColor = white, symbolColor _backgroundColor = black, onFocus_DelegateType _onFocus = NULL, onFocus_DelegateType _onFocusLost = NULL, onClick_DelegateType _onClick = NULL)
	{
		pos = _pos;
		size = { _sizex, _elementsCount };
		itemTextColor = _itemTextColor;
		itemFoneColor = _itemFoneColor;
		selectedItemTextColor = _selectedItemTextColor;
		selectedItemFoneColor = _selectedItemFoneColor;
		backgroundColor = _backgroundColor;

		onClickSystemDelegate = &listBox_onClick;
		onFocusSystemDelegate = NULL;
		onFocusLostSystemDelegate = NULL;

		onClickEvent += _onClick;
		onFocusEvent += _onFocus;
		onFocusLostEvent += _onFocusLost;
	}

	void Draw()
	{
		consoleCursorInfo save;
		save.getAndReset();

		for (int i = 0; i < items.count; i++)
		{
			setTo(pos.x, pos.y + i);
			int itemLenght = strlen(items[i]);

			if (i != selectedItem)
				setSymbolColor(itemTextColor, itemFoneColor);
			else
				setSymbolColor(selectedItemTextColor, selectedItemFoneColor);

			if (itemLenght > size.x)
			{
				consolePrintStr(items[i], itemLenght - 3);
				consolePrintStr((char*)"...", 3);
			}
			else {
				consolePrintStr(items[i], itemLenght);
				consolePrintLine(size.x - itemLenght, filledCharacter_1_5);
			}
		}

		setSymbolFullColor(backgroundColor);
		for (int i = items.count; i < size.y; i++)
		{
			setTo(pos.x, pos.y + i);
			consolePrintLine(size.x, filledCharacter_5_5);
		}

		save.apply();
	}
	bool entersTheArea(int x, int y)
	{
		return getBorder(x, pos.x, pos.x + size.x - 1)
			&& getBorder(y, pos.y, pos.y + size.y - 1);
	}
	bool entersTheArea(point point)
	{
		return entersTheArea(point.x, point.y);
	}

	void addItem(char* item)
	{
		items.add(item);
	}
	void deleteItem(char* item)
	{
		items.delElement(item);
	}
	void popItem()
	{
		items.delLast();
	}
	void clearItems()
	{
		items.clean();
	}

	void setPos(int x, int y)
	{
		pos.x = x;
		pos.y = y;
	}

	point getPos()
	{
		return pos;
	}
	unsigned int getItemsCount()
	{
		return items.count;
	}

	friend void listBox_onClick(void* listBoxPtr, point clickedPos);
};

void listBox_onClick(void* listBoxPtr, point clickedPos)
{
	ListBox* listBox = (ListBox*)listBoxPtr;

	if (clickedPos.y < listBox->items.count)
	{
		listBox->selectedItem = clickedPos.y;
	}
}