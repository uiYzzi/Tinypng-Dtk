#define RUNDIR "/opt/apps/top.yzzi.tinypng/files/"
#include "filechoosewidget.h"
#include <DFileDialog>

#include <QDragEnterEvent>
#include <QMimeData>

#include <QFileInfo>
#include <QPixmap>
#include <QDebug>
#include <DLabel>
#include <QImageReader>
#include <QVBoxLayout>
#include <DApplicationHelper>
#include <sstream>
#include "utils.h"
//以下大量代码来自https://github.com/linuxdeepin/deepin-deb-installer

using namespace std;
QHash<QString, QPixmap> m_imgCacheHash;
FileChooseWidget::FileChooseWidget(QWidget *parent) :
    QWidget(parent)
{

    this->setAcceptDrops(true);
    m_iconImage = new DLabel(this);//图标
    m_iconImage->setFixedSize(110, 110);
    m_iconImage->setPixmap(Utils::renderSVG(":/new/prefix1/images/picture.svg", QSize(110, 110)));


    m_dndTips = new DLabel(this);//提示文字
    m_dndTips->setFixedHeight(30);
    m_dndTips->setAlignment(Qt::AlignTop);
    m_dndTips->setText(tr("Drag picture here"));
    m_dndTips->setObjectName("DNDTips");


    DGuiApplicationHelper *guiAppHelp = DGuiApplicationHelper::instance();
    split_line = new DLabel(this);
    split_line->setObjectName("SplitLine");//分隔线
    if (guiAppHelp->themeType() == DGuiApplicationHelper::ColorType::DarkType) {  //暗色主题
        split_line->setPixmap(Utils::renderSVG(":/new/prefix1/images/split_line_dark.svg", QSize(220, 3)));
    } else {  //浅色主题
        split_line->setPixmap(Utils::renderSVG(":/new/prefix1/images/split_line.svg", QSize(220, 3)));
    }
    split_line->setFixedHeight(3);


    m_chooseFileBtn = new ChooseFileButton("", this);
    m_chooseFileBtn->setFixedHeight(28);
    m_chooseFileBtn->setObjectName("FileChooseButton");
    m_chooseFileBtn->setText(tr("Select File"));
#ifdef SHOWBORDER
    m_chooseFileBtn->setStyleSheet("QPushButton{border:1px solid black;}");
#endif


    QVBoxLayout *centralLayout = new QVBoxLayout(this);
    centralLayout->addSpacing(55);
    centralLayout->addWidget(m_iconImage);
    centralLayout->setAlignment(m_iconImage, Qt::AlignHCenter);

    centralLayout->addSpacing(30);
    centralLayout->addWidget(m_dndTips);
    centralLayout->setAlignment(m_dndTips, Qt::AlignHCenter);

    centralLayout->addWidget(split_line);
    centralLayout->setAlignment(split_line, Qt::AlignHCenter);

    centralLayout->addSpacing(11);
    centralLayout->addWidget(m_chooseFileBtn);
    centralLayout->setAlignment(m_chooseFileBtn, Qt::AlignHCenter);
    centralLayout->addStretch();

    centralLayout->setSpacing(0);
    centralLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(centralLayout);
    connect(m_chooseFileBtn, &ChooseFileButton::clicked, this, &FileChooseWidget::chooseFiles);

}
void FileChooseWidget::chooseFiles()//选择文件
{
    QString historyDir = m_settings.value("history_dir").toString();

    if (historyDir.isEmpty()) {
        historyDir = QDir::homePath();
    }

    DFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter("Images Files (*.jpg  *.png)");
    dialog.setDirectory(historyDir);

    const int mode = dialog.exec();

    // save the directory string to config file.
    m_settings.setValue("history_dir", dialog.directoryUrl().toLocalFile());

    if (mode != QDialog::Accepted) return;

    const QStringList selected_files = dialog.selectedFiles();

    emit FileChooseWidget::tinypng(selected_files);
}



void FileChooseWidget::tinypng(QStringList selected_files)
{
    qDebug()<<selected_files;
    ostringstream mklk;
    QString pathStr;
    QString tmp;
    QString qmklk;
    int cmd;
    for(int i = 0; i< selected_files.size();++i)
    {
        tmp = selected_files.at(i);
        qDebug()<<"tmp ="<< tmp;
        pathStr=tmp.left(tmp.lastIndexOf("/"));
        qDebug()<<pathStr;
        mklk.str("");
        mklk<<RUNDIR<<"tinypng"<<" -f \""<<tmp.toStdString()<<"\" -d \""<<pathStr.toStdString()<<"\"";
        qmklk = QString::fromStdString(mklk.str());
        qDebug()<<qmklk;
        cmd=system(qmklk.toUtf8());
        qDebug()<<cmd;
        if(cmd==256)//如果返回值为256
        {
            qDebug("成功");
        }
        else if(cmd==512)
        {
            qDebug("网络错误");
        }

    }

}

FileChooseWidget::~FileChooseWidget()
{

}

