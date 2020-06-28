#pragma once
#include "core\controlElement.hpp"
#include "modules\IInterpretedToString.hpp"
#include "shell\graphics.hpp"
#include "modules\types.hpp"
#include "modules\dynamicArray.hpp"
#include "core\event.hpp"


class CharPtr_InterpretedToString : public IInterpretedToString
{
public:
	char* string;

	CharPtr_InterpretedToString()
	{
		string = NULL;
	}
	CharPtr_InterpretedToString(char* _string)
	{
		string = stringCopy(_string, strlen(_string));
	}
	CharPtr_InterpretedToString(char* _string, int stringSize)
	{
		string = stringCopy(_string, stringSize);
	}
	~CharPtr_InterpretedToString()
	{
		delete string;
	}

	char* ToString()
	{
		return string;
	}
};


void listBox_onClick(void* listBoxPtr, point clickedPos);

class ListBox : public controlElement {
	dynamicArray<IInterpretedToString*> items;
	unsigned int selectedItem;
	symbolColor itemTextColor;
	symbolColor itemFoneColor;
	symbolColor selectedItemTextColor;
	symbolColor selectedItemFoneColor;
public:
	ListBox(symbolColor _itemTextColor = white, symbolColor _itemFoneColor = black, symbolColor _selectedItemTextColor = black, symbolColor _selectedItemFoneColor = white, symbolColor _background = black)
	{
		pos = emptyPoint;
		size = emptyPoint;
		selectedItem = -1;
		itemTextColor = _itemTextColor;
		itemFoneColor = _itemFoneColor;
		selectedItemTextColor = _selectedItemTextColor;
		selectedItemFoneColor = _selectedItemFoneColor;
		background = _background;

		onClick.add(listBox_onClick);
		onFocus.add(Default_System_OnFocus);
	}


	//Drawing methods
	void Draw(rectangle& drawFrame)
	{
		for (int i = 0; i < items.count && i < size.y; i++)
		{
			char* itemString = items[i]->ToString();
			consolePrintStrInLine(drawFrame, { pos.x, pos.y + i}, size.x, itemString, strlen(itemString), itemTextColor, filledCharacter_5_5, itemFoneColor);
		}

		if (size.y > items.count)
		{
			rectangle listBoxDownRect = { { pos.x, pos.y + items.count }, pos + size };
			consolePrintRect(drawFrame, listBoxDownRect, filledCharacter_5_5, background);
		}

		needToDraw = false;
	}


	//List box methods
	void addItem(IInterpretedToString* item)
	{
		items.add(item);
	}
	void addItem(char* item)
	{
		addItem(new CharPtr_InterpretedToString(item));
	}
	void addItem(const char* item)
	{
		addItem(new CharPtr_InterpretedToString((char*)item));
	}
	void insertItem(IInterpretedToString* item, unsigned int insertedIndex)
	{
		items.insert(item, insertedIndex);
	}
	void insertItem(char* item, unsigned int insertedIndex)
	{
		insertItem(new CharPtr_InterpretedToString(item), insertedIndex);
	}
	void insertItem(const char* item, unsigned int insertedIndex)
	{
		insertItem(new CharPtr_InterpretedToString((char*)item), insertedIndex);
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
	void deleteItem(unsigned int index)
	{
		items.delElementIn(index);
	}

	void popBackItem()
	{
		items.delLast();
	}
	void popFrontItem()
	{
		items.delFirst();
	}
	void clearItems()
	{
		items.clean();
	}
	
	unsigned int getItemsCount()
	{
		return items.count;
	}
	IInterpretedToString* getItem(unsigned int index)
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

	IInterpretedToString* getSelectedItem()
	{
		return items[selectedItem];
	}


	//Listbox Setters/Getters
	void setSelectedItem(unsigned int newSelectedItem)
	{
		selectedItem = newSelectedItem;

		if (selectedItem != newSelectedItem)
			setAllTreeInDrawQueue();
	}

	void setItemTextColor(symbolColor newItemTextColor)
	{
		itemTextColor = newItemTextColor;

		if(itemTextColor != newItemTextColor)
			setAllTreeInDrawQueue();
	}

	void setItemFoneColor(symbolColor newItemFoneColor)
	{
		itemFoneColor = newItemFoneColor;

		if(itemFoneColor != newItemFoneColor)
			setAllTreeInDrawQueue();
	}

	void setSelectedItemTextColor(symbolColor newSelectedItemTextColor)
	{
		selectedItemTextColor = newSelectedItemTextColor;

		if(selectedItemTextColor != newSelectedItemTextColor)
			setAllTreeInDrawQueue();
	}

	void setSelectedItemFoneColor(symbolColor newSelectedItemFoneColor)
	{
		selectedItemFoneColor = newSelectedItemFoneColor;

		if(selectedItemFoneColor != newSelectedItemFoneColor)
			setAllTreeInDrawQueue();
	}

	unsigned int getSelectedItemIndex()
	{
		return selectedItem;
	}

	symbolColor getItemTextColor()
	{
		return itemTextColor;
	}

	symbolColor getItemFoneColor()
	{
		return itemFoneColor;
	}

	symbolColor getSelectedItemTextColor()
	{
		return selectedItemTextColor;
	}

	symbolColor getSelectedItemFoneColor()
	{
		return selectedItemFoneColor;
	}
};


//System delegates
void listBox_onClick(void* listBoxPtr, point clickedPos)
{
	ListBox* listBox = static_cast<ListBox*>(listBoxPtr);

	if (clickedPos.y < listBox->getItemsCount())
		listBox->setSelectedItem(clickedPos.y);
}