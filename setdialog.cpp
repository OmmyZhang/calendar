#include "setdialog.h"
#include <QLayout>
#include <QDebug>

SetDialog::SetDialog(QString& once,QString& monthly,QString& weekly,QString& daily)
{
    setWindowTitle(tr("Edit reminders"));

    m_once    = new EditReminder(tr("Once:    "),once);
    if(!once.length()) m_once->hide();
    
    m_monthly = new EditReminder(tr("Monthly:"),monthly);
    if(!monthly.length()) m_monthly->hide();
    
    m_weekly = new EditReminder(tr("Weekly:"),weekly);
    if(!weekly.length()) m_weekly->hide();
    
    m_daily = new EditReminder(tr("Daily: "),daily);
    if(!daily.length()) m_daily->hide();

    connect(m_once->b_save,SIGNAL(clicked()),this,SLOT(any_change()));
    connect(m_monthly->b_save,SIGNAL(clicked()),this,SLOT(any_change()));
    connect(m_weekly->b_save,SIGNAL(clicked()),this,SLOT(any_change()));
    connect(m_daily->b_save,SIGNAL(clicked()),this,SLOT(any_change()));
    
    QVBoxLayout *Layout = new QVBoxLayout;
    Layout->addWidget(m_once);
    Layout->addWidget(m_monthly);
    Layout->addWidget(m_weekly);
    Layout->addWidget(m_daily);
       

    QHBoxLayout *AddReminderLayout = new QHBoxLayout;

    new_r= new QLineEdit;
    new_add = new QPushButton(tr("Add"));

    combo = new QComboBox;
    combo->addItem(tr("Once"),QVariant::fromValue((QObject*)m_once));
    combo->addItem(tr("Monthly"),QVariant::fromValue((QObject*)m_monthly));
    combo->addItem(tr("Weekly"),QVariant::fromValue((QObject*)m_weekly));
    combo->addItem(tr("Daily"),QVariant::fromValue((QObject*)m_daily));

    AddReminderLayout ->addWidget(new QLabel(tr("New:  ")));
    AddReminderLayout ->addWidget(new_r);
    AddReminderLayout ->addWidget(combo);
    AddReminderLayout ->addWidget(new_add);

    connect(new_add,SIGNAL(clicked()),this,SLOT(add()));

    Layout->addLayout(AddReminderLayout);
    setLayout(Layout);

}

void SetDialog::add()
{
    if(new_r ->text().length() == 0) return;
    EditReminder *choice = qobject_cast<EditReminder*>( qvariant_cast<QObject*>(combo ->itemData(combo ->currentIndex())) ) ;
    if(choice)
    {
        qDebug() << choice->todo <<" "<<new_r->text() <<endl;
        choice->save();
        if(choice->todo.length())
                choice->todo += QString(";");
        choice->todo += new_r ->text();
        choice->reset(); 
        choice->show();

        new_r->clear();
        any_change();
    }
    else
        qDebug()<<"bad"<<endl;

}

void SetDialog::any_change()
{
    emit repaint_the_calendar();
}
