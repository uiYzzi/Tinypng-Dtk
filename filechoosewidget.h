#ifndef FILECHOOSEWIDGET_H
#define FILECHOOSEWIDGET_H

#include "choosefilebutton.h"
#include <QWidget>
#include <QSettings>
#include <DLabel>
DWIDGET_USE_NAMESPACE


namespace Ui {
class FileChooseWidget;
}

class FileChooseWidget : public QWidget
{
    Q_OBJECT
signals:
    void packagesSelected(const QStringList files) const;

public:
    explicit FileChooseWidget(QWidget *parent = nullptr);
    ~FileChooseWidget();
private slots:
    void chooseFiles();
    void tinypng(QStringList selected_files);

private:
    DLabel *m_iconImage {nullptr};
    DLabel *m_dndTips {nullptr};
    DLabel *split_line {nullptr};
    QSettings m_settings;
    ChooseFileButton *m_chooseFileBtn {nullptr};

};

#endif // WIDGET_H
