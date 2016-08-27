#include "calendar.h"
#include <QWidget>
#include <QInputDialog>
#include <QTextCharFormat>
#include <QDebug>
#include <QtGlobal>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QDir>
#include <QMessageBox>
#include "draglabel.h"

#define DOC "usr_data/.document.zyn"
#define ST(x) ( (x).length() ? (x) : "<empty>" )
#define TS(x) ( ((x)=="<empty>") ? ("") : (x) )

calendar::calendar() : PATH("usr_data/"),f_mode(false)
{
    head = new int(0);
    recent_d = new QDate[REPEAT];
    recent_r = new QRect[REPEAT];

    setAcceptDrops(f_mode);
    load();
    
	connect(this,SIGNAL(activated(const QDate &)),this,SLOT(addNote(const QDate &)));
}

calendar::~calendar()
{
}

void calendar::save()
{
    QFile doc(DOC);
    if( doc.open(QIODevice::WriteOnly | QIODevice::Truncate) )
    {
        QTextStream op(&doc);
        op << "Start saving. Key:xfgcfhjknbvcr567ugbhnjkmo75rdtcfgvhjvc54trdfctt6tgfgy6ygy7ygygft5rf3ghvjbBNUI8uy7uh98uygbhj887ygg7ygt65rdrtt" <<endl;    

        for(int i=1;i<=31;++i)
            op << ST(monthly_todo[i]) << endl;
        op << "-------" << endl;
        for(int i=1;i<=7;++i)
            op << ST(weekly_todo[i]) << endl;
        op << "-------" << endl;
        op << ST(daily) << endl;
        op << "-------" << endl;
        
        QMap< QDate, bool>::const_iterator it;
        for(it = visit.begin();it!=visit.end();++it)
        {
            QDate date = it.key();
            op << date.year() << " " << date.month() << " " << date.day() << endl;
            op << ST(once_todo[date]) << endl;
            op << i_m[date] <<" "<< i_w[date] <<" "<< i_d[date] << endl;
            if(cell_color[date])
                op << 1 << endl << cell_color[date]->rgb() <<endl;
            else 
                op << 233333 <<endl;
            int si = files[date].size();
            op << si <<endl;
            for(int i=0;i<si;++i)
                op << files[date][i] <<endl;
        }
        doc.close();
    }
    else
        QMessageBox::warning(this,tr("waring"),tr("Something wrong.Can't save."));
}

void calendar::load()
{
    QFile doc(DOC);
    if(doc.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream ip(&doc);
        int y,m,d;
        QString s = ip.readLine();
        qDebug() << s << endl;
        if(s != QString("Start saving. Key:xfgcfhjknbvcr567ugbhnjkmo75rdtcfgvhjvc54trdfctt6tgfgy6ygy7ygygft5rf3ghvjbBNUI8uy7uh98uygbhj887ygg7ygt65rdrtt"))
        {
        	QMessageBox::warning(this,tr("Warning!"),tr("The document file has be changed.Loading fail."));
        	return ;
        }
     
        for(int i=1;i<=31;++i)
        {
            s=ip.readLine();
            monthly_todo[i] = TS(s);
        }
        s=ip.readLine(); //
        for(int i=1;i<=7;++i)
        {
            s=ip.readLine();
            weekly_todo[i] = TS(s);
        }
        s=ip.readLine(); //
        s=ip.readLine();
        daily=TS(s);
        s=ip.readLine(); //

        while(!ip.atEnd())
        {
            
        	ip >> y >> m >> d; s = ip.readLine();
            QDate date(y,m,d); visit[date]=true;
            qDebug() << date.toString() << endl;
            
            s = ip.readLine();
            once_todo[date]=TS(s);

            qDebug() << s << endl;

            int im,iw,id;
            ip >> im >> iw >> id;
            i_m[date] = im; i_w[date] = iw; i_d[date] = id;

            ip >> y;
            if(y==1)
            {
                unsigned rgb;
                ip >> rgb;
                cell_color[date] = new QColor(rgb);
            }
            
            ip >> y;ip.readLine();
            for(int i=0;i<y;++i)
            {
                s = ip.readLine();
                if(QFile::exists( PATH + date.toString() + s ) )
                    files[date].push_back(s);
            }
        
		}

    }
    else
        QMessageBox::about(this,tr("Hello"),tr("It seems you are a new user. Enjoy it!"));
}

void calendar::mode_changed(bool _f_mode)
{
    setAcceptDrops(f_mode=_f_mode);
    interseting_repaint();

}
void calendar::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void calendar::dropEvent(QDropEvent *event)
{
    qDebug()<<"drop"<<endl;
    qDebug()<<event->pos().x()<<" , "<<event ->pos().y()<<endl;

    QDate choose = find(event ->pos());
    qDebug()<< choose <<endl;
    if(choose.isNull())
    {
        QMessageBox::warning(this,"Warring!",tr("please drop it in a cell"));
        return ;
    }
    
    visit[choose]=true;

    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) 
    {
        QList<QUrl> urlList = mimeData->urls();
        for (int i = 0; i < urlList.size(); ++i) 
        {
            QString url = urlList.at(i).path();
            add_file(url,choose);
            qDebug() << url <<endl;
        }
    }
    else
        qDebug()<<"wrong"<<endl;
   // addNote(choose);

    event->acceptProposedAction();
}

void calendar::add_file(QString url,const QDate date)
{
    qDebug() << url[0] <<endl;
    int p=url.length()-2;
    while(url[p]!='/') --p;
    QString file_name=url.right( url.length() - p );

    QDir dir(PATH);
    dir.mkdir(date.toString());
    if(QDir(url).exists())
        QMessageBox::warning(this,tr("Fail!"),tr("Copying a directory is not allowed."));
    else
    if(QFile::copy( url , PATH + date.toString() + file_name ) == false)
        QMessageBox::warning(this,tr("Fail to copy ")+file_name.right(file_name.length()-1),tr("Copying Failed,please check if it is a local file or if it alrealdy exists."));
    else
    {
        files[date].push_back(file_name);
        interseting_repaint();
    }

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
    visit[date] = true;

    if(f_mode)
    {

        return ;
    }

    setwindow = new SetDialog(once_todo[date],monthly_todo[date.day()],weekly_todo[date.dayOfWeek()],daily,i_m[date] , i_w[date] , i_d[date],cell_color[date]);
    connect(setwindow,SIGNAL(repaint_the_calendar()),this,SLOT(interseting_repaint()));
    setwindow->exec();
}


void calendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    //qDebug()<<"come in paintCell "<<date.toString()<<rect.bottom()<<" "<<rect.top()<<endl;
    
    recent_d[*head] = date; 
    recent_r[*head] = rect.translated(0,25);
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

    if(f_mode)
        something = false;

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
        painter->setPen(QPen(Qt::black,0.8));

	painter->drawRect(rect.adjusted(0, 0, -1, -1));	  
	painter->setPen(Qt::blue);
    
    if(f_mode)
    {
        painter->setPen(Qt::black);
        QFont font("宋体",7,-1,true);
        painter->setFont(font);
        all=QString("");
        for(int i=0 ; i < files[date].size() ; ++i )
            all+=files[date][i].right(files[date][i].length()-1)  +_n;
        painter->drawText(rect,all);
    }
    else
    {
        painter->setPen(Qt::darkBlue);
        QFont font("宋体",9,-1);
        painter->setFont(font);
	    painter->drawText(rect,Qt::TextWordWrap,all);
    }

}

void calendar::interseting_repaint()
{
    //无法靠update()或repaint()解决问题，只能先这样了
    hide();
    show();
    save();
}




