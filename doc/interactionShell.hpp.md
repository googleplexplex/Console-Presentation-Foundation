# InteractionShell.hpp
###### Файл с определением основных механизмов считывания активности фреймворка



### Функции

`bool ***getMouseLeftButtonState***()` - Возвращает *true*, если левая кнопка мыши зажата, в ином случае - *false*

`bool ***getMouseRightButtonState***()` - Возвращает *true*, если правая кнопка мыши зажата, в ином случае - *false*

`POINT ***getMouseGlobalPos***()` - Возвращает абсолютную позицию мыши

`POINT ***getWindowGlobalPos***()` - Возвращает абсолютную позицию окна консоли

`POINT ***getConsoleFontSize***()` - Возвращает размер шрифта консоли

`point ***getPresentConsoleSize***()` - Возвращает размер окна консоли

`rectangle ***consoleSizeRectangle***()` - Возвращает размер консоли в виде структуры *rectangle*

`POINT ***getMouseConsolePos***()` - Возвращает позицию мыши относительно консоли в символах

`void ***setConsoleSize***(int **x**, int **y**)` - Задает консоли размер **x, y** в символах

`void ***setTittle***(char* **newTittle**)` - Задает консоли титул **newTittle**

`void ***setWinTo***(short **x**, short  **y**)` - Задает консоли положение

`bool ***keyboardHit***()` - Возвращает *true*, если любая клавиша зажата, в ином случае - *false*

`char ***getInputedChar***()` - Возвращает зажатую клавишу

`UserInputStruct ***getInput***()` - Возвращает структуру *UserInputStruct*, полностью заполненную вводом пользователя

`UserActivityStruct ***getUserActivity***(UserInputStruct& **prevUserIOActions**, UserInputStruct& **presentUserIOActions**, point& **prevConsoleSize**, point& **presentConsoleSize**)` - Возвращает структуру *UserActivityStruct*, заполненную активностью пользователя, исходя из пользовательского ввода на нынешней и прошлой итерации



### Структуры


`***UserActivityStruct***` - Структура активности пользователя

## Члены класса

`bool **mouseLeftButtonStateChanged**` - Флаг изменения состояния левой кнопки мыши

`bool **mouseRightButtonStateChanged**` - Флаг изменения состояния правой кнопки мыши

`bool **mousePosChanged**` - Флаг изменения позиции мыши

`bool **keyboardStateChanged**` - Флаг изменения состояния любой клавишы клавиатуры

`bool **consoleWindowResized**` - Флаг изменения размера окна консоли

---

`**UserInputStruct**` - Структура ввода пользователя

## Члены класса

`point **mouseConsolePos**` - Позиция мыши

`bool **mouseLeftPressed**` - Состояние левой кнопки мыши

`bool **mouseRightPressed**` - Состояние правой кнопки мыши

`bool **keyboardPress**` - Флаг зажатия хоть одной клавиши

`char **keyboardPressedKey**` - Если клавиша зажата, то это поле хранит его символ

## Методы класса

`***setNull***()` - Обнуляет все флаги и поля
