#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>
#include <QString>
class SetDialog : public QDialog
{
    Q_OBJECT
    public:
        SetDialog(QString& once,QString& monthly,QString& weekly,QString& daily);
};


#endif
