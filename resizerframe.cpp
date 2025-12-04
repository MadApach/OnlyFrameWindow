#include "resizerframe.h"
#include <QHBoxLayout>
#include <QCursor>
#include <QWindow>
#include <QPushButton>

ResizerFrame::ResizerFrame(Qt::Edges type, QWidget *parent)
    : QFrame(parent), m_edgeType(type)
{
    // Устанавливаем курсоры для наглядности
    if (type == Qt::TopEdge)
    {
        setCursor(Qt::OpenHandCursor);
        auto closeButton = new QPushButton("X", this);
        closeButton->setFixedSize(50, this->height());
        closeButton->setStyleSheet("background-color: blue; color: white; border: none;");
        closeButton->setCursor(Qt::ArrowCursor);

        // Подключаем сигнал нажатия кнопки к нашему слоту
        connect(closeButton, &QPushButton::clicked, [] {qApp->quit();});

        // Используем QHBoxLayout для размещения кнопки справа
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->addStretch(); // Растягивает пустое пространство слева
        layout->addWidget(closeButton); // Добавляет кнопку справа
        layout->setContentsMargins(0, 0, 0, 0);
        setLayout(layout);

    }
    else if(type == Qt::BottomEdge) {
        setCursor(Qt::SizeVerCursor);
    } else if (type == Qt::LeftEdge || type == Qt::RightEdge) {
        setCursor(Qt::SizeHorCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

void ResizerFrame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = true;
        m_dragPosition = event->pos();
        // Захватываем мышь, пока не отпустим
        grabMouse();
    }
    emit mousePressed(true);
}

void ResizerFrame::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging) {
        QWidget *p = parentWidget();

        // Если это верхняя рамка, перетаскиваем все родительское окно
        if (m_edgeType == Qt::TopEdge) {
            setCursor(Qt::ClosedHandCursor);
            p->move(p->mapToGlobal(event->pos() - m_dragPosition));
        }
        // Иначе меняем размер родительского окна
        else {
            // Отправляем системный запрос на изменение размера
            if (p->windowHandle()) {
                p->windowHandle()->startSystemResize(m_edgeType);
            }
        }
    }
}

void ResizerFrame::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_dragging) {
        if (m_edgeType == Qt::TopEdge) {
            setCursor(Qt::OpenHandCursor);
        }
        m_dragging = false;
        releaseMouse();
    }
    emit mousePressed(false);
}
