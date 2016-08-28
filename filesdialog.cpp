#include "filesdialog.h"
#include "filewidget.h"
#include <QLayout>
#include <QScrollArea>

FilesDialog::FilesDialog(const QString dpath,const QList<QString>& files)
{
    QVBoxLayout *Layout = new QVBoxLayout;
    Layout ->setContentsMargins(0, 0, 0, 0);

    for(int i=0;i<files.size();++i)
    {
        QString f_name = files[i];
        if(QFile::exists(dpath+f_name))
		{
			FileWidget *fw= new FileWidget(dpath+f_name,f_name);
            fw->setMinimumSize(200,30);
        	Layout ->addWidget(fw);
        }
    }
    Layout ->addStretch();

    QScrollArea *scroll = new QScrollArea(this);
    QWidget *tmp = new QWidget;
    tmp->setLayout(Layout);
    tmp->setMinimumSize(390,390);

    scroll->setWidget(tmp);

}


