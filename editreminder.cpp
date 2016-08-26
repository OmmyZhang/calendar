#include "editreminder.h"
#include <QLayout>
#include <QDebug>
EditReminder::EditReminder(QString _title,QString& _todo,bool repeat,bool& _ignore) 
    : todo(_todo) , ignore(_ignore)
{
    QHBoxLayout *Layout = new QHBoxLayout;
    Layout->addWidget(new QLabel(_title));

    el = new QLineEdit(todo);
    Layout->addWidget(el);

    b_save = new QPushButton(tr("save"));
    b_reset = new QPushButton(tr("reset"));
    Layout->addWidget(b_save);
    Layout->addWidget(b_reset);

    c_ignore = new QCheckBox(tr("ignore it this day"));
    Layout->addWidget(c_ignore);
    if(!repeat)
    {
    	c_ignore->hide();
    	Layout->addWidget(new QLabel(tr("          Only this day       ")));
    }
    c_ignore->QAbstractButton::setChecked(ignore);

    setLayout(Layout);
    
    connect(c_ignore,SIGNAL(stateChanged(int)),this,SLOT(change_ignore(int)));
    connect(b_save ,SIGNAL(clicked()),this,SLOT(save()));
    connect(b_reset,SIGNAL(clicked()),this,SLOT(reset()));
    
}

void EditReminder::save()
{
    todo = el->text(); 
}

void EditReminder::reset()
{
    el->setText(todo);
}

void EditReminder::change_ignore(int x)
{
	qDebug() << "change" <<endl;
    ignore = (x==2);
}

