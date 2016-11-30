#ifndef DISCONNECTIONPAGE_H
#define DISCONNECTIONPAGE_H

#include <QWidget>

namespace Ui {
class DisconnectionPage;
}

class DisconnectionPage : public QWidget
{
    Q_OBJECT

public:
    explicit DisconnectionPage(QWidget *parent = 0);
    ~DisconnectionPage();

private:
    Ui::DisconnectionPage *ui;
};

#endif // DISCONNECTIONPAGE_H
