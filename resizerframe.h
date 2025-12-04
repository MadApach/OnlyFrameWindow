#ifndef RESIZERFRAME_H
#define RESIZERFRAME_H

#include <QFrame>
#include <QMouseEvent>
#include <QWidget>

class ResizerFrame : public QFrame
{
    Q_OBJECT

public:
    ResizerFrame(Qt::Edges type, QWidget *parent = nullptr);

signals:
    void mousePressed(bool on);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Qt::Edges m_edgeType;
    QPoint m_dragPosition;
    bool m_dragging = false;
};

#endif // RESIZERFRAME_H
