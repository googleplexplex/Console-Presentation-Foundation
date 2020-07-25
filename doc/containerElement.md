# containerElement
###### Абстрактный класс контейнера
##### Наследуется от [controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)
##### Имеет наследников [Canvas](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Canvas.md), [Grid](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Grid.md), [StackPanel](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/StackPanel.md), [UniformGrid](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/UniformGrid.md)
##### Определено в [одноименном файле](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/core/containerElement.hpp)


### Методы

*void ***setAsMainContainer***()* - Устанавливает этот контейнер как первичный


### Асбстрактные Методы

*void ***addChild***([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& **addedElement**)* - Добавляет в этот контейнер элемент **addedElement**. Чаще всего контейнер имеет перегрузки этого метода для некоторых частных случаев, однако стандартный метод должен быть определен.

*void ***delChild***([controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)& **deletedChild**) - Удаляет из этого контейнера элемент **deletedChild**

*unsigned int ***getChildsCount***() - Воозвращает количество элементов в контейнере

*void ***updatePositions***() - Задает всем элементам контейнера их позицию и размер, размещая их в себе

