# Inventory Management System

Эта программа представляет собой систему управления складом, написанную на C++. Программа позволяет добавлять, удалять, заменять, искать, сортировать товары и отображать инвентарь склада. 

## Функциональность

- **Добавление товара**: Позволяет пользователю вводить информацию о новом товаре, включая название, производителя, цену, категорию, дату поступления, срок годности, OEM и комментарии.
- **Удаление товара**: Удаляет товар по его названию.
- **Замена товара**: Позволяет заменить существующий товар на новый.
- **Поиск товара**: Позволяет искать товары по названию, производителю, цене или категории.
- **Сортировка товаров**: Возможность сортировки товаров по цене или категории.
- **Отображение инвентаря**: Показывает текущий инвентарь склада.

## Структура проекта

- **main.cpp**: Основной файл программы, содержащий интерфейс командной строки.
- **Warehouse.h и Warehouse.cpp**: Классы для управления складом.
- **Product.h и Product.cpp**: Классы для представления товаров.
