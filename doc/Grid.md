# Grid
###### Контейнер-таблица с произвольным размером ячеек
##### Наследуется от [containerElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/containerElement.md)
##### Определен в [одноименном файле](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/containers/Grid.hpp)


### Члены класса

*bool **ShowGridLines*** - Флаг, отвечающий за отрисовку сетки контейнера

### Конструктор:

****Grid***(unsigned int **rowsCount** = 0, unsigned int **columnsCount** = 0, bool **showGridLines** = false, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **background** = black)*

* **rowsCount** - Количество строк

* **columnsCount** - Количество колонок

* **showGridLines** - Начальное значение флага *ShowGridLines*

* **background** - Цвет фона

### Методы

*void ***addChild***([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& **element**, unsigned int **row**, unsigned int **column**, unsigned int **RowSpan**, unsigned int **ColumnSpan**)* - Добавляет в ячейку **row**/**column** таблицы элемент **element** размером **RowSpan**/**ColumnSpan**

*void ***addChild***([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& **element**, unsigned int **row**, unsigned int **column**)* - Добавляет в ячейку **row**/**column** таблицы элемент **element**

(Метод **void addChild([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& addedChild)** наследован от **[containerElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/containerElement.md)**)

(Метод **void delChild([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& deletedChild)** наследован от **[containerElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/containerElement.md)**)

*void ***delChild***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **childPos**)* - Перегрузка delChild, где **childPos** - позиция удаляемого элемента

*void ***delChild***(int **row**, int **column**)* - Перегрузка *delChild*, где **row** и **column** - позиция элемента в контейнере

*[controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)* ***getChild***(int **rowIndex**, int **columnIndex**)* - Возвращает элемент, который находится в контейнере по позиции **rowIndex**/**columnIndex**

*unsigned int ***getChildRowSpan***(int **row**, int **column**)* - Возвращает количество занимаемых строк элементом в ячейке **row**/**column**

*unsigned int ***getChildColumnSpan***(int **row**, int **column**)* - Возвращает количество занимаемых столбцов элементом в ячейке **row**/**column**

*unsigned int ***getChildsCount***()* - Возвращает количество элементов в контейнере

--

(Метод **void Draw()** наследован от **[controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)**)

*void ***showGrid***([symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **gridColor** = blue)* - Отображает сетку контейнера, где **gridColor** - её цвет

(Метод **void updatePositions()** наследован от **[controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)**)

*void ***setHeight***(unsigned int **elementIndex**, unsigned int **newHeight**)* - Устанавливает высоту **newHeight** строке с индексом **elementIndex** 

*unsigned int ***getHeight***(unsigned int **elementIndex**)* - Возвращает высоту строки с индексом **elementIndex** 

*unsigned int ***getHeightsSum***()* - Возвращает сумму высот всех строк

*void ***setWidth***(unsigned int **elementIndex**, unsigned int **newWidth**)* - Устанавливает ширину **newWidth** столбцу с индексом **elementIndex** 

*unsigned int ***getWidth***(unsigned int **elementIndex**)* - Возвращает ширину столбца с индексом **elementIndex**

*unsigned int ***getWidthsSum***()* - Возвращает сумму высот всех столбцов

*point ***getOnePointSize***()* - Возвращает размер одной Относительной точки (*)

*point ***calculateOneElementSize***()* - Возвращает размер одного элемента в Относительных точках (*)

---

*bool ***isIdentifyed***()* - Возвращает false, если таблица пустая, или true, если имеет строки или колонки

*void ***addRow***(unsigned int **size**)* - Добавляет в таблицу одну строку размера **size**

*void ***addRow***()* - Добавляет в таблицу одну строку

*void ***addRows***(unsigned int **rowsCount**, unsigned int rowsSize)* - Добавляет в таблицу **rowsCount** строк размера rowsSize

*void ***addRows***(unsigned int **rowsCount**)* - Добавляет в таблицу **rowsCount** строк

*void ***delRow***(int **rowIndex**)* - Удаляет из таблицы строку **rowIndex**

*unsigned int ***getRowsCount***()* - Возвращает количество строк в таблице

*void ***addColumn***()* - Добавляет в таблицу одну колоноку

*void ***addColumn***(unsigned int **size**)* - Добавляет в таблицу одну колоноку размера **size**

*void ***addColumns***(unsigned int **columnsCount**, unsigned int columnsSize)* - Добавляет в таблицу **columnsCount** колонок размера columnsSize

*void ***addColumns***(int **columnsCount**)* - Добавляет в таблицу **columnsCount** колонок

*void ***delColumn***(int **columnIndex**)* - Удаляет из таблицы колоноку **columnIndex**

*unsigned int ***getColumnsCount***()* - Возвращает количество колонок в таблице

*void ***setRowsColumnsCount***(unsigned int **rowsCount**, unsigned int **columnsCount**, unsigned int **size**)* - Добавляет в таблицу **rowsCount** строк и **columnsCount** колонок размера **size**

*void ***setRowsColumnsCount***(int **rowsCount**, int **columnsCount**)* - Добавляет в таблицу **rowsCount** строк и **columnsCount** колонок


*void ***setColumnsRowsCount***(int **columnsCount**, int **rowsCount**)* - Добавляет в таблицу **rowsCount** строк и **columnsCount** колонок

*void ***setColumnsRowsCount***(unsigned int **columnsCount**, unsigned int **rowsCount**, unsigned int **size**)* - Добавляет в таблицу **rowsCount** строк и **columnsCount** колонок размера **size**

*unsigned int ***getRowsColumnsCount***()* - Возвращает количество ячеек в таблице

*unsigned int ***getColumnsRowsCount***()* - Возвращает количество ячеек в таблице








