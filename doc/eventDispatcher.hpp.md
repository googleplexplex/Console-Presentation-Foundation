# [eventDispathcer.hpp](https://github.com/googleplexplex/Console-Presentation-Foundation/blob/master/core/eventDispatcher.hpp)
###### Файл с определением основного механизма рампределения событий фреймворка


*void ***eventDispatcherMainLoop***()* - Бесконечный цикл распрпеделения всех событий для главного контейнера

*unsigned int **eventDispatcherDelay*** - Размер интервала между итерациями цикла (В милисекундах)

*bool **needToDrawAll*** - Флаг необходимости отрисовывать все элементы заново
