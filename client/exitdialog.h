#ifndef EXITDIALOG_H
#define EXITDIALOG_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class ExitDialog;
}

class ExitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExitDialog(QWidget *parent = 0);
    ~ExitDialog();

private:
    Ui::ExitDialog *ui;

private slots:
    void slotChangeLableWin(bool);
};

#endif // EXITDIALOG_H
