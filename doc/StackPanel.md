# StackPanel
###### Контейнер с последовательным расположением элементов
##### Наследуется от containerElement
##### Определен в одноименном файле


### Типы

***stackPanelOrientationEnum*** - Перечисление выравнивания элементов

**Vertical** - Вертикальное

**Horizontal** - Горизонтальное


###Члены класса

*stackPanelOrientationEnum **stackPanelOrientation*** - Выравнивание элементов внутри контейнера

### Конструктор:
****StackPanel***(stackPanelOrientationEnum **stackPanelOrientation** = Vertical, symbolColor **background** = black)*

**stackPanelOrientation** - Начальное значение флага выравнивание элементов

**background** - Цвет фона

### Методы

(Метод **void addChild(controlElement& addedChild)** наследован от **containerElement**)

(Метод **void delChild(controlElement& deletedChild)** наследован от **containerElement**)

*void ***delChild***(unsigned int **index**)* - Перегрузка *delChild*, где **index** - индекс удаляемого элемента

*void ***delChild***(point **childPos**)* - Перегрузка *delChild*, где **childPos** - позиция удаляемого элемента

*controlElement* ***getChild***(int **index**)* - Возвращает элемент, индекс которого **index**

*unsigned int ***getChildsCount***()* - Возвращает количество элементов в контейнере

--

(Метод **void Draw()** наследован от **controlElement**)

(Метод **void updatePositions()** наследован от **controlElement**)




