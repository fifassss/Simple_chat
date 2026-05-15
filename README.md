# Ru: 

# Simple_chat
Простой чат(Клиент-сервер) на C++ с помощью WINSOCK(сокетов)

## Возможности
Сервер:


Принимает подключения от нескольких клиентов.


Обрабатывает сообщения от клиентов и пересылает их другим подключенным пользователям.


Работает в многопоточном режиме, обеспечивая одновременную работу с несколькими клиентами.


Причесляет Айди(В доработке пока что)

Клиент:


Подключается к серверу.


Отправляет сообщения на сервер.


Получает и отображает сообщения других участников чата.


Отображает айди юзера(в доработке)

## Стркутура 

Webtest.cpp: Файл с кодом для работы серверной части.


ClientWebtest.cpp: Файл с кодом для работы клиентской части.


## Как использовать


# Требования

1 Операционная система - Windows.


2 Компилятор с поддержкой стандарта C++11 и выше.


3 Библиотека WinSock2 для работы с сетевыми сокетами.


# Как запускать?


Сначало компилим сервер и запускаем его после компилим клиент и запускаем.


Клиент же должен ввести айпи адресс для требоваемого подключения


После успешного подключения необходимо ввести имя пользователя.


Далее клиент может отправлять сообщения в чат. Сообщения будут отправляться на сервер, который пересылает их другим участникам чата.


Для выхода из чата вводим команду 'exit'.

# Eng:

simple chat(client-server) on C++,made with help sockets(library winsock)

# Features

Server : 

Accept connection from some clients

Work in multithreading

assigns id(users) in WIP.(Work in progress)

It processes messages from customers and forwards them to other connected users.

Client:

Connection on server

Send message on server

receives and out message other clients chat

out id(user).In WIP(Work in progress).

# Structure

Webtest.cpp : file with code server part

Clientwebtest.cpp : file with code client part

# How using

# Requirements

1 Os - Windows.

2 Compiler with support standard C++11 and upper

3 library winsock2 for work to web sockets.

# How start

Start with compile server and run.After compile client and run.

client have to enter Ip-adress,for connection

After successful connection,client have to enter nickname.

and use chat for chatting.

For exit from chat enter command 'exit'
