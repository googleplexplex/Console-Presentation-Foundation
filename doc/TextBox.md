# TextBox
###### Класс отображения текста
##### Наследуется от textControlElement 
##### Определено в одноименном файле


### Члены класса

`onTextChanged_EventType **onTextChanged**` - Событие, вызываемое при изменении текста элемента

`unsigned int **MaxLength**` - Максимальная длинна текста

`bool **ReadOnly**` - Флаг возможности редактирования текста


### Конструктор

`***TextBox***(char* **text** = (char*)"TextBox", unsigned int **maxLength** = 512, bool **readOnly** = false, symbolColor **textColor** = white, symbolColor **foneColor** = black)`

* **text** - Текст элемента

* **maxLength** - Максимальная длинна текста

* **readOnly** - Флаг возможности редактирования текста

* **textColor** - Цвет текста

* **foneColor** - Цвет фона


### Методы

(Метод **Draw()** наследованный от **textControlElement**)
