#include "calendarwindow.h"
#include <QLayout>

CalendarWindow::CalendarWindow()
{
    mainbody = new calendar;
    mainbody ->setFirstDayOfWeek(Qt::Monday);
    QObject::connect(mainbody,SIGNAL(activated(const QDate &)),mainbody,SLOT(addNote(const QDate &)));

    fix = new QPushButton;
    fix ->setFixedSize(25,25);

    QHBoxLayout *ButtonsLayout = new QHBoxLayout;
    ButtonsLayout ->addWidget(fix);

    QVBoxLayout *Layout = new QVBoxLayout;
    Layout ->addLayout(ButtonsLayout);
    Layout ->addWidget(mainbody);

    setLayout(Layout);
    

}
