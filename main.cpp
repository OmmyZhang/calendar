#include <QApplication>
#include "calendar.h"
#include "calendarwindow.h"
#include <QDesktopWidget>
#include <QTranslator>

//#define T_CN

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef T_CN
    QTranslator qtTranslator; 
    qtTranslator.load("cn.qm");
    a.installTranslator(&qtTranslator); 
#endif
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();

    CalendarWindow* calew = new CalendarWindow(screenRect);
    calew->resize(QSize(screenRect.width()*2/3, screenRect.height()*2/3));
    calew->setWindowOpacity(0.8);
    calew->setWindowFlags(Qt::FramelessWindowHint );
    calew->show();


    return a.exec();
}
