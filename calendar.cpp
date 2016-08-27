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
    head = new int(0);
    recent_d = new QDate[REPEAT];
    recent_r = new QRect[REPEAT];

    setAcceptDrops(true);
}

calendar::~calendar()
{

}

void calendar::dragEnterEvent(QDragEnterEvent *event)
{
     event->acceptProposedAction();
     installEventFilter(this);
}

void calendar::dropEvent(QDropEvent *event)
{
    qDebug()<<"drop"<<endl;
    qDebug()<<event->pos().x()<<" , "<<event ->pos().y()<<endl;

    QMouseEvent *e1 = new QMouseEvent( QEvent::MouseButtonPress , event->pos() , Qt::LeftButton , Qt::LeftButton , 0);
    QMouseEvent *e2 = new QMouseEvent( QEvent::MouseButtonRelease , event->pos() , Qt::LeftButton , Qt::LeftButton , 0);
    QMouseEvent *e3 = new QMouseEvent( QEvent::MouseButtonDblClick , event->pos() , Qt::LeftButton , Qt::LeftButton , 0);
	QApplication::sendEvent(app,e1);
	QApplication::sendEvent(app,e2);	
	QApplication::sendEvent(app,e3);

    QDate choose = find(event ->pos());
    qDebug()<< choose <<endl;
    if(choose.isNull())
        return ;

   // addNote(choose);

    event->acceptProposedAction();
}

QDate calendar::find(QPoint p)
{
    for(int i=0;i<REPEAT;++i)
        if(recent_r[i].contains(p,true))
        {
            qDebug()<<recent_r[i].bottom()<<" "<<recent_r[i].top()<<endl;
            return recent_d[i];
        }
    return QDate();
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
    //qDebug()<<"come in paintCell "<<date.toString()<<rect.bottom()<<" "<<rect.top()<<endl;
    
    recent_d[*head] = date; 
    recent_r[*head] = rect;
    (*head) = ((*head)+1) % REPEAT;

    QCalendarWidget::paintCell(painter, rect, date);
	
	QString all=once_todo[date];
    QString _n = QString("\n");
    if(all.length())
        all+=_n;
	if(monthly_todo[date.day()].length() && !i_m[date])
		all+=monthly_todo[date.day()]+_n;
    if(weekly_todo[date.dayOfWeek()].length() && !i_w[date])
		all+=weekly_todo[date.dayOfWeek()]+_n;
    bool something = (all.length()>0); 
	if(daily.length() && !i_d[date])
       all+=daily+_n;

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






