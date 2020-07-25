# [Types.hpp](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/modules/Types.hpp)
###### Файл с определением основных типов фреймворка


### Типы

***orientationXEnum*** - Перечисления выравниваний элемента по горизонтали

**left**

**centerX**

**right**


***orientationYEnum*** - Перечисление выравниваний элемента по вертикали

**up**

**centerY**

**down**


***point*** - тип точки, имеет x и y координаты и перегрузки операторов

*emptyPoint* - пустая точка


***rectangle*** - тип четырёхугольника, задаётся двумя **point** - верхней левой и нижней правой

*point getSize()* - возвращает размер четырёхугольника

