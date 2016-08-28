#include "filewidget.h"
#include <QMimeData>
#include <QPixmap>
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QDir>
#include <QUrl>

FileWidget::FileWidget(const QString _url , const QString& f_name):url(_url)
{
    QHBoxLayout *Layout = new QHBoxLayout;
    Layout ->setContentsMargins(0,0,0,0);

    QLabel *file_p = new QLabel;
    file_p ->setPixmap(QPixmap("pic/file.png"));
    Layout->addWidget(file_p);
    Layout->addWidget(new QLabel(f_name.right(f_name.length()-1)));
    Layout->addStretch();
    setLayout(Layout);
}

void FileWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << url <<endl;
    QMimeData *mimeData = new QMimeData;
/*
    QList < QUrl> urls;
    //urls.push_back(QUrl(url));
    urls.push_back(QUrl("/home/zhangyn/a.out"));

    mimeData->setUrls(urls);
    mimeData->setText(QUrl("file:///home/zhangyn/a.out").toEncoded());
    //mimeData->setData("application/x-hotspot",QByteArray::number(hotSpot.x()) + " " + QByteArray::number(hotSpot.y()));
*/
	QString ab_url = QString("file://")+ QDir::current().path() +QString("/")+ url + QString("\n");
	qDebug() << ab_url << endl;
	QByteArray qa(ab_url.toUtf8());
	//QByteArray qa("file:///home/zhangyn/zyn_calendar/usr_data/周二 7月 26 2016/ipv6\n");
	mimeData ->setData("text/uri-list",qa);
	mimeData ->setData("text/plain",qa);	
	mimeData ->setData("text/plain;charset=utf-8",qa);	
	
	
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap("pic/file.png"));
    drag->setHotSpot(QPoint(pos().x(),event->pos().y()));

    if(drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
        hide();
}


