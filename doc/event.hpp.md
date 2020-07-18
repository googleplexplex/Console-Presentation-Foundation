# event.hpp
###### Файл с определением типов и механизмов работы событий и делегатов фреймворка



### Методы

`template <typename **delegateArgType**>
void ***callDelegate***(void(* **delegate**)(**delegateArgType**), **delegateArgType** **delegateArg**)` - Вызов делегата **delegate** с аргументом **delegateArg** типа **delegateArgType** (Используется вместо **delegate**(), потому что проверяет **delegate** на ненулевое значение)

`template <typename **delegateFirstArgType**, typename **delegateSecondArgType**>
void callDelegate(void(* **delegate**)(**delegateFirstArgType**, **delegateSecondArgType**), **delegateFirstArgType firstDelegateArg**, **delegateSecondArgType secondDelegateArg**)` - Вызов делегата **delegate** с аргументами **firstDelegateArg** и **secondDelegateArg** типов **delegateFirstArgType** и **delegateSecondArgType** (Используется вместо **delegate**(), потому что проверяет **delegate** на ненулевое значение)



### Классы событий


`***event_oneDelegateArg***` - Шаблонный класс события с одним аргументом (**argType** - тип аргумента)

## Члены класса

`dynamicArray<void(*)(**argType**)> **delegates**` - Динамический массив вызываемых делегатов

## Методы класса

`void ***call***(**argType** **arg**)` - Вызов всех делегатов с аргументом **arg**

`void ***add***(void(* **addedDelegate**)(**argType**))` - Добавление делегата **addedDelegate** к массиву делегатов

`void ***del***(void(* **deletedDelegate**)(**argType**))` - Удаление делегата **deletedDelegate** из массива делегатов

## Операторы класса

`event_oneDelegateArg<**argType**>& ***+=***(void(* **right**)(**argType**))` - Добавление делегата к массиву делегатов

`event_oneDelegateArg<**argType**>& operator***-=***(void(* **right**)(**argType**))` - Удаление делегата из массива делегатов

`event_oneDelegateArg<**argType**>& operator***()***(**argType** **arg**)` - Вызов всех делегатов с аргументом **arg**


`***event_twoDelegateArg***` - Шаблонный класс события с двумя аргументами (**fArgType** и **sArgType** - типы аргумента)

## Члены класса

`dynamicArray<void(*)(**fArgType**, **sArgType**)> **delegates**` - Динамический массив вызываемых делегатов

## Методы класса

`void ***call***(**fArgType arg1**, **sArgType arg2**)` - Вызов всех делегатов с аргументами **arg1** и **arg2**

`void ***add***(void(*addedDelegate)(**fArgType**, **sArgType**))` - Добавление делегата **addedDelegate** к массиву делегатов

`void ***del***(void(*deletedDelegate)(**fArgType**, **sArgType**))` - Удаление делегата **deletedDelegate** из массива делегатов

## Операторы класса

`event_twoDelegateArg<**fArgType**, **sArgType**>& operator***+=***(void(* **right**)(**fArgType**, **sArgType**))` - Добавление делегата к массиву делегатов

`event_twoDelegateArg<**fArgType**, **sArgType**>& operator***-=***(void(* **right**)(**fArgType**, **sArgType**))` - Удаление делегата из массива делегатов

`event_twoDelegateArg<**fArgType**, **sArgType**>& operator***()***(**fArgType arg1**, **sArgType arg2**)` - Вызов всех делегатов с аргументами **arg1** и **arg2**



### Типы

## Делегаты

`onFocus_DelegateType` - Делегат функции фокуса

`onFocusLost_DelegateType` - Делегат функции фокуса

(Пример функции фокуса - void someFocusFunc(void* focusedElement, point mousePos))

`onClick_DelegateType` - Делегат функции нажатия

`onLeftButtonDown_DelegateType` - Делегат функции зажатия левой кнопки мыши

`onLeftButtonUp_DelegateType` - Делегат функции опускания левой кнопки мыши

`onRightButtonDown_DelegateType` - Делегат функции зажатия правой кнопки мыши

`onRightButtonUp_DelegateType` - Делегат функции опускания правой кнопки мыши

(Пример функции взаимодействия с мышью - void someMouseFunc(void* mousedElement, point clickedPoint))

`onKeyDown_DelegateType` - Делегат зажатия кнопки клавиатуры

`onKeyUp_DelegateType` - Делегат отпускания кнопки клавиатуры

(Пример функции взаимодействия с клавиатурой - void someKeyFunc(void* keyedElement, char charset))

`beforeDraw_DelegateType` - Делегат функции, вызываемой до отрисовки

`afterDraw_DelegateType` - Делегат функции, вызываемой после отрисовки

(Пример функции взаимодействия с этапами отрисовки - void someDraw(void* element))

`onResize_DelegateType` - Делегат функции, вызываемой при изменении размера элемента

`onMoved_DelegateType` - Делегат функции, вызываемой при изменении положения элемента

(Пример функции отслеживания позиции/размера элемента - void onElementFunc(void* element))

`onTextChanged_DelegateType` - Делегат функции, вызываемый при изменении текста внутри элемента

(Пример функции отслеивания изменения текста - void onTextChangedFunc(void* element))

## События

`onFocus_EventType` - Событие фокуса

`onFocusLost_EventType` - Событие потери фокуса

`onClick_EventType` - Событие нажатия

`onLeftButtonDown_EventType` - Событие зажатия левой кнопки мыши

`onLeftButtonUp_EventType` - Событие отпускания левой кнопки мыши

`onRightButtonDown_EventType` - Событие зажатия правой кнопки мыши

`onRightButtonUp_EventType` - Событие отпускания правой кнопки мыши

`onKeyDown_EventType` - Событие зажатия клавиши

`onKeyUp_EventType` - Событие отпускания клавиши

`onTextChanged_EventType` - Событие изменения текста внутри элемента

`beforeDraw_EventType` - Событие, вызываемое до отрисовки элемента

`afterDraw_EventType` - Событие, вызываемое после отрисовки элемента

`onResize_EventType` - Событие изменения размера элемента

`onMoved_EventType` - Событие изменения положения элемента

(События принимают те же аргументы и типы аргументов, что и делегаты, так как являются их списками)