#pragma once

char* stringCopy(char* string, int stringSize)
{
	char* result = new char[stringSize + 1];
	memcpy(result, string, stringSize + 1);
	return result;
}
char* stringCopy(const char* string, int stringSize)
{
	return stringCopy((char*)string, stringSize);
}
bool stringCompare(char* firstString, char* secondString)
{
	int firstStringLen = strlen(firstString);
	int secondStringLen = strlen(secondString);

	if (firstStringLen != secondStringLen)
		return false;

	for (int i = 0; i < firstStringLen; i++)
	{
		if (firstString[i] != secondString[i])
			return false;
	}

	return true;
}