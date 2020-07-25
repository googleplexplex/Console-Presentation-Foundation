# TextBox
###### Класс отображения текста
##### Наследуется от [textControlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/textControlElement.md)
##### Определено в [одноименном файле](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/elements/TextBox.hpp)


### Члены класса

*[onTextChanged_EventType]((https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/event.hpp.md)) **onTextChanged*** - Событие, вызываемое при изменении текста элемента

*unsigned int **MaxLength*** - Максимальная длинна текста

*bool **ReadOnly*** - Флаг возможности редактирования текста


### Конструктор

****TextBox***(char* **text** = (char*)"TextBox", unsigned int **maxLength** = 512, bool **readOnly** = false, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **textColor** = white, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **foneColor** = black)*

* **text** - Текст элемента

* **maxLength** - Максимальная длинна текста

* **readOnly** - Флаг возможности редактирования текста

* **textColor** - Цвет текста

* **foneColor** - Цвет фона


### Методы

(Метод **Draw()** наследованный от **[textControlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/textControlElement.md)**)
