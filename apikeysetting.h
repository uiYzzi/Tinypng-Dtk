#ifndef APIKEYSETTING_H
#define APIKEYSETTING_H
#include <DMainWindow>
#include <QWidget>

DWIDGET_USE_NAMESPACE
class apikeysetting : public QWidget
{
        Q_OBJECT
public:
    apikeysetting(QWidget *parent = nullptr);
    ~apikeysetting();
};

#endif // APIKEYSETTING_H
