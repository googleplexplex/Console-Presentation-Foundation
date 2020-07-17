# TextBox
###### Класс отображения текста
##### Наследуется от textControlElement 
##### Определено в одноименном файле


###Члены класса

`onTextChanged_EventType onTextChanged` - Событие, вызываемое при изменении текста элемента

`unsigned int MaxLength` - Максимальная длинна текста

`bool ReadOnly` - Флаг возможности редактирования текста


###Конструктор

`**TextBox(char* text = (char*)"TextBox", unsigned int _maxLength = 512, bool _readOnly = false, symbolColor _textColor = white, symbolColor _foneColor = black)**`

text - Текст элемента

maxLength - Максимальная длинна текста

readOnly - Флаг возможности редактирования текста

textColor - Цвет текста

foneColor - Цвет фона


###Методы

(Метод **Draw()** наследованный от **textControlElement**)
