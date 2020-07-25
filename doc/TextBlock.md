# TextBlock
###### Класс текста внутри блока
##### Наследуется от [controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)
##### Определено в [одноименном файле](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/elements/TextBlock.hpp)


### Конструктор:

****TextBlock***(char* **text** = (char*)"TextBlock", [point](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **size** = { 0, 0 }, [orientationXEnum](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **textOrientationX** = centerX, [orientationYEnum](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **textOrientationY** = centerY, symbolColor **textColor** = white, symbolColor **background** = black)*

* **text** - Текст внутри блока

* **size** - Размер блока

* **textOrientationX** - Горизонтальное выравнивание текста

* **textOrientationY** - Вертикальное выравнивание текста

* **textColor** - Цвет текста

* **background** - Цвет фона

### Методы

(Метод **Draw()** наследованный от **controlElement**)

*[orientationXEnum](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) ***setTextOrientationX***([orientationXEnum](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **newTextOrientationX**)* - Задает горизонтальное выравнивание тексту

*[orientationYEnum](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) ***setTextOrientationY***([orientationYEnum](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) **newTextOrientationY**)* - Задает вертикальное выравнивание тексту

*[orientationXEnum](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) ***getTextOrientationX***()* - Возвращает горизонтальное выравнивание текста

*[orientationYEnum](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/Types.hpp.md) ***getTextOrientationY***()* - Возвращает вертикальное выравнивание текста