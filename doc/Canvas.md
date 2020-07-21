# Canvas
###### Контейнер с кастомным размером и позицией ячеек
##### Наследуется от containerElement
##### Определен в одноименном файле



### Конструктор:

****Canvas***(symbolColor **background** = black)*

* **background** - Цвет фона

### Методы

(Метод **void addChild(controlElement& addedChild)** наследован от **containerElement**)

*void ***addChild***(controlElement& **addedChild**, point **childPos**)* - Перегрузка **addChild**, где **childPos** позиция элемента в контейнере

(Метод **void delChild(controlElement& deletedChild)** наследован от **containerElement**)

*void ***delChild***(point **childPos**)* - Перегрузка *delChild*, где **childPos** - позиция удаляемого элемента

*controlElement* ***getChild***(int **rowIndex**, int **columnIndex**)* - Возвращает элемент, который находится в контейнере по позиции **rowIndex/columnIndex**

*unsigned int ***getChildsCount***()* - Возвращает количество элементов в контейнере

--

(Метод **void Draw()** наследован от **controlElement**)