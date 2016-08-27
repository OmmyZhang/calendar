#include "calendarwindow.h"
#include <QLayout>
#include <QGroupBox>

CalendarWindow::CalendarWindow() : _fixed(false)
{
    mainbody = new calendar;
    mainbody ->setWindowOpacity(0.3);
    mainbody ->setFirstDayOfWeek(Qt::Monday);

    fix = new QPushButton;
    fix ->setFixedSize(20,20);

    sc = new SwitchControl;
    sc->setDisabledColor(Qt::red);

    connect(sc,SIGNAL(toggled(bool)),mainbody,SLOT(mode_changed(bool)));

    QHBoxLayout *ButtonsLayout = new QHBoxLayout;
    ButtonsLayout ->addWidget(fix);
    ButtonsLayout ->addWidget(new QLabel(tr("Notes Mode")));
    ButtonsLayout ->addWidget(sc);
    ButtonsLayout ->addWidget(new QLabel(tr("File Mode")));

    QWidget *box = new QWidget;
    box ->setFixedSize(245,35);
    box->setLayout(ButtonsLayout);

    QVBoxLayout *Layout = new QVBoxLayout;
    Layout ->addWidget(box);
    Layout ->addWidget(mainbody);

    setLayout(Layout);

    myrect= new XRectangle;
    //fixed();
    connect(fix,SIGNAL(clicked()),this,SLOT(fixed()));
}

void CalendarWindow::fixed()
{
	_fixed = ! _fixed;
	
    if(_fixed)
    {
        setWindowOpacity(0.2);
    
   //     setMinimumSize(width(),height());
    //    setMaximumSize(width(),height());
    
    //layout() ->setSizeConstraint(QLayout::SetFixedSize);
    //layout() ->setSizeConstraint(QLayout::SetNoConstraint);

        myrect->x = 0;
        myrect->y = 0;
        myrect->width = width();
        myrect->height = height();

        XShapeCombineRectangles(QX11Info::display(), winId(), ShapeInput, 0, 0, myrect ,0 ,ShapeSet,YXBanded);
//    }
//    else
//    {
        myrect->x = 0;
        myrect->y = 0;
        myrect->width = width();
        myrect->height = 75;
        
  //      setMinimumSize(0,0);
   //     setMaximumSize(100000,100000);

		XShapeCombineRectangles(QX11Info::display(), winId(), ShapeInput, 0, 0, myrect ,1 ,ShapeSet,YXBanded);
		//setWindowOpacity(0.8);
	}
    
}
