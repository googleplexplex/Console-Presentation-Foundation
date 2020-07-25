# controlElement
###### Абстрактный класс элемента управления
##### Имеет наследников [containerElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/containerElement.md), [CheckBox](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/elements/CheckBox.hpp), [ListBox](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/elements/ListBox.hpp), [textControlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/textControlElement.md)
##### Определено в [одноименном файле]([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md))


### Члены класса

*[point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **pos*** - Явная позиция элемента в консоли (В символах)

*[point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **size*** - Явный размер элемента (В символах)

*[symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **background*** - Цвет фона

*bool **Visible*** - Видимость элемента

*bool **Handled*** - Обрабатываемость элемента контейнером

*void* **parent*** - Указатель на контейнер

*[onFocus_EventType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **onFocus*** - Событие фокуса

*[onFocusLost_EventType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **onFocusLost*** - Событие потери фокуса

*[onClick_EventType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **onClick*** - Событие нажатия

*[onLeftButtonDown_EventType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **onLeftButtonDown*** - Событие зажатия левой кнопки мыши

*[onLeftButtonUp_EventType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **onLeftButtonUp*** - Событие отпускания левой кнопки мыши

*[onRightButtonDown_EventType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **onRightButtonDown*** - Событие зажатия правой кнопки мыши

*[onRightButtonUp_EventType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **onRightButtonUp*** - Событие отпускания правой кнопки мыши

*[onKeyDown_EventType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **onKeyDown*** - Событие зажатия клавишы

*[onKeyUp_EventType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **onKeyUp*** - Событие отпускания клавишы

*[beforeDraw_EventType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **beforeDraw*** - Событие, вызываемое до отрисовки элемента

*[afterDraw_EventType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **afterDraw*** - Событие, вызываемое после отрисовки элемента

*[onResize_EventType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **onResize*** - Событие, вызываемое при изменении размера элемента

*[onMoved_EventType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **onMoved*** - Событие, вызываемое при перемещении элемента


### Конструктор:

****Grid***(unsigned int **rowsCount** = 0, unsigned int **columnsCount** = 0, bool **showGridLines** = false, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **background** = black)***

* **rowsCount** - Количество строк

* **columnsCount** - Количество колонок

* **showGridLines** - Начальное значение флага **ShowGridLines**

* **background** - Цвет фона


### Методы

*bool ***entersTheArea***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **point**)* - Находится ли точка **point** внутри элемента

*void ***Erase***()* - Закрашивает элемент

*void ***setParent***([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& **parent**)* - Устанавливает элементу контейнер **parent**

*void ***setPos***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **newPos**)* - Устанавливет явную позицию элемента

*void ***setSize***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **newSize**)* - Устанавливает явный размер элемента

*void ***setBackground***([symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **newBackground**)* - Устанавливает цвет фона

*void ***addInRedrawQueue***()* - Добавляет элемент в очередь перерисовки основного цикла событий

*[point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) ***getPos***()* - Возвращает явную позицию элемента

*[point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) ***getSize***()* - Возвращает явный размер элемента

*[rectangle](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) ***getRect***()* - Возвращает явную позицию и размер в виде структуры *rectangle*

*void* ***getParent***()* - Возвращает указатель на контейнер

*[symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) ***getBackground***()* - Возвращает цвет фона


### Асбстрактные Методы

****Draw***()* - Отрисовывает элемент, исходя из его явной позиции и размера
