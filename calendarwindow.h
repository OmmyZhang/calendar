#ifndef C_W_H
#define C_W_H
#include "calendar.h"
#include "switchcontrol.h"
#include <QPushButton>
#include <QLabel>

#include <X11/extensions/shape.h>
#include <QX11Info>

class CalendarWindow : public QWidget
{
    Q_OBJECT

public:
        CalendarWindow(QRect);
private:
        calendar* mainbody;
        QPushButton *clo,*fix;
        SwitchControl *sc;
        XRectangle *myrect;
        bool _fixed;
        QRect sr;
private slots:
        void fixed();


};

#endif
