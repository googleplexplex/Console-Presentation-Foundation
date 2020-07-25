# Canvas
###### Контейнер с кастомным размером и позицией ячеек
##### Наследуется от [containerElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/containerElement.md)
##### Определен в [одноименном файле](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/containers/Canvas.hpp)



### Конструктор:

****Canvas***([symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **background** = black)*

* **background** - Цвет фона

### Методы

(Метод **void addChild([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& addedChild)** наследован от **[containerElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/containerElement.md)**)

*void ***addChild***([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& **addedChild**, [point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **childPos**)* - Перегрузка **addChild**, где **childPos** позиция элемента в контейнере

(Метод **void delChild(controlElement& deletedChild)** наследован от **[containerElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/containerElement.md)**)

*void ***delChild***([point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **childPos**)* - Перегрузка *delChild*, где **childPos** - позиция удаляемого элемента

*[controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)* ***getChild***(int **rowIndex**, int **columnIndex**)* - Возвращает элемент, который находится в контейнере по позиции **rowIndex/columnIndex**

*unsigned int ***getChildsCount***()* - Возвращает количество элементов в контейнере

--

(Метод **void Draw()** наследован от **[controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)**)