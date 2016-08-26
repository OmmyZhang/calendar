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
    setAcceptDrops(true);
}

calendar::~calendar()
{

}


void calendar::addNote( const QDate &date )
{
    qDebug()<<"come in addNote"<<endl;
    setwindow = new SetDialog(once_todo[date],monthly_todo[date.day()],weekly_todo[date.dayOfWeek()],daily,
                                                i_m[date] , i_w[date] , i_d[date],cell_color[date]);

    //无法靠update()或repaint()解决问题，只能先这样了
    connect(setwindow,SIGNAL(repaint_the_calendar()),this,SLOT(hide()));
    connect(setwindow,SIGNAL(repaint_the_calendar()),this,SLOT(show()));
    setwindow->exec();
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
	if(monthly_todo[date.day()].length() && !i_m[date])
		all+=QString("\n")+monthly_todo[date.day()];
    if(weekly_todo[date.dayOfWeek()].length() && !i_w[date])
		all+=QString("\n")+weekly_todo[date.dayOfWeek()];
    bool something = (all.length()>0); 
	if(daily.length() && !i_d[date])
       all+=QString("\n")+daily;


//    connect(setwindow,SIGNAL(repaint_the_calendar()),setwindow,SLOT(hide()));
//    connect(setwindow,SIGNAL(repaint_the_calendar()),setwindow,SLOT(show()));

    if(something || cell_color[date])
    {

	    QColor brushcolor;
	    if(cell_color[date])
   	    	brushcolor=*cell_color[date];
   	    else
   			brushcolor=Qt::yellow;

        brushcolor.setAlpha(100);

        painter->setBrush(brushcolor);
    }
    else
        painter->setBrush(Qt::transparent);

        if(something)
            painter->setPen(QPen(Qt::red,2));
        else
            painter->setPen(QPen(Qt::black,0.7));

	painter->drawRect(rect.adjusted(0, 0, -1, -1));	  
	painter->setPen(Qt::blue);
	painter->drawText(rect,Qt::TextWordWrap,all);

}






