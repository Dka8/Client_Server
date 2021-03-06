Тестовое задание для ***
на должность: Junior C++ developer (разработчик C++) 
выполнил: Юшков Иван

Тестовое задание:
			Необходимо написать две программы, клиент и сервер. Сервер принимает 
			сообщения от клиента по протоколам UDP и TCP и отправляет их обратно 
			клиенту, т.е. работает в режиме эха. Клиент читает сообщения 
			произвольной длины с консоли и отправляет их на сервер. Протокол, по 
			которому отправляет сообщения клиент, указывается при его запуске.

			Размер сообщения не фиксированный, но не более 65 кб. Важно, чтобы 
			объем передаваемых по сети данных был минимально необходимым.

			Задание должно быть выполнено на языке С++ (уместное применение 
			ООП/STL приветствуется), с использованием Berkeley Sockets для работы с 
			сетью.
			Применение библиотек и фреймвоков наподобие Qt или boost для работы с 
			сетью при выполнении задания не допускается.

			Простое дополнение к работе сервера (помимо эхо-функции при 
			реализации максимально возможно использовать STL):
				- во входном сообщении найти вхождения всех чисел от 0 до 9 и 
				вывести на консоль:
					* их сумму;
					* все числа, в порядке убывания;
					* максимальное и минимальное значения.
-----------------------------------------------------------------------------------------------------					
В результа выполнения задания было создан проект Client_server, в который входят следующие компоненты,
3 библиотеки и 2 исполняемых файла:
	1 — Network_lib - 	предназначена для работы с сетью и является ОПП оберткой Berkeley Sockets.
		Состоит из следующих заголовочных файлов:
		1) Config.hpp - 	определяет переменные среды в зависимости от используемой
					операционной системы для корректной работы
					системных сетевых библиотек библиотек
		2) SocketBE.hpp -	в зависимости от операциооной системы подключает
					необходимые заголовочные файлы.
		3) SocketBE_Unix.hpp -  необходимые библиотеки и логика работы с Berkeley Sockets в Unix
		4) SocketBE_Win.hpp -	необходимые библиотеки и логика работы с Berkeley Sockets в Windows
		5) IpAddress.hpp -	класс для работы с IPv4
		6) SafeTypes.hpp - 	определ¤ем безопасные типы, которые можно безопасно
					передавать по сети
		7) SocketHandle.hpp - 	описывает какое внутреннее обозначение сокета
					используется в системе
		8) Socket.hpp -		класс, описывающий протоколонезависимые методы работы с сокетами
		9) TcpSocket.hpp -	класс, описывает специфические методы, применимые при использовании
					сокетов по протоколу Tcp
		10) TcpListener.hpp - 	вспомогательный класс при работе по протоколу Tcp
		11) UdpSocket.hpp - 	класс, описывает специфические методы, применимые при использовании
					сокетов по протоколу Udp
		
	2 — Server_lib - 	предназначена для осуществления функциональности сервера в пределах
				тестового задания (режим эха, обработка входящей строки).
				Двухпоточное приложение.
				Дополнительный поток обрабатывает команды, вводимые через консоль.
				В частности команду "quit", которая завершает работу приложение Server_main
				Также конструктор класса Server может принимать указатель на функцию,
				которая будет обрабатывать полученные данные (в данном случаем,
				это функция @StringHandler, она находится в файле Server_main.cpp,
				находит вхождения всех цифр в строке и производит дальнейшую их обработку)
	3 — Client_lib -	предназначена для осуществления функциональности сервера в пределах
				тестового задания (выбор протокола передачи данных при запуске,
				принятие пользовательной строки, ожидание ответа сервера и его отображение)
		Состоит из следующих заголовочных файлов:
		1) Client.hpp - 	класс интерфейс, описывает общие методы работы клиента,
					управление протоколами реализовано при помощи паттерна "стратегия"
		2) Protocol.h -		содержит базовый класс-интерфейс Protocol и два класса
					наследника UDP и TCP, в которых реализована логика работы
					с сервером в зависимости от выбранного протокола.
					Выбор протокола передачи осуществляется при запуске
					приложения Client_main, через аргументы консоли.
-----------------------------------------------------------------------------------------------------
Исполняемые файлы Client_main.exe и Server_main.exe создаются на основе Client_main.cpp и Server_main.cpp
соответственно.
Исполняемые файлы находятся в корневой директории проекта Client_Server
-----------------------------------------------------------------------------------------------------
Сборка осуществляется с помощью CMake, файл CMakeLists.txt находится в корневой директории проекта
-----------------------------------------------------------------------------------------------------
Замечания по дальнейшему совершенствованию проекта (DOTO list):
	1.	Добавить возможность выбора портов для Udp и Tcp при запуске сервера.
	2.	Добавить возможность указания порта для подключения, при запуске клиента.
	3.	Добавить возможность указания Ip для подключения, при запуске клиента.
	4.	Расширить список консольных команд для сервера.
	5.	Добавить возможность отправки клиентом нескольких сообщений подряд.
