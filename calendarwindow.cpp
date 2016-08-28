#include "calendarwindow.h"
#include <QLayout>
#include <QGroupBox>

//#define T_CN

CalendarWindow::CalendarWindow(QRect _sr) : _fixed(false),sr(_sr)
{
    mainbody = new calendar;
    mainbody ->setWindowOpacity(0.3);
    mainbody ->setFirstDayOfWeek(Qt::Monday);

    clo = new QPushButton(QIcon("pic/clo.png"),"");
    clo ->setFixedSize(20,20);
    clo ->setIconSize(QSize(20,20));
    clo ->setFlat(true);
    clo ->setFocusPolicy(Qt::NoFocus);;

    fix = new QPushButton(QIcon("pic/fix.png"),"");
    fix ->setFixedSize(20,20);
    fix ->setIconSize(QSize(20,20));
    fix ->setFlat(true);
    fix ->setFocusPolicy(Qt::NoFocus);

    sc = new SwitchControl;
    sc->setDisabledColor(Qt::red);

    connect(clo,SIGNAL(clicked()),this,SLOT(close()));
    connect(fix,SIGNAL(clicked()),this,SLOT(fixed()));
    connect(sc,SIGNAL(toggled(bool)),mainbody,SLOT(mode_changed(bool)));

    QHBoxLayout *ButtonsLayout = new QHBoxLayout;
    ButtonsLayout ->addWidget(clo);
    ButtonsLayout ->addWidget(fix);
    ButtonsLayout ->addWidget(new QLabel(tr("Notes Mode")));
    ButtonsLayout ->addWidget(sc);
    ButtonsLayout ->addWidget(new QLabel(tr("File Mode")));

    QWidget *box = new QWidget;
#ifdef T_CN
    box ->setFixedSize(240,35);
#else
    box ->setFixedSize(272,35);
#endif

    box->setLayout(ButtonsLayout);

    QVBoxLayout *Layout = new QVBoxLayout;
    Layout ->setContentsMargins(0, 0, 0, 15);
    Layout ->addWidget(box);
    Layout ->addWidget(mainbody);

    setLayout(Layout);

    myrect= new XRectangle;
    //fixed();
}

void CalendarWindow::fixed()
{
	_fixed = ! _fixed;
	
    if(_fixed)
    {
        setWindowOpacity(0.2);
    
        setMinimumSize(width(),height());

        setMaximumSize(width(),height());


        myrect->x = 0;
        myrect->y = 0;
        myrect->width = width();
        myrect->height = height();

        XShapeCombineRectangles(QX11Info::display(), winId(), ShapeInput, 0, 0, NULL ,0 ,ShapeSet,YXBanded);

        myrect->x = 0;
        myrect->y = 0;
        myrect->width = 280;
        myrect->height = 35;


		XShapeCombineRectangles(QX11Info::display(), winId(), ShapeInput, 0, 0, myrect ,1 ,ShapeSet,YXBanded);

	}
	else
	{
		setWindowOpacity(0.8);
        
        
        myrect->x = 0;
        myrect->y = 0;
        myrect->width  = sr.width();
        myrect->height = sr.height();
        
                
        setMinimumSize(600,400);
        setMaximumSize(sr.size());

        XShapeCombineRectangles(QX11Info::display(), winId(), ShapeInput, 0, 0, myrect ,1 ,ShapeSet,YXBanded);	
	
	}
    
}
