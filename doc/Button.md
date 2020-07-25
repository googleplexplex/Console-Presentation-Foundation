# Button
###### Класс кнопки
##### Наследуется от [controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)
##### Определено в [одноименном файле](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/elements/Button.hpp)


### Конструктор:

*Button(char* **text** = (char*)"Button", [onClick_DelegateType](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md) **onClick** = NULL, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **textColor** = white, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **foneColor** = black)*

* **text** - Текст, отображенный в кнопке

* **onClick** - Делегат, вызываемый при нажатии на кнопку

* **textColor** - Цвет текста

* **foneColor** - Цвет фона


### Методы

(Метод **Draw()** наследованный от **[controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)**)