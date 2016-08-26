#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QColor>
#include "editreminder.h"
class SetDialog : public QDialog
{
    Q_OBJECT
    public:
        SetDialog(QString& once,QString& monthly,QString& weekly,QString& daily,bool& i_m,bool& i_w,bool& i_d,QColor*& _cc);

        QColor* &cc;
    private:
        EditReminder *m_once,*m_monthly,*m_weekly,*m_daily;
        QLineEdit *new_r;
        QPushButton *new_add,*c_c;
        QComboBox *combo;
    private slots:
        void add();
        void any_change();
        void chooseColor();
    signals:
        void repaint_the_calendar();    

};


#endif
