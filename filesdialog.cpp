#include "filesdialog.h"
#include "filewidget.h"
#include <QLayout>

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
        	Layout ->addWidget(fw);
        }
    }
    Layout ->addStretch();

    setLayout(Layout);


}


