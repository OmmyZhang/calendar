#ifndef C_W_H
#define C_W_H
#include "calendar.h"
#include "switchcontrol.h"
#include <QPushButton>
#include <QLabel>
class CalendarWindow : public QWidget
{
    Q_OBJECT

public:
        CalendarWindow();
private:
        calendar* mainbody;
        QPushButton *fix;
        SwitchControl *sc;


};

#endif
