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
#include <cstdio>

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

    bool eventFilter(QObject* ,QEvent*);
protected:
    virtual void paintCell(QPainter * painter, const QRect & rect, const QDate & date) const;
    
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void addNote( const QDate & );

private:
    QDate m_currentDate;

    QMap<QDate , QString> once_todo;
    QMap<QDate , bool> i_m,i_w,i_d;
    QMap<QDate , QColor*> cell_color;
        
    QString weekly_todo[8];
    QString monthly_todo[32];
    QString daily;

    SetDialog *setwindow;

};

#endif // CALENDAR_H
