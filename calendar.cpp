#include "calendar.h"
#include <QWidget>
#include <QInputDialog>
#include <QTextCharFormat>
#include <QDebug>
#include <QtGlobal>
#include <QDropEvent>
#include <QMouseEvent>
#include <QApplication>
#include "draglabel.h"


calendar::calendar()
{
    setAcceptDrops(true);
    qDebug() << ( Q_DECLARE_PRIVATE(QCalendarWidget) ) <<endl;
}

calendar::~calendar()
{

}

void calendar::dragEnterEvent(QDragEnterEvent *event)
{
     event->acceptProposedAction();
     installEventFilter(this);
}

bool calendar::eventFilter(QObject* obj,QEvent* ev)
{
    if(obj==this && ev->type() == QEvent::MouseButtonPress)
        qDebug() << (static_cast<QMouseEvent*>(ev) ->button() == Qt::LeftButton ? "pL" : "pR") <<endl;
    else
        if(obj==this && ev->type() == QEvent::MouseButtonRelease)
        	qDebug() << (static_cast<QMouseEvent*>(ev) ->button() == Qt::LeftButton ? "rL" : "rR") <<endl;
        else
        	qDebug()<<"other event[]"<< ev->type() <<endl;

    return false;
}

void calendar::dropEvent(QDropEvent *event)
{
    qDebug()<<"drop"<<endl;
    qDebug()<<event->pos().x()<<" , "<<event->pos().y()<<endl;
    QMouseEvent *my_click1 = new QMouseEvent( QEvent::MouseButtonPress , event->pos() , Qt::LeftButton , Qt::LeftButton , 0);
    QMouseEvent *my_click2 = new QMouseEvent( QEvent::MouseButtonRelease , event->pos() , Qt::LeftButton , Qt::LeftButton , 0);
    
    QApplication::postEvent(QWidget::focusWidget(),my_click1);
    QApplication::postEvent(QWidget::focusWidget(),my_click2);
    
    qDebug() << (QWidget::focusWidget() == this) <<endl;

    event->acceptProposedAction();
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






