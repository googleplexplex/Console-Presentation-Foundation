#pragma once
#include "helpers\helpFunctions.hpp"
#include "shell\graphics.hpp"
#include "core\controlElement.hpp"

void CheckBox_onClick(void* checkBoxPtr, point clickedPos);

class CheckBox : controlElement {
	bool checked;
	symbolColor checkedColor;
	symbolColor notCheckedColor;
public:
	CheckBox(point _pos, void(*_onClick)(void*, point) = &OnClick_emptyEvent, symbolColor _checkedColor = gray, symbolColor _notCheckedColor = white, void(*_onFocus)(void*) = &onFocus_emptyEvent, void(*_onFocusLost)(void*) = &onFocusLost_emptyEvent)
	{
		pos = _pos;
		size = { 1, 1 };
		checkedColor = _checkedColor;
		notCheckedColor = _notCheckedColor;

		onClickEvent += &CheckBox_onClick; //TODO
		onFocusEvent += _onFocus;
		onFocusLostEvent += _onFocusLost;
	}

	void Draw()
	{
		consoleCursorInfo save;
		save.getAndReset();

		setTo(pos.x, pos.y);
		if(checked)
			setSymbolFullColor(checkedColor);
		else
			setSymbolFullColor(notCheckedColor);
		consolePrintCharset(filledCharacter_5_5);

		save.apply();
	}
	bool entersTheArea(int x, int y)
	{
		return (pos.x == x && pos.y == y);
	}
	bool entersTheArea(point point)
	{
		return entersTheArea(point.x, point.y);
	}

	void setPos(int x, int y)
	{
		pos.x = x;
		pos.y = y;
	}
	void setState(bool settedState)
	{
		checked = settedState;
	}
	void getCheckedColor(symbolColor settedColor)
	{
		checkedColor = settedColor;
	}
	void getNotCheckedColor(symbolColor settedColor)
	{
		notCheckedColor = settedColor;
	}

	point getPos()
	{
		return pos;
	}
	point getSize()
	{
		return size;
	}
	bool isChecked()
	{
		return checked;
	}
	symbolColor getCheckedColor()
	{
		return checkedColor;
	}
	symbolColor getNotCheckedColor()
	{
		return notCheckedColor;
	}
};

void CheckBox_onClick(void* checkBoxPtr, point clickedPos)
{
	CheckBox* checkBox = (CheckBox*)checkBoxPtr;
	checkBox->setState(!(checkBox->isChecked()));
}