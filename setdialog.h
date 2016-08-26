#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include "editreminder.h"
class SetDialog : public QDialog
{
    Q_OBJECT
    public:
        SetDialog(QString& once,QString& monthly,QString& weekly,QString& daily);

    private:
        EditReminder *m_once,*m_monthly,*m_weekly,*m_daily;
        QLineEdit *new_r;
        QPushButton *new_add;
        QComboBox *combo;
    private slots:
        void add();
        void any_change();
    signals:
        void repaint_the_calendar();    

};


#endif
