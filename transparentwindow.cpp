#include "transparentwindow.h"

TransparentWindow::TransparentWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // *** КЛЮЧЕВЫЕ НАСТРОЙКИ ПРОЗРАЧНОСТИ ***

    // 1. Убираем системный заголовок и рамку, чтобы ОС не мешала нашей маске
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    // 2. Делаем весь фон окна прозрачным (это должно работать в Qt 6/современном Linux)
    setAttribute(Qt::WA_TranslucentBackground);

    // 3. Устанавливаем атрибут, чтобы ОС пропускала ввод через наше окно
    //    Именно маска, которую мы установим ниже, "активирует" рамку для кликов
    setAttribute(Qt::WA_TransparentForMouseEvents);

    setGeometry(100, 100, 1280 + 2*m_borderWidth, 720 + 2*m_borderWidth);

    updateWindowMask(); // Устанавливаем начальную маску
        // --- Создаем 4 непрозрачных виджета-рамки ---
        QString frameStyle = QString("background-color: %1;");

        leftFrame = new ResizerFrame(Qt::LeftEdge, this);
        leftFrame->setStyleSheet(frameStyle.arg("red"));

        rightFrame = new ResizerFrame(Qt::RightEdge, this);
        rightFrame->setStyleSheet(frameStyle.arg("red"));

        topFrame = new ResizerFrame(Qt::TopEdge, this);
        topFrame->setStyleSheet(frameStyle.arg("magenta"));

        bottomFrame = new ResizerFrame(Qt::BottomEdge, this);
        bottomFrame->setStyleSheet(frameStyle.arg("red"));

        m_dimensionsOverlay = new QLabel(this);
        m_dimensionsOverlay->setAlignment(Qt::AlignCenter);
        m_dimensionsOverlay->setStyleSheet("color: white; font-size: 32px; background-color: rgba(0, 0, 0, 150); border-radius: 5px; padding: 5px;");
        m_dimensionsOverlay->hide();
        m_dimensionsOverlay->setAttribute(Qt::WA_TransparentForMouseEvents); // Он не будет ловить клики

        auto repaintOverlay = [this](bool on){
            m_dimensionsOverlay->setVisible(on);
            updateDimensionOverlay();
            updateWindowMask();
            repaint();
        };

        connect(leftFrame, &ResizerFrame::mousePressed, repaintOverlay);
        connect(rightFrame, &ResizerFrame::mousePressed, repaintOverlay);
        connect(bottomFrame, &ResizerFrame::mousePressed, repaintOverlay);

        setFrameGeometry();
}

void TransparentWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
}

void TransparentWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    setFrameGeometry();
    updateDimensionOverlay();
    updateWindowMask(); // Обновляем маску при изменении размера
}

void TransparentWindow::updateWindowMask()
{
    // Создаем область всего окна
    QRegion fullRegion(this->rect());

    // Создаем область для внутреннего (прозрачного) центра
    QRegion innerRegion(
        m_borderWidth, m_borderWidth,
        this->width() - 2 * m_borderWidth,
        this->height() - 2 * m_borderWidth
        );

    // Вычитаем внутреннюю область из полной области.
    // Маска останется только на границах (рамке).
    QRegion finalMask = fullRegion.subtracted(innerRegion);

    if(m_dimensionsOverlay)
    {
        QRegion dimensionRegion = m_dimensionsOverlay->geometry();
        if(m_dimensionsOverlay->isVisible())
        {
            finalMask = finalMask.united(dimensionRegion);
        }
    }

    // Устанавливаем маску: только область маски (рамка) будет ловить клики мыши.
    setMask(finalMask);
}

void TransparentWindow::setFrameGeometry()
{
    topFrame->setGeometry(0, 0, this->rect().width(), m_borderWidth);
    bottomFrame->setGeometry(0, this->rect().height() - m_borderWidth, this->rect().width(), m_borderWidth);
    leftFrame->setGeometry(0, 0, m_borderWidth, this->rect().height());
    rightFrame->setGeometry(this->rect().width() - m_borderWidth, 0, m_borderWidth, this->rect().height());
}

void TransparentWindow::updateDimensionOverlay()
{
    if(m_dimensionsOverlay->isHidden())
    {
        return;
    }
    int width = this->width() - 2 * m_borderWidth;
    int height = this->height() - 2 * m_borderWidth;
    QString sizeText = QString("%1x%2").arg(width).arg(height);

    m_dimensionsOverlay->setText(sizeText);
    // Устанавливаем геометрию так, чтобы он был по центру прозрачной области
    m_dimensionsOverlay->setGeometry(m_borderWidth, m_borderWidth, width, height);

    // Делаем его видимым и убеждаемся, что он не блокирует ввод
    m_dimensionsOverlay->setAttribute(Qt::WA_TransparentForMouseEvents);
}
