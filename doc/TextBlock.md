# TextBlock
###### Класс текста внутри блока
##### Наследуется от controlElement
##### Определено в одноименном файле


###Конструктор:
`TextBlock(char* text = (char*)"TextBlock", point size = { 0, 0 }, orientationXEnum textOrientationX = centerX, orientationYEnum textOrientationY = centerY, symbolColor _textColor = white, symbolColor _background = black)`
text - Текст внутри блока
size - Размер блока
textOrientationX - Горизонтальное выравнивание текста
textOrientationY - Вертикальное выравнивание текста
textColor - Цвет текста
background - Цвет фона

###Методы
(Метод **Draw()** наследованный от **controlElement**)
`orientationXEnum setTextOrientationX(orientationXEnum newTextOrientationX)` - Задает горизонтальное выравнивание тексту
`orientationYEnum setTextOrientationY(orientationYEnum newTextOrientationY)` - Задает вертикальное выравнивание тексту
`orientationXEnum getTextOrientationX()` - Возвращает горизонтальное выравнивание текста
`orientationYEnum getTextOrientationY()` - Возвращает вертикальное выравнивание текста