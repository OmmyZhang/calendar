#include "calendarwindow.h"
#include <QLayout>
#include <QGroupBox>


CalendarWindow::CalendarWindow()
{
    mainbody = new calendar;
    mainbody ->setFirstDayOfWeek(Qt::Monday);
    QObject::connect(mainbody,SIGNAL(activated(const QDate &)),mainbody,SLOT(addNote(const QDate &)));

    fix = new QPushButton;
    fix ->setFixedSize(20,20);

    sc = new SwitchControl;
    sc->setDisabledColor(Qt::red);

    connect(sc,SIGNAL(toggled(bool)),mainbody,SLOT(mode_changed(bool)));

    QHBoxLayout *ButtonsLayout = new QHBoxLayout;
    ButtonsLayout ->addWidget(fix);
    ButtonsLayout ->addWidget(new QLabel(tr("Note Mode")));
    ButtonsLayout ->addWidget(sc);
    ButtonsLayout ->addWidget(new QLabel(tr("File Mode")));

    QWidget *box = new QWidget;
    box ->setFixedSize(240,35);
    box->setLayout(ButtonsLayout);

    QVBoxLayout *Layout = new QVBoxLayout;
    Layout ->addWidget(box);
    Layout ->addWidget(mainbody);

    setLayout(Layout);
    

}
