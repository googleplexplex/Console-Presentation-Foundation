# ListBox
###### Класс отображения списка объектов (Только таких, которые имеют строковое представление)
##### Наследуется от controlElement
##### Определено в одноименном файле


###Конструктор:

`**ListBox(symbolColor itemTextColor = white, symbolColor itemFoneColor = black, symbolColor selectedItemTextColor = black, symbolColor selectedItemFoneColor = white, symbolColor background = black)**`

itemTextColor - Цвет текста содержимого

itemFoneColor - Цвет фона содержимого

selectedItemTextColor - Цвет текста выделенной строки

selectedItemFoneColor - Цвет фона выделенной строки

background - Цвет фона элемента

###Методы

(Метод **Draw()** наследованный от **controlElement**)

##Методы взаимодействия с содержимым

`void addItem(IInterpretedToString* item)` - Добавляет в список объект, имеющий строковое представление

`void addItem(char* item)` - Добавляет в список строку

`void setItem(unsigned int index, IInterpretedToString* newItem)` - Заменяет объект по индексу index в списке на newItem

`void setItem(unsigned int index, char* newItem)` - Заменяет объект по индексу index в списке на newItem

`void insertItem(IInterpretedToString* item, unsigned int insertedIndex)` - Добавляет в список объект item между объектами по индексу insertedIndex и insertedIndex + 1

`void insertItem(char* item, unsigned int insertedIndex)` - Добавляет в список объект item между объектами по индексу insertedIndex и insertedIndex + 1

`void deleteItem(IInterpretedToString* item)` - Удаляет объект item из списка

`void deleteItem(char* item)` - Удаляет объект из списка, строковое представление которого item

`void deleteItem(unsigned int index)` - Удаляет из списка объект по индексу index

`void popBackItem()` - Удаляет последний объект из списка

`void popFrontItem()` - Удаляет первый объект из списка

`void clearItems()` - Очищает список

`unsigned int getItemsCount()` - Возвращает количество объектов в списке

`IInterpretedToString*& getItem(unsigned int index)` - Возвращает указатель на объект по индексу index

`IInterpretedToString* findItem(IInterpretedToString* findedObject)` - Ищет в списке объект findedObject, и возвращает ссылку на него

`IInterpretedToString* findItem(char* findedString)` - Ищет в списке объект, строковое представление которого findedString, и возвращает ссылку на него

`IInterpretedToString* getSelectedItem()` - Возвращает указатель на выделенный объект

`void setSelectedItem(unsigned int newSelectedItem)` - Выделяет объект по индексу newSelectedItem

`unsigned int getSelectedItemIndex()` - Возвращает индекс выделенного объекта в списке

##Методы взаимодействия цветами содержимого

`void setItemTextColor(symbolColor newItemTextColor)` - Задает цвет текста объекта newItemTextColor

`void setItemFoneColor(symbolColor newItemFoneColor)` - Задает цвет фона текста объекта newItemTextColor

`void setSelectedItemTextColor(symbolColor newSelectedItemTextColor)` - Задает цвет текста выделенного объекта newItemTextColor

`void setSelectedItemFoneColor(symbolColor newSelectedItemFoneColor)` - Задает цвет фона текста выделенного объекта newItemTextColor

`symbolColor getItemTextColor()` - Возвращает цвет текста объекта

`symbolColor getItemFoneColor()` - Возвращает цвет фона текста объекта

`symbolColor getSelectedItemTextColor()` - Возвращает цвет текста выделенного объекта

`symbolColor getSelectedItemFoneColor()` - Возвращает цвет фона текста выделенного объекта
