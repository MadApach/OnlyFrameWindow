cmake_minimum_required(VERSION 3.16)

project(OnlyFrameWindow VERSION 1.0)

# Найти пакет Qt Widgets (для Qt6)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Включаем автоматическую обработку MOC, UIC, RCC
# Это автоматически обрабатывает Q_OBJECT в заголовочных файлах
qt_standard_project_setup()

# Добавить исполняемый файл
add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
    transparentwindow.cpp
    resizerframe.cpp
    transparentwindow.h
    resizerframe.h
)

# Прилинковать библиотеки Qt к нашему исполняемому файлу
target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        Qt6::Widgets
)
