# textControlElement
###### Элемент с методами взаимодействия с текстом внутри элемента
##### Наследуется от [controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)
##### Определен в [одноименном файле](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/modules/textControlElement.hpp)


### Методы

*void ***setText***(char* **settedText**, unsigned int **settedTextLength**)* - Задает элементу текст **settedText** (**settedTextLength** - размер массива символов)

*void ***setText***(char* **settedText**)* - Задает элементу текст **settedText** (Размер массива символов вычисляется функцией *strlen()*)

*void ***setTextColor***([symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **settedTextColor**)* - Задает тексту цвет **symbolColor**

*void ***addToText***(char **addedCharset**)* - Добавляет к тексту символ **addedCharset**

*void ***addToText***(char* **addedString**, unsigned int **addedStringLength**)* - Добавляет к тексту строку **addedString** (**addedStringLength** - размер массива символов)

*void ***popText***()* - Удаляет последний символ текста

*char* ***getText***()* - Возвращает копию текста внутри элемента

*int ***getTextLength***()* - Возвращает размер текста внутри элемента





