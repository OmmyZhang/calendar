#ifndef CALENDAR_H
#define CALENDAR_H

#include<QCalendarWidget>
#include <QPainter>
#include <QColor>
#include <QDate>
#include <QPen>
#include <QBrush>
#include <QMap>
#define REPEAT 42

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

protected:
    virtual void paintCell(QPainter * painter, const QRect & rect, const QDate & date) const;
    
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

public slots:
    void mode_changed(bool f_mode);

private slots:
    void addNote( const QDate & );
    void interseting_repaint();

private:
    QString PATH;
    QDate find(QPoint);
    void add_file(QString,const QDate);

    void save();
    void load();

    bool f_mode;
    QDate *recent_d;
    QRect *recent_r;
    int *head;

    QMap<QDate , bool> visit;
    QMap<QDate , QString> once_todo;
    QMap<QDate , bool> i_m,i_w,i_d;
    QMap<QDate , QColor*> cell_color;
    QMap<QDate , QList<QString> > files;
    QString monthly_todo[32];
    QString weekly_todo[8];
    QString daily;

};

#endif // CALENDAR_H
