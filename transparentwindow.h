// #ifndef TRANSPARENTWINDOW_H
// #define TRANSPARENTWINDOW_H

// #include <QMainWindow> // Используем QMainWindow для системного заголовка
// #include <QHBoxLayout>
// #include <QVBoxLayout>
// #include "resizerframe.h" // Подключаем наш новый класс

// class TransparentWindow : public QWidget
// {
//     Q_OBJECT

// public:
//     TransparentWindow(QWidget *parent = nullptr);
//     ~TransparentWindow();

// protected:
//     void resizeEvent(QResizeEvent *event) override;

//     void paintEvent(QPaintEvent *) override;

// private:
//     void updateTitleWithDimensions();
//     ResizerFrame *topFrame;
//     ResizerFrame *bottomFrame;
//     ResizerFrame *leftFrame;
//     ResizerFrame *rightFrame;
//     int m_borderWidth = 5;
// };
// #endif // TRANSPARENTWINDOW_H

#ifndef TRANSPARENTWINDOW_H
#define TRANSPARENTWINDOW_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QResizeEvent>
#include <QLabel>
#include <QRegion> // Добавляем QRegion
#include "resizerframe.h" // Подключаем наш новый класс

class TransparentWindow : public QMainWindow
{
    Q_OBJECT

public:
    TransparentWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateWindowMask(); // Метод для создания маски
    void setFrameGeometry();
    void updateDimensionOverlay();
    int m_borderWidth = 5;
    ResizerFrame *topFrame;
    ResizerFrame *bottomFrame;
    ResizerFrame *leftFrame;
    ResizerFrame *rightFrame;
    QLabel *m_dimensionsOverlay = nullptr; // Виджет оверлея
};
#endif // TRANSPARENTWINDOW_H
