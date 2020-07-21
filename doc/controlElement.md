# controlElement
###### Абстрактный класс элемента управления
##### Имеет наследников containerElement, CheckBox, ListBox, textControlElement
##### Определено в одноименном файле


### Члены класса

*point **pos*** - Явная позиция элемента в консоли (В символах)

*point **size*** - Явный размер элемента (В символах)

*symbolColor **background*** - Цвет фона

*bool **Visible*** - Видимость элемента

*bool **Handled*** - Обрабатываемость элемента контейнером

*void* **parent*** - Указатель на контейнер

*onFocus_EventType **onFocus*** - Событие фокуса

*onFocusLost_EventType **onFocusLost*** - Событие потери фокуса

*onClick_EventType **onClick*** - Событие нажатия

*onLeftButtonDown_EventType **onLeftButtonDown*** - Событие зажатия левой кнопки мыши

*onLeftButtonUp_EventType **onLeftButtonUp*** - Событие отпускания левой кнопки мыши

*onRightButtonDown_EventType **onRightButtonDown*** - Событие зажатия правой кнопки мыши

*onRightButtonUp_EventType **onRightButtonUp*** - Событие отпускания правой кнопки мыши

*onKeyDown_EventType **onKeyDown*** - Событие зажатия клавишы

*onKeyUp_EventType **onKeyUp*** - Событие отпускания клавишы

*beforeDraw_EventType **beforeDraw*** - Событие, вызываемое до отрисовки элемента

*afterDraw_EventType **afterDraw*** - Событие, вызываемое после отрисовки элемента

*onResize_EventType **onResize*** - Событие, вызываемое при изменении размера элемента

*onMoved_EventType **onMoved*** - Событие, вызываемое при перемещении элемента


### Конструктор:

****Grid***(unsigned int **rowsCount** = 0, unsigned int **columnsCount** = 0, bool **showGridLines** = false, symbolColor **background** = black)***

* **rowsCount** - Количество строк

* **columnsCount** - Количество колонок

* **showGridLines** - Начальное значение флага **ShowGridLines**

* **background** - Цвет фона


### Методы

*bool ***entersTheArea***(point **point**)* - Находится ли точка **point** внутри элемента

*void ***Erase***()* - Закрашивает элемент

*void ***setParent***(controlElement& **parent**)* - Устанавливает элементу контейнер **parent**

*void ***setPos***(point **newPos**)* - Устанавливет явную позицию элемента

*void ***setSize***(point **newSize**)* - Устанавливает явный размер элемента

*void ***setBackground***(symbolColor **newBackground**)* - Устанавливает цвет фона

*void ***addInRedrawQueue***()* - Добавляет элемент в очередь перерисовки основного цикла событий

*point ***getPos***()* - Возвращает явную позицию элемента

*point ***getSize***()* - Возвращает явный размер элемента

*rectangle ***getRect***()* - Возвращает явную позицию и размер в виде структуры *rectangle*

*void* ***getParent***()* - Возвращает указатель на контейнер

*symbolColor ***getBackground***()* - Возвращает цвет фона


### Асбстрактные Методы

****Draw***()* - Отрисовывает элемент, исходя из его явной позиции и размера
