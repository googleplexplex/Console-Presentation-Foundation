#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"

void CheckBox_onClick(void* checkBoxPtr, point clickedPos);

class CheckBox : public controlElement {
public:
	bool Checked;
	symbolColor checkedColor;
	symbolColor notCheckedColor;
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
	}

	//Check box methods
	bool isChecked()
	{
		return Checked;
	}
};

//System delegates
void CheckBox_onClick(void* checkBoxPtr, point clickedPos)
{
	CheckBox* checkBox = static_cast<CheckBox*>(checkBoxPtr);
	checkBox->Checked = !(checkBox->Checked);
}