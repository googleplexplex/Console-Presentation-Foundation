#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"

void CheckBox_onClick(void* checkBoxPtr, point clickedPos);

class CheckBox : controlElement {
	bool checked;
	symbolColor checkedColor;
	symbolColor notCheckedColor;
public:
	CheckBox(point _pos, onClick_DelegateType _onClick = NULL, symbolColor _checkedColor = gray, symbolColor _notCheckedColor = white, onFocus_DelegateType _onFocus = NULL, onFocusLost_DelegateType _onFocusLost = NULL)
	{
		pos = _pos;
		size = { 1, 1 };
		checkedColor = _checkedColor;
		notCheckedColor = _notCheckedColor;

		onClickSystemDelegate = &CheckBox_onClick;
		onFocusSystemDelegate = NULL;
		onFocusLostSystemDelegate = NULL;

		onClickEvent += _onClick;
		onFocusEvent += _onFocus;
		onFocusLostEvent += _onFocusLost;

		registerElement();
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
	bool entersTheArea(point point)
	{
		return (pos.x == point.x && pos.y == point.y);
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