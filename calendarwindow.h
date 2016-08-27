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
        CalendarWindow();
private:
        calendar* mainbody;
        QPushButton *fix;
        SwitchControl *sc;
        XRectangle *myrect;
        bool _fixed;
private slots:
        void fixed();


};

#endif
