# [Graphics.hpp](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/shell/graphics.hpp)
###### Файл с определением основных графических механизмов фреймворка


### Переменные

*HWND **consoleHWND*** - *HWND* окна консоли

*HANDLE **consoleHandle*** - *HANDLE* окна консоли

*HANDLE **stdHandle*** - *HANDLE* std потока

*HWND **stdHWND*** - *HWND* std потока

*symbolColor **presentTextAttribute*** - Цвет выводимого текста в консоли конкретно сейчас

*CHAR_INFO **mouseChar*** - Символ, которым отмечается мышь на экране

### Типы

***symbolColor*** - Перечисление цветов Windows-Консоли

null - пустой цвет

black - черный

blue - синий

green - зелёный

aqua - светло-синий

red - красный

violet - фиолетовый

yellow - жёлтый

white - белый

gray - серый

brightBlue - ярко-синий

brightGreen - ярко-зелёный

brightAqua - ярко-светло-синий (?)

brightRed - ярко-красный

brightViolet - ярко-фиолетовый

brightYellow - ярко-жёлтый

brightWhite - ярко-белый (?)


### Функции

*[rectangle](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) ***getConsoleSizeRectangle***()* - Возвращает размер окна консоли в виде *rectangle* структуры

*void inline ***setTo***(short **x**, short **y**)* - Устанавливает позицию курсора в **x, y**

*void inline ***setTo***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **point**)* - Устанавливает позицию курсора в **point**

*bool ***getTo***([rectangle](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **drawFrame**, unsigned int **x**, unsigned int **y**)* - Проверяет, находится ли **x, y** внутри **drawFrame**

*bool ***getTo***([rectangle](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **drawFrame**, [point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **_point**)* - Проверяет, находится ли **_point** внутри **drawFrame**

*bool ***getTo***(unsigned int **x**, unsigned int **y**)* - Проверяет, находится ли **x, y** внутри консоли

*bool ***getTo***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **_point**)* - Проверяет, находится ли **_point** внутри консоли

*[point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) ***getConsoleCursorPosition***()* - Возвращает позицию курсора в консоли


*void ***consolePrintCharset***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **pos**, char **printedCharset**, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **printedCharColor** = presentTextAttribute)* - Выводит **printedCharset** цвета **printedCharColor** в позиции **pos**

*void ***consolePrintStr***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **pos**, int **size**, char* **printedStr**, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **printedStrColor** = presentTextAttribute)* - Выводит **printedStr** (где **size** - размер **printedStr**) цвета **printedStrColor** в позиции **pos**

*void ***consolePrintRect***([rectangle](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md)& **rect**, char **lineCharset** = filledCharacter_5_5, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **lineCharsetColor** = presentTextAttribute)* - Заполняет **rect** символами **lineCharset** цвета **lineCharsetColor**

*void ***consolePrintLine***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **pos**, int **size**, char **lineCharset** = filledCharacter_5_5, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **printedLineColor** = presentTextAttribute)* - Выводит горизонтальную линию символов **lineCharset** (где **size** - размер линии) цвета **printedStrColor** в позиции **pos**

*void ***consolePrintVerticalLine***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **pos**, int **size**, char **lineCharset** = filledCharacter_5_5, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **printedLineColor** = presentTextAttribute)* - Выводит вертикальную линию символов **lineCharset** (где **size** - размер линии) цвета **printedStrColor** в позиции **pos**

*void ***consolePrintStrInLine***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **pos**, int **lineSize**, char* **printedStr**, int **strSize**, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **strColor** = presentTextAttribute, char **filledChar** = emptyAsciiChar, symbolColor **filledCharColor** = presentTextAttribute)* - Выводит горизонтальную линию символов **lineCharset** (где **size** - размер линии) цвета **printedStrColor** в позиции **pos** с строкой **printedStr** цвета **strColor** внутри (где **strSize** - размер строки)

*void ***consolePrintStrInRect***([rectangle](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md)& **rect**, char* **printedStr**, int **printedStrSize**, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **printedStrColor** = presentTextAttribute, char **filledChar** = emptyAsciiChar, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **filledCharColor** = presentTextAttribute)* - Заполняет **rect** символами **filledChar** цвета **filledCharColor**, и выводит внутри **rect** строку **printedStr** цвета **printedStrColor** (где **printedStrSize** - размер строки)

*void ***consoleErase***([rectangle](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md)& **rect**)* - Заполняет **rect** пустыми символами

*void ***consoleClearAll***()* - Заполняет консоль пустыми символами


*symbolColor inline ***collectColor***(symbolColor **textColor**, symbolColor **backgroundColor**)* - Возвращает цвет, у которого цвет текста **textColor** и цвет фона **backgroundColor**

*void inline ***setSymbolFullColor***(symbolColor **color**)* - Задаёт цвет печатаемых символов **color**

*void inline ***setSymbolColor***(symbolColor **textColor**, symbolColor **backgroundColor**)*- Задаёт цвет печатаемого текста **textColor** и цвет фона **backgroundColor**

*void inline ***setStandartSymbolsColor***()* - Возвращает цвет печатаемых символов в стандартный


## Трансляторы значений

*POINT inline ***toWinPoint***(COORD **coord**)* - Транслирует из *COORD* в *POINT*

*POINT inline ***toWinPoint***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **point**)* - Транслирует из *point* в *POINT*

*COORD inline ***toCoord***(POINT **point**)* - Транслирует из *POINT* в *COORD*

*COORD inline ***toCoord***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **point**)* - Транслирует из *point* в *COORD*

*[point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) inline ***toPoint***(POINT **point**)* - Транслирует из *POINT* в *[point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md)*

*[point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) inline ***toPoint***(COORD **coord**)* - Транслирует из *COORD* в *[point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md)*

*SMALL_RECT inline ***toSmallRect***([rectangle](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **rect**)* - Транслирует из *rectangle* в *SMALL_RECT*







