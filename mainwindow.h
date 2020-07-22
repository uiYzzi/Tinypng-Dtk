#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include "filechoosewidget.h"
#include <QMenu>

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    FileChooseWidget *w;
    QMenu *m_menu;
    QAction *m_apikey;
};

#endif // MAINWINDOW_H
