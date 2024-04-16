# NotesApp
NotesApp - асинхронное клиент-серверное приложение, написанное на C++, позволяющее сохранять заметки в своём аккаунте и просматривать их.

## Клиентская часть
Клиент представляет из себя кросс-платформенное приложение с графическим интерфейсом фреймфорка QT, и nlohmann для работы с JSON. Сборка происходит с помощью qmake.
Клиент может войти в свой аккаунт, просматривать свои старые заметки и писать новые. 

## Серверная часть
Серверная часть с использованием Boost.Beast.

Клиент и сервер общаются по протоколу Websocket.