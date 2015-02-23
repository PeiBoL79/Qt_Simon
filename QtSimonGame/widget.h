#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButtonYellow_pressed();

    void on_pushButtonYellow_released();

    void on_pushButtonGreen_pressed();

    void on_pushButtonGreen_released();

    void on_pushButtonRed_pressed();

    void on_pushButtonRed_released();

    void on_pushButtonBlue_pressed();

    void on_pushButtonBlue_released();

private:

    void InitIcons();
    void InitButtons();

    Ui::Widget *ui;
    QIcon *yellowOnIcon;
    QIcon *yellowOffIcon;
    QIcon *greenOnIcon;
    QIcon *greenOffIcon;
    QIcon *blueOnIcon;
    QIcon *blueOffIcon;
    QIcon *redOnIcon;
    QIcon *redOffIcon;
};

#endif // WIDGET_H
