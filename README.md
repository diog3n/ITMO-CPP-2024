# ITMO-CPP-2024-LAB1
Задание на лабораторную работу №1 по курсe "Программирование на С++".

## Рассматриваемые темы
Ввод/вывод, файловый ввод вывод. Основные типы данных и выражения. Понятие функции. Основы компиляции.
С основными типа данных можно ознакомиться, например, здесь:
https://cplusplus.com/doc/tutorial/variables/

Разработать программу, которая вводит с клавиатуры два или три типа данных, и в качестве результата выводит в файл функцию, в которой будут созданы и проинициализированы переменные указанных типов, а также осуществлены арифметические операции над этими переменными с последующим выводом результата.

## Улучшение программы
*Предложите способ, позволяющий легко модифицировать программу генератор, чтобы она могла синтезировать более сложные выражения, используя, например, файл в котором каждая  содержит символы операций. Приветствуются любые решения.*
Для улучшения программы можно использовать специальный файл, в котором описаны проверяемые операции. У такого файла может быть специальный синтаксис, что возможности генерации чуть более гибкими.

## Решение
Решение представленно в данном репозитории. Для его сборки нужно просто запустить make:

```bash
make
```

После чего будет получен файл funcgen. Примеры использования:

```bash
./funcgen test/out.cpp
```
или
```bash
./funcgen test/out.cpp file.op
```
В первом случае будет сгенерирована простая функция, проверяющая обычные арифметические операции. Для генерации используются данные, поступающие от пользователя на вход в интерактивном режиме. Во втором случае будет сгенерирована более сложная функция. Для генерации используется файл с (опциональным) расширением .op. Пример файла

```
var var1
var var2
var var3
var var4

type float = 0.1 0.2 0.3 0.4
type unsigned int = 1 2 3 4
type char = 'a' 'b' 'c' 'd'

expr (var1 + var2) / var3
expr (var2 + var3) * var4
expr var2 + var4
expr var1 - var3
```

Где ключевым словом **var** помечено определение имен переменных, ключевым словом **type** помечено определение типа переменной и через знак "=" через пробел записаны начальные значения, которые буду даны этим переменным.
Ключевым словом **expr** помечаются выражения, которые будут использованы для проверки типов.

## Пример вывода
При генерации простой фукнции:
```cpp
#include <iostream>

void TestFunction() {
	{
		int var1 = 1;
		int var2 = 2;
		std::cout << var1 + var2 << std::endl;
		std::cout << var1 - var2 << std::endl;
		std::cout << var1 / var2 << std::endl;
		std::cout << var1 * var2 << std::endl;
	}
	{
		double var1 = 0.1;
		double var2 = 0.2;
		std::cout << var1 + var2 << std::endl;
		std::cout << var1 - var2 << std::endl;
		std::cout << var1 / var2 << std::endl;
		std::cout << var1 * var2 << std::endl;
	}
}
```
При генерации "сложной" функции:
```cpp
#include <iostream>

void TestFunction() {
	{
		float var1 = 0.1;
		float var2 = 0.2;
		float var3 = 0.3;
		float var4 = 0.4;
		std::cout << "(var1 + var2) / var3 = " << (var1 + var2) / var3 << std::endl;
		std::cout << "(var2 + var3) * var4 = " << (var2 + var3) * var4 << std::endl;
		std::cout << "var2 + var4 = " << var2 + var4 << std::endl;
		std::cout << "var1 - var3 = " << var1 - var3 << std::endl;
	}

	{
		unsigned int var1 = 1;
		unsigned int var2 = 2;
		unsigned int var3 = 3;
		unsigned int var4 = 4;
		std::cout << "(var1 + var2) / var3 = " << (var1 + var2) / var3 << std::endl;
		std::cout << "(var2 + var3) * var4 = " << (var2 + var3) * var4 << std::endl;
		std::cout << "var2 + var4 = " << var2 + var4 << std::endl;
		std::cout << "var1 - var3 = " << var1 - var3 << std::endl;
	}

	{
		char var1 = 'a';
		char var2 = 'b';
		char var3 = 'c';
		char var4 = 'd';
		std::cout << "(var1 + var2) / var3 = " << (var1 + var2) / var3 << std::endl;
		std::cout << "(var2 + var3) * var4 = " << (var2 + var3) * var4 << std::endl;
		std::cout << "var2 + var4 = " << var2 + var4 << std::endl;
		std::cout << "var1 - var3 = " << var1 - var3 << std::endl;
	}

}

```