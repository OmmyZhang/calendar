#ifndef E_R_H
#define E_R_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QCheckBox>
class EditReminder : public QWidget
{
    Q_OBJECT
    public:
        EditReminder(QString _title,QString& _todo,bool repeat,bool& ignore);
        QString& todo;
        bool& ignore;
    private:
        QLineEdit *el;
    public:
        QPushButton *b_save,*b_reset;
        QCheckBox *c_ignore;
    public slots:
        void save();
        void reset();
        void change_ignore(int);
    
};


#endif
