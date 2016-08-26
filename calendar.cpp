#include "calendar.h"
#include <QWidget>
#include <QInputDialog>
#include <QTextCharFormat>
#include <QDebug>
#include <QtGlobal>
#include "draglabel.h"


calendar::calendar()
{
    m_outlinePen.setColor(Qt::red);
    m_transparentBrush.setColor(Qt::transparent);
    setAcceptDrops(true);
}

calendar::~calendar()
{

}


void calendar::addNote( const QDate &date )
{
    qDebug()<<"come in addNote"<<endl;
    setwindow = new SetDialog(once_todo[date],monthly_todo[date.day()],weekly_todo[date.dayOfWeek()],daily);

    //无法靠update()或repaint()解决问题，只能先这样了
    connect(setwindow,SIGNAL(repaint_the_calendar()),this,SLOT(hide()));
    connect(setwindow,SIGNAL(repaint_the_calendar()),this,SLOT(show()));
    setwindow->exec();
/*
    QString memo = QInputDialog::getText( this,
            "Memo", "Description:" );

    if( !memo.isEmpty() )
    {
        QBrush brush;
        brush.setColor(Qt::yellow);

        QTextCharFormat cf = this->dateTextFormat(date);
        cf.setBackground(brush);
        this->setDateTextFormat(date, cf);
        if(dates.contains(date))
        {
            int index = dates.indexOf(date);
            todolist.replace(index, memo);
        }
        else
        {
            dates.append(date);
            todolist.append(memo);
        }
    }
*/
}

void calendar::setColor(QColor& color)
{
   m_outlinePen.setColor(color);
}

QColor calendar::getColor()
{
   return (m_outlinePen.color());
}

void calendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
   //qDebug()<<"come in paintCell"<<endl;
   QCalendarWidget::paintCell(painter, rect, date);
   
   QString all=once_todo[date];
   if(monthly_todo[date.day()].length())
       all+=QString("\n")+monthly_todo[date.day()];
   if(weekly_todo[date.dayOfWeek()].length())
       all+=QString("\n")+weekly_todo[date.dayOfWeek()];
   if(daily.length())
       all+=QString("\n")+daily;

   painter->setPen(m_outlinePen);
   painter->setBrush(m_transparentBrush);
   painter->drawRect(rect.adjusted(0, 0, -1, -1));
   painter->setPen(Qt::blue);
   painter->drawText(rect,Qt::TextWordWrap,all);

}






