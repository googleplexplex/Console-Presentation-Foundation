#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"

void CheckBox_onClick(void* checkBoxPtr, point clickedPos);

class CheckBox : public controlElement {
	bool Checked;
	symbolColor checkedColor;
	symbolColor notCheckedColor;
public:
	CheckBox(bool _checked = false, symbolColor _checkedColor = gray, symbolColor _notCheckedColor = white)
	{
		pos = emptyPoint;
		size = { 1, 1 };
		Checked = _checked;

		checkedColor = _checkedColor;
		notCheckedColor = _notCheckedColor;

		onClick += CheckBox_onClick;
		onFocus += Default_System_OnFocus;
	}

	//Drawing methods
	void Draw(rectangle drawFrame)
	{
		if (Checked)
			consolePrintCharset(drawFrame, pos, filledCharacter_5_5, checkedColor);
		else
			consolePrintCharset(drawFrame, pos, filledCharacter_5_5, notCheckedColor);

		needToDraw = false;
	}

	//Checkbox Setters/Getters
	void setChecked(bool newState)
	{
		Checked = newState;

		if (Checked != newState)
			needToDraw = true;
	}

	void setCheckedColor(symbolColor newCheckedColor)
	{
		checkedColor = newCheckedColor;

		if(checkedColor != newCheckedColor)
			needToDraw = true;
	}

	void setNotCheckedColor(symbolColor newNotCheckedColor)
	{
		notCheckedColor = newNotCheckedColor;

		if(notCheckedColor != newNotCheckedColor)
			needToDraw = true;
	}

	bool isChecked()
	{
		return Checked;
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

//System delegates
void CheckBox_onClick(void* checkBoxPtr, point clickedPos)
{
	CheckBox* checkBox = static_cast<CheckBox*>(checkBoxPtr);

	checkBox->setChecked(!checkBox->isChecked());
}