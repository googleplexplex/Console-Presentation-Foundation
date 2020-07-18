# Graphics.hpp
###### Файл с определением основных графических механизмов фреймворка


### Переменные

`HWND **consoleHWND**` - *HWND* окна консоли

`HANDLE **consoleHandle**` - *HANDLE* окна консоли

`HANDLE **stdHandle**` - *HANDLE* std потока

`HWND **stdHWND**` - *HWND* std потока

`symbolColor **presentTextAttribute**` - Цвет выводимого текста в консоли конкретно сейчас

`CHAR_INFO **mouseChar**` - Символ, которым отмечается мышь на экране

### Типы

`**symbolColor**` - Перечисление цветов Windows-Консоли

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

`rectangle ***getConsoleSizeRectangle***()` - Возвращает размер окна консоли в виде *rectangle* структуры

`void inline ***setTo***(short **x**, short **y**)` - Устанавливает позицию курсора в **x, y**

`void inline ***setTo***(point **point**)` - Устанавливает позицию курсора в **point**

`bool ***getTo***(rectangle **drawFrame**, unsigned int **x**, unsigned int **y**)` - Проверяет, находится ли **x, y** внутри **drawFrame**

`bool ***getTo***(rectangle **drawFrame**, point **_point**)` - Проверяет, находится ли **_point** внутри **drawFrame**

`bool ***getTo***(unsigned int **x**, unsigned int **y**)` - Проверяет, находится ли **x, y** внутри консоли

`bool ***getTo***(point **_point**)` - Проверяет, находится ли **_point** внутри консоли

`point ***getConsoleCursorPosition***()` - Возвращает позицию курсора в консоли


`void ***consolePrintCharset***(point **pos**, char **printedCharset**, symbolColor **printedCharColor** = presentTextAttribute)` - Выводит **printedCharset** цвета **printedCharColor** в позиции **pos**

`void ***consolePrintStr***(point **pos**, int **size**, char* **printedStr**, symbolColor **printedStrColor** = presentTextAttribute)` - Выводит **printedStr** (где **size** - размер **printedStr**) цвета **printedStrColor** в позиции **pos**

`void ***consolePrintRect***(rectangle& **rect**, char **lineCharset** = filledCharacter_5_5, symbolColor **lineCharsetColor** = presentTextAttribute)` - Заполняет **rect** символами **lineCharset** цвета **lineCharsetColor**

`void ***consolePrintLine***(point **pos**, int **size**, char **lineCharset** = filledCharacter_5_5, symbolColor **printedLineColor** = presentTextAttribute)` - Выводит горизонтальную линию символов **lineCharset** (где **size** - размер линии) цвета **printedStrColor** в позиции **pos**

`void ***consolePrintVerticalLine***(point **pos**, int **size**, char **lineCharset** = filledCharacter_5_5, symbolColor **printedLineColor** = presentTextAttribute)` - Выводит вертикальную линию символов **lineCharset** (где **size** - размер линии) цвета **printedStrColor** в позиции **pos**

`void ***consolePrintStrInLine***(point **pos**, int **lineSize**, char* **printedStr**, int **strSize**, symbolColor **strColor** = presentTextAttribute, char **filledChar** = emptyAsciiChar, symbolColor **filledCharColor** = presentTextAttribute)` - Выводит горизонтальную линию символов **lineCharset** (где **size** - размер линии) цвета **printedStrColor** в позиции **pos** с строкой **printedStr** цвета **strColor** внутри (где **strSize** - размер строки)

`void ***consolePrintStrInRect***(rectangle& **rect**, char* **printedStr**, int **printedStrSize**, symbolColor **printedStrColor** = presentTextAttribute, char **filledChar** = emptyAsciiChar, symbolColor **filledCharColor** = presentTextAttribute)` - Заполняет **rect** символами **filledChar** цвета **filledCharColor**, и выводит внутри **rect** строку **printedStr** цвета **printedStrColor** (где **printedStrSize** - размер строки)

`void ***consoleErase***(rectangle& **rect**)` - Заполняет **rect** пустыми символами

`void ***consoleClearAll***()` - Заполняет консоль пустыми символами


`symbolColor inline ***collectColor***(symbolColor **textColor**, symbolColor **backgroundColor**)` - Возвращает цвет, у которого цвет текста **textColor** и цвет фона **backgroundColor**

`void inline ***setSymbolFullColor***(symbolColor **color**)` - Задаёт цвет печатаемых символов **color**

`void inline ***setSymbolColor***(symbolColor **textColor**, symbolColor **backgroundColor**)`- Задаёт цвет печатаемого текста **textColor** и цвет фона **backgroundColor**

`void inline ***setStandartSymbolsColor***()` - Возвращает цвет печатаемых символов в стандартный


## Трансляторы значений

`POINT inline ***toWinPoint***(COORD **coord**)` - Транслирует из *COORD* в *POINT*

`POINT inline ***toWinPoint***(point **point**)` - Транслирует из *point* в *POINT*

`COORD inline ***toCoord***(POINT **point**)` - Транслирует из *POINT* в *COORD*

`COORD inline ***toCoord***(point **point**)` - Транслирует из *point* в *COORD*

`point inline ***toPoint***(POINT **point**)` - Транслирует из *POINT* в *point*

`point inline ***toPoint***(COORD **coord**)` - Транслирует из *COORD* в *point*

`SMALL_RECT inline ***toSmallRect***(rectangle **rect**)` - Транслирует из *rectangle* в *SMALL_RECT*







