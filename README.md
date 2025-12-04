# OnlyFrameWindow (Рамка для записи экрана)

## Описание проекта

Это приложение представляет собой утилиту, предназначенную для помощи в **записи определенной области экрана**.

Оно создает видимую рамку с прозрачным внутренним содержимым. Основная цель — визуально обозначить на экране точную область (viewport), в которой должно располагаться основное содержимое других окон или приложений во время захвата экрана (скринкастинга), чтобы обеспечить единообразный и точный захват кадра.

Проект разработан с использованием **Qt 6** и **C++17**.

## Сборка и запуск

Проект использует CMake для управления сборкой.

### Требования

Для успешной сборки вам понадобятся:

*   **Компилятор C++17:** GCC/G++ (MinGW) или MSVC (Visual Studio).
*   **CMake:** Версии 3.16 или новее.
*   **Qt 6:** Версия 6.x.

### Сборка на Windows

Рекомендуется использовать компилятор MSVC, который соответствует используемой версии Qt.

```bash
git clone git@github.com:MadApach/OnlyFrameWindow.git
cd OnlyFrameWindow
mkdir build
cd build
cmake ..
cmake --build . --config Release
````

Собранный исполняемый файл будет находиться в папке build/Release/.

### Сборка на Ubuntu/Linux

```bash
sudo apt update
sudo apt install qt6-base-dev cmake build-essential
git clone git@github.com:MadApach/OnlyFrameWindow.git
cd OnlyFrameWindow
mkdir build
cd build
cmake ..
make
````

Собранный исполняемый файл будет находиться в папке build/.

### Использование

Запустите исполняемый файл (./OnlyFrameWindow или OnlyFrameWindow.exe). На экране появится прозрачное окно с видимой рамкой. Вы можете перемещать и изменять размер этой рамки, чтобы обозначить нужную область захвата.

### Лицензия

Этот проект распространяется под лицензией MIT.

# OnlyFrameWindow (Screen Recording Frame)

## Project Description

This application is a utility designed to assist with **recording a specific area of the screen**.

It creates a visible frame with a transparent inner content area. The main purpose is to visually mark the exact viewport on the screen where content should fit while capturing the screen (screencasting), ensuring consistent and precise frame capture.

The project is developed using **Qt 6** and **C++17**.

## Building and Running

The project uses CMake for managing the build process.

### Requirements

To successfully build the project, you need the following:

*   **C++17 Compiler:** GCC/G++ (MinGW) or MSVC (Visual Studio).
*   **CMake:** Version 3.16 or newer.
*   **Qt 6:** Version 6.x.

### Building on Windows

It is recommended to use the MSVC compiler that matches the version of Qt being used.

```bash
git clone git@github.com:MadApach/OnlyFrameWindow.git
cd OnlyFrameWindow
mkdir build
cd build
cmake ..
cmake --build . --config Release
````

The compiled executable file will be located in the build/Release/ folder.

### Building on Ubuntu/Linux

```bash
sudo apt update
sudo apt install qt6-base-dev cmake build-essential
git clone git@github.com:MadApach/OnlyFrameWindow.git
cd OnlyFrameWindow
mkdir build
cd build
cmake ..
make
````

The compiled executable file will be located in the build/ folder.

### Usage

Run the executable file (./OnlyFrameWindow or OnlyFrameWindow.exe). A transparent window with a visible frame will appear on the screen. You can move and resize this frame to designate the desired capture area.
Screenshots

### License

This project is distributed under the MIT License.
