# UniformGrid
###### Контейнер с фиксированным размером ячеек
##### Наследуется от containerElement
##### Определен в одноименном файле


### Члены класса
`bool **ShowGridLines**` - Флаг, отвечающий за отрисовку сетки контейнера

### Конструктор:
***UniformGrid***(unsigned int **rowsCount** = 0, unsigned int **columnsCount** = 0, bool **showGridLines** = false, symbolColor **background** = black)`

* **rowsCount** - Количество строк

* **columnsCount** - Количество колонок

* **showGridLines** - Начальное значение флага **ShowGridLines**

* **background** - Цвет фона


### Методы
(Метод **void addChild(controlElement& addedChild)** наследован от **containerElement**)

`void ***addChild***(controlElement& **addedChild**, int **row**, int **column**)` - Перегрузка **addChild**, где **row** и **column** - позиция элемента в контейнере

(Метод **void delChild(controlElement& **deletedChild**)** наследован от **containerElement**)

`void ***delChild***(point **childPos**)` - Перегрузка delChild, где **childPos** - позиция удаляемого элемента

`void ***delChild***(int **row**, int **column**)` - Перегрузка delChild, где **row** и **column** - позиция элемента в контейнере

`controlElement* ***getChild***(int **rowIndex**, int **columnIndex**)` - Возвращает элемент, который находится в контейнере по позиции **rowIndex/columnIndex**

`unsigned int ***getChildsCount***()` - Возвращает количество элементов в контейнере

--

(Метод **void Draw()** наследован от **controlElement**)

`void ***showGrid***(symbolColor **gridColor** = blue)` - Отображает сетку контейнера, где **gridColor** - её цвет

(Метод **void updatePositions()** наследован от **controlElement**)

`point ***getOnePointSize***()` - Возвращает размер одной Относительной точки (*)

`point ***calculateOneElementSize***()` - Возвращает размер одного элемента в Относительных точках (*)

---

`bool ***isIdentifyed***()` - Возвращает *false*, если таблица пустая, или *true*, если имеет строки или колонки

`void ***addRows***(int **rowsCount**)` - Добавляет в таблицу **rowsCount** строк

`void ***addRow***()` - Добавляет в таблицу одну строку

`void ***delRow***(int **rowIndex**)` - Удаляет из таблицы строку **rowIndex**

`unsigned int ***getRowsCount***()` - Возвращает количество строк в таблице

`void ***addColumns***(int **columnsCount**)` - Добавляет в таблицу **columnsCount** колонок

`void ***addColumn***()` - Добавляет в таблицу одну колоноку

`void ***delColumn***(int **columnIndex**)` - Удаляет из таблицы колоноку **columnIndex**

`unsigned int ***getColumnsCount***()` - Возвращает количество колонок в таблице

`void ***setRowsColumnsCount***(int **rowsCount**, int **columnsCount**)` - Добавляет в таблицу **rowsCount** строк и **columnsCount** колонок

`void ***setColumnsRowsCount***(int **columnsCount**, int **rowsCount**)` - Добавляет в таблицу **rowsCount** строк и **columnsCount** колонок

`unsigned int ***getRowsColumnsCount***()` - Возвращает количество ячеек в таблице

`unsigned int ***getColumnsRowsCount***()` - Возвращает количество ячеек в таблице








