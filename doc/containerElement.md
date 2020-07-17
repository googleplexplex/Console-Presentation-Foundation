# containerElement
###### Абстрактный класс контейнера
##### Имеет наследников Canvas, Grid, StackPanel, UniformGrid
##### Определено в одноименном файле


###Методы

`void setAsMainContainer()` - Устанавливает этот контейнер как первичный


###Асбстрактные Методы

`void addChild(controlElement& addedElement)` - Добавляет в этот контейнер элемент addedElement. Чаще всего контейнер имеет перегрузки этого метода для некоторых частных случаев, однако стандартный метод должен быть определен.

`void delChild(controlElement& deletedChild) - Удаляет из этого контейнера элемент deletedChild

`unsigned int getChildsCount() - Воозвращает количество элементов в контейнере

`void updatePositions() - Задает всем элементам контейнера их позицию и размер, размещая их в себе

