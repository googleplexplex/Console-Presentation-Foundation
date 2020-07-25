# ListBox
###### Класс отображения списка объектов (Только таких, которые имеют строковое представление)
##### Наследуется от [controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)
##### Определено в [одноименном файле](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/elements/ListBox.hpp)


### Конструктор:

****ListBox***(symbolColor **itemTextColor** = white, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **itemFoneColor** = black, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **selectedItemTextColor** = black, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **selectedItemFoneColor** = white, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **background** = black)*

* **itemTextColor** - Цвет текста содержимого

* **itemFoneColor** - Цвет фона содержимого

* **selectedItemTextColor** - Цвет текста выделенной строки

* **selectedItemFoneColor** - Цвет фона выделенной строки

* **background** - Цвет фона элемента


### Методы

(Метод **Draw()** наследованный от **[controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)**)


## Методы взаимодействия с содержимым

*void ***addItem***([IInterpretedToString](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/IInterpretedToString.md)* **item**)* - Добавляет в список объект, имеющий строковое представление

*void ***addItem***(char* **item**)* - Добавляет в список строку

*void ***setItem***(unsigned int **index**, [IInterpretedToString](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/IInterpretedToString.md)* **newItem**)* - Заменяет объект по индексу **index** в списке на **newItem**

*void ***setItem***(unsigned int **index**, char* **newItem**)* - Заменяет объект по индексу index в списке на **newItem**

*void ***insertItem***([IInterpretedToString](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/IInterpretedToString.md)* **item**, unsigned int **insertedIndex**)* - Добавляет в список объект **item** между объектами по индексу **insertedIndex** и **insertedIndex** + 1

*void ***insertItem***(char* **item**, unsigned int **insertedIndex**)* - Добавляет в список объект **item** между объектами по индексу **insertedIndex** и **insertedIndex** + 1

*void ***deleteItem***([IInterpretedToString](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/IInterpretedToString.md)* **item**)* - Удаляет объект **item** из списка

*void ***deleteItem***(char* **item**)* - Удаляет объект из списка, строковое представление которого **item**

*void ***deleteItem***(unsigned int **index**)* - Удаляет из списка объект по индексу **index**

*void ***popBackItem***()* - Удаляет последний объект из списка

*void ***popFrontItem***()* - Удаляет первый объект из списка

*void ***clearItems***()* - Очищает список

*unsigned int ***getItemsCount***()* - Возвращает количество объектов в списке

*[IInterpretedToString](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/IInterpretedToString.md)*& ***getItem***(unsigned int **index**)* - Возвращает указатель на объект по индексу **index**

*[IInterpretedToString](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/IInterpretedToString.md)* ***findItem***([IInterpretedToString](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/IInterpretedToString.md)* **findedObject**)* - Ищет в списке объект **findedObject**, и возвращает ссылку на него

*[IInterpretedToString](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/IInterpretedToString.md)* ***findItem***(char* **findedString**)* - Ищет в списке объект, строковое представление которого **findedString**, и возвращает ссылку на него

*[IInterpretedToString](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/IInterpretedToString.md)* ***getSelectedItem***()* - Возвращает указатель на выделенный объект

*void ***setSelectedItem***(unsigned int **newSelectedItem**)* - Выделяет объект по индексу **newSelectedItem**

*unsigned int ***getSelectedItemIndex***()* - Возвращает индекс выделенного объекта в списке

## Методы взаимодействия цветами содержимого

*void ***setItemTextColor***([symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **newItemTextColor**)* - Задает цвет текста объекта **newItemTextColor**

*void ***setItemFoneColor***([symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **newItemFoneColor**)* - Задает цвет фона текста объекта **newItemTextColor**

*void ***setSelectedItemTextColor***([symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **newSelectedItemTextColor**)* - Задает цвет текста выделенного объекта **newItemTextColor**

*void ***setSelectedItemFoneColor***([symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **newSelectedItemFoneColor**)* - Задает цвет фона текста выделенного объекта **newItemTextColor**

*[symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) ***getItemTextColor***()* - Возвращает цвет текста объекта

*[symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) ***getItemFoneColor***()* - Возвращает цвет фона текста объекта

*[symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) ***getSelectedItemTextColor***()* - Возвращает цвет текста выделенного объекта

*[symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) ***getSelectedItemFoneColor***()* - Возвращает цвет фона текста выделенного объекта
