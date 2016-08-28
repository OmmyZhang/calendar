#ifndef  F_W_H
#define F_W_H

#include <QWidget>
#include <QMouseEvent>

class FileWidget : public QWidget
{
    public:
        FileWidget(const QString url,const QString& f_name);

    protected:
        void mousePressEvent(QMouseEvent *event);
    private:
        QString url;
};

#endif
