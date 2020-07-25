# UniformGrid
###### Контейнер с фиксированным размером ячеек
##### Наследуется от [containerElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/containerElement.md)
##### Определен в [одноименном файле](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/containers/UniformGrid.hpp)


### Члены класса
*bool **ShowGridLines*** - Флаг, отвечающий за отрисовку сетки контейнера

### Конструктор:
***UniformGrid***(unsigned int **rowsCount** = 0, unsigned int **columnsCount** = 0, bool **showGridLines** = false, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **background** = black)*

* **rowsCount** - Количество строк

* **columnsCount** - Количество колонок

* **showGridLines** - Начальное значение флага **ShowGridLines**

* **background** - Цвет фона


### Методы
(Метод **void addChild([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& addedChild)** наследован от **containerElement**)

*void ***addChild***([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& **addedChild**, int **row**, int **column**)* - Перегрузка **addChild**, где **row** и **column** - позиция элемента в контейнере

(Метод **void delChild([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& **deletedChild**)** наследован от **containerElement**)

*void ***delChild***(point **childPos**)* - Перегрузка delChild, где **childPos** - позиция удаляемого элемента

*void ***delChild***(int **row**, int **column**)* - Перегрузка delChild, где **row** и **column** - позиция элемента в контейнере

*controlElement* ***getChild***(int **rowIndex**, int **columnIndex**)* - Возвращает элемент, который находится в контейнере по позиции **rowIndex/columnIndex**

*unsigned int ***getChildsCount***()* - Возвращает количество элементов в контейнере

--

(Метод **void Draw()** наследован от **controlElement**)

*void ***showGrid***([symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **gridColor** = blue)* - Отображает сетку контейнера, где **gridColor** - её цвет

(Метод **void updatePositions()** наследован от **[controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)**)

*point ***getOnePointSize***()* - Возвращает размер одной Относительной точки (*)

*point ***calculateOneElementSize***()* - Возвращает размер одного элемента в Относительных точках (*)

---

*bool ***isIdentifyed***()* - Возвращает *false*, если таблица пустая, или *true*, если имеет строки или колонки

*void ***addRows***(int **rowsCount**)* - Добавляет в таблицу **rowsCount** строк

*void ***addRow***()* - Добавляет в таблицу одну строку

*void ***delRow***(int **rowIndex**)* - Удаляет из таблицы строку **rowIndex**

*unsigned int ***getRowsCount***()* - Возвращает количество строк в таблице

*void ***addColumns***(int **columnsCount**)* - Добавляет в таблицу **columnsCount** колонок

*void ***addColumn***()* - Добавляет в таблицу одну колоноку

*void ***delColumn***(int **columnIndex**)* - Удаляет из таблицы колоноку **columnIndex**

*unsigned int ***getColumnsCount***()* - Возвращает количество колонок в таблице

*void ***setRowsColumnsCount***(int **rowsCount**, int **columnsCount**)* - Добавляет в таблицу **rowsCount** строк и **columnsCount** колонок

*void ***setColumnsRowsCount***(int **columnsCount**, int **rowsCount**)* - Добавляет в таблицу **rowsCount** строк и **columnsCount** колонок

*unsigned int ***getRowsColumnsCount***()* - Возвращает количество ячеек в таблице

*unsigned int ***getColumnsRowsCount***()* - Возвращает количество ячеек в таблице








