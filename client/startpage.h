#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class StartPage;
}

class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = 0);
    ~StartPage();
    Ui::StartPage *ui;

public slots:
    void connected();
    void slotStartClicked();
    void slotChangeStart(int);
    void slotPlayWithBot();
    //void slotGetName();

signals:
    void signStartClicked(QString);
    void signStartClicked();
    void signPlayWithBot();
};

#endif // STARTPAGE_H
