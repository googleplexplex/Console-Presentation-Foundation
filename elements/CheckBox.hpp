#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"

void CheckBox_onClick(void* checkBoxPtr, point clickedPos);

class CheckBox : public controlElement {
	bool checked;
	symbolColor checkedColor;
	symbolColor notCheckedColor;
public:
	CheckBox(point _pos, symbolColor _checkedColor = gray, symbolColor _notCheckedColor = white)
	{
		pos = _pos;
		size = { 1, 1 };
		checkedColor = _checkedColor;
		notCheckedColor = _notCheckedColor;

		onClickSystemDelegate = CheckBox_onClick;
		onFocusSystemDelegate = Default_System_OnFocus;

		registerElement();
	}

	void Draw(rectangle drawFrame)
	{
		consoleCursorInfo save;
		save.getAndReset();

		setTo(pos.x, pos.y);
		if(checked)
			setSymbolFullColor(checkedColor);
		else
			setSymbolFullColor(notCheckedColor);
		consolePrintCharset(drawFrame, filledCharacter_5_5);

		save.apply();
	}

	void setState(bool settedState)
	{
		checked = settedState;
	}
	void setCheckedColor(symbolColor settedColor)
	{
		checkedColor = settedColor;
	}
	void setNotCheckedColor(symbolColor settedColor)
	{
		notCheckedColor = settedColor;
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