#ifndef F_D_H
#define F_D_H

#include <QLabel>
#include <QDialog>
#include <QDate>
#include <QList>

class FilesDialog : public QDialog
{
    Q_OBJECT

    public:
        FilesDialog(const QString dpath,const QList<QString>& files);

};


#endif
