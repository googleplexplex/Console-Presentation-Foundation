#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "helpers\IInterpretedToString.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"
#include "helpers\dynamicArray.hpp"

class CharPtr_InterpretedToString : public IInterpretedToString
{
public:
	char* string;

	CharPtr_InterpretedToString()
	{
		string = NULL;
	}
	CharPtr_InterpretedToString(char* string)
	{
		string = stringCopy(string, strlen(string));
	}
	CharPtr_InterpretedToString(char* string, int stringSize)
	{
		string = stringCopy(string, stringSize);
	}
	~CharPtr_InterpretedToString()
	{
		delete[] string;
	}

	char* ToString()
	{
		return string;
	}
};

void listBox_onClick(void* listBoxPtr, point clickedPos);

class ListBox : public controlElement {
	dynamicArray<IInterpretedToString*> items;
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
			int itemLenght = strlen(items[i]->ToString());

			if (i != selectedItem)
				setSymbolColor(itemTextColor, itemFoneColor);
			else
				setSymbolColor(selectedItemTextColor, selectedItemFoneColor);

			if (itemLenght > size.x)
			{
				consolePrintStr(drawFrame, items[i]->ToString(), itemLenght - 3);
				consolePrintStr(drawFrame, (char*)"...", 3);
			}
			else {
				consolePrintStr(drawFrame, items[i]->ToString(), itemLenght);
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

	void addItem(IInterpretedToString* item)
	{
		items.add(item);
	}
	void addItem(char* item)
	{
		items.add(new CharPtr_InterpretedToString(item));
	}
	void addItem(const char* item)
	{
		items.add(new CharPtr_InterpretedToString((char*)item));
	}
	void deleteItem(IInterpretedToString* item)
	{
		items.del(item);
	}
	void deleteItem(char* item)
	{
		IInterpretedToString* deletedElementIndex = findItem(item);
		items.del(deletedElementIndex);
	}
	void deleteItem(const char* item)
	{
		IInterpretedToString* deletedElementIndex = findItem((char*)item);
		items.del(deletedElementIndex);
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
	IInterpretedToString* getItem(int index)
	{
		return items[index];
	}
	IInterpretedToString* findItem(IInterpretedToString* findedObject)
	{
		char* findedObjectString = findedObject->ToString();
		for (int i = 0; i < items.count; i++)
		{
			if(items[i] == findedObject)
				return items[i];

			char* presentItemString = items[i]->ToString();
			if (stringCompare(presentItemString, findedObjectString))
				return items[i];
		}
	}
	IInterpretedToString* findItem(char* findedString)
	{
		for (int i = 0; i < items.count; i++)
		{
			char* presentItemString = items[i]->ToString();
			if (stringCompare(presentItemString, findedString))
				return items[i];
		}
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