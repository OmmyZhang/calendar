#include <QApplication>
#include "calendar.h"
#include "calendarwindow.h"
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();

    CalendarWindow* calew = new CalendarWindow();
    calew->resize(QSize(screenRect.width()*2/3, screenRect.height()*2/3));
    calew->setWindowOpacity(0.9);
    calew->show();


    return a.exec();
}
