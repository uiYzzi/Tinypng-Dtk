#include "mainwindow.h"
#include <DTitlebar>
#include <DMainWindow>

DWIDGET_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
        m_menu(new QMenu),
        m_apikey(new QAction("API KEY"))

{

    m_apikey->setCheckable(true);
    m_menu->addAction(m_apikey);
    titlebar()->setMenu(m_menu);
    w = new FileChooseWidget;
    //connect(m_apikey, &QAction::triggered, this, &MainWindow::handleTrayIconTriggered);
    resize(w->size()); //设置窗口大小
    //setWindowOpacity(0.5);
    setFixedSize(480, 380);
    //setTitlebarShadowEnabled(false);//取消标题栏阴影
    setCentralWidget(w);
    DTitlebar *tb = titlebar();
    tb->setTitle("");
    tb->setBlurBackground(true);//启用标题栏毛玻璃

}

MainWindow::~MainWindow()
{

}
