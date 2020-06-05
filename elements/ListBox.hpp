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

		onClickSystemDelegate = listBox_onClick;
		onFocusSystemDelegate = Default_System_OnFocus;

		registerElement();
	}

	void Draw(rectangle& drawFrame) //TODO
	{
		for (int i = 0; i < items.count || i < size.y; i++)
		{
			char* itemString = items[i]->ToString();
			consolePrintStrInLine(drawFrame, { pos.x, pos.y + i}, size.x, itemString, strlen(itemString), itemTextColor, filledCharacter_5_5, itemFoneColor);
		}

		if (size.y > items.count)
		{
			rectangle listBoxDownRect = { { pos.x, pos.y + items.count }, pos + size };
			consolePrintRect(drawFrame, listBoxDownRect, filledCharacter_5_5, background);
		}
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