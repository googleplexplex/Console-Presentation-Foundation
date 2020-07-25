# StackPanel
###### Контейнер с последовательным расположением элементов
##### Наследуется от [containerElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/containerElement.md)
##### Определен в [одноименном файле](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/containers/StackPanel.hpp)


### Типы

***stackPanelOrientationEnum*** - Перечисление выравнивания элементов

**Vertical** - Вертикальное

**Horizontal** - Горизонтальное


###Члены класса

*stackPanelOrientationEnum **stackPanelOrientation*** - Выравнивание элементов внутри контейнера

### Конструктор:
****StackPanel***(stackPanelOrientationEnum **stackPanelOrientation** = Vertical, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **background** = black)*

**stackPanelOrientation** - Начальное значение флага выравнивание элементов

**background** - Цвет фона

### Методы

(Метод **void addChild([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& addedChild)** наследован от **containerElement**)

(Метод **void delChild([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& deletedChild)** наследован от **containerElement**)

*void ***delChild***(unsigned int **index**)* - Перегрузка *delChild*, где **index** - индекс удаляемого элемента

*void ***delChild***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **childPos**)* - Перегрузка *delChild*, где **childPos** - позиция удаляемого элемента

*[controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)* ***getChild***(int **index**)* - Возвращает элемент, индекс которого **index**

*unsigned int ***getChildsCount***()* - Возвращает количество элементов в контейнере

--

(Метод **void Draw()** наследован от **[controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)**)

(Метод **void updatePositions()** наследован от **[controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)**)




