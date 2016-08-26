#ifndef CALENDAR_H
#define CALENDAR_H

#include<QCalendarWidget>
#include <QPainter>
#include <QColor>
#include <QDate>
#include <QPen>
#include <QBrush>
#include <QMap>
#include "setdialog.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class calendar: public QCalendarWidget
{
    Q_OBJECT
public:
    calendar();
    ~calendar();

    void setColor(QColor& color);
    QColor getColor();
protected:
    virtual void paintCell(QPainter * painter, const QRect & rect, const QDate & date) const;

private slots:
    void addNote( const QDate & );

private:
    QDate m_currentDate;
    QPen m_outlinePen;
    QBrush m_transparentBrush;

    QMap<QDate , QString> once_todo;
    QString weekly_todo[7];
    QString monthly_todo[31];
    QString daily;

    SetDialog *setwindow;

};

#endif // CALENDAR_H
