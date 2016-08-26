#include "draglabel.h"

DragLabel::DragLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.1);
}
