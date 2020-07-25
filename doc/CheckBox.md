# CheckBox
###### Класс флага
##### Наследуется от [controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)
##### Определено в [одноименном файле](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/CheckBox.md)


### Конструктор:

****CheckBox***(bool **checked** = false, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **checkedColor** = gray, [symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **notCheckedColor** = white)*

* **checked** - Начальное значение флага

* **checkedColor** - Цвет флага, когда он установлен в *true*

* **notCheckedColor** - Цвет флага, когда он установлен в *false*


### Методы

(Метод **Draw()** наследованный от **[controlElement](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/controlElement.md)**)

*void ***setChecked***(bool **newState**)* - Задает значение флага

*void ***setCheckedColor***([symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **newCheckedColor**)* - Задает цвет флага, когда он установлен в *true*

*void ***setNotCheckedColor***([symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) **newNotCheckedColor**)* - Задает цвет флага, когда он установлен в *false*

*bool ***isChecked***()* - Возвращает флаг

*[symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) ***getCheckedColor***()* - Возвращает цвет флага, когда он установлен в *true*

*[symbolColor](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/doc/graphics.hpp.md) ***getNotCheckedColor***()* - Возвращает цвет флага, когда он установлен в *false*