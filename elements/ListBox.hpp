#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"
#include "helpers\dynamicArray.hpp"


void listBox_onClick(void* listBoxPtr, point clickedPos);

class ListBox : public controlElement {
	dynamicArray<char*> items;
	int selectedItem;
	symbolColor itemTextColor;
	symbolColor itemFoneColor;
	symbolColor selectedItemTextColor;
	symbolColor selectedItemFoneColor;
public:
	ListBox(point _pos, int _sizex, int _elementsCount, symbolColor _itemTextColor = white, symbolColor _itemFoneColor = black, symbolColor _selectedItemTextColor = black, symbolColor _selectedItemFoneColor = white, symbolColor _background = black)
	{
		pos = _pos;
		size = { _sizex, _elementsCount };
		selectedItem = -1;
		itemTextColor = _itemTextColor;
		itemFoneColor = _itemFoneColor;
		selectedItemTextColor = _selectedItemTextColor;
		selectedItemFoneColor = _selectedItemFoneColor;
		background = _background;

		onClickSystemDelegate = &listBox_onClick;

		registerElement();
	}

	void Draw(rectangle drawFrame)
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
				consolePrintStr(drawFrame, items[i], itemLenght - 3);
				consolePrintStr(drawFrame, (char*)"...", 3);
			}
			else {
				consolePrintStr(drawFrame, items[i], itemLenght);
				consolePrintLine(drawFrame, size.x - itemLenght, filledCharacter_1_5);
			}
		}

		setSymbolFullColor(background);
		for (int i = items.count; i < size.y; i++)
		{
			setTo(pos.x, pos.y + i);
			consolePrintLine(drawFrame, size.x, filledCharacter_5_5);
		}

		save.apply();
	}
	bool entersTheArea(point point)
	{
		return getBorder(point.x, pos.x, pos.x + size.x - 1)
			&& getBorder(point.y, pos.y, pos.y + size.y - 1);
	}

	void addItem(char* item)
	{
		items.add(item);
	}
	void addItem(const char* item)
	{
		items.add((char*)item);
	}
	void deleteItem(char* item)
	{
		items.delElement(item);
	}
	void deleteItem(const char* item)
	{
		items.delElement((char*)item);
	}
	void popItem()
	{
		items.delLast();
	}
	void clearItems()
	{
		items.clean();
	}
	
	unsigned int getItemsCount()
	{
		return items.count;
	}
	char* getElement(int index)
	{
		return items[index];
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