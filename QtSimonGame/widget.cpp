#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QIcon>
#include <QFile>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    InitIcons();
    InitButtons();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::InitButtons()
{
    ui->pushButtonBlue->setIcon(*blueOffIcon);
    ui->pushButtonGreen->setIcon(*greenOffIcon);
    ui->pushButtonRed->setIcon(*redOffIcon);
    ui->pushButtonYellow->setIcon(*yellowOffIcon);
}

void Widget::InitIcons()
{
    QPixmap yellowOn(":Images/Yellow_On.png");
    yellowOnIcon = new QIcon(yellowOn);
    QPixmap yellowOff(":Images/Yellow_Off.png");
    yellowOffIcon = new QIcon(yellowOff);

    QPixmap greenOn(":Images/Green_On.png");
    greenOnIcon = new QIcon(greenOn);
    QPixmap greenOff(":Images/Green_Off.png");
    greenOffIcon = new QIcon(greenOff);

    QPixmap blueOn(":Images/Blue_On.png");
    blueOnIcon = new QIcon(blueOn);
    QPixmap blueOff(":Images/Blue_Off.png");
    blueOffIcon = new QIcon(blueOff);

    QPixmap redOn(":Images/Red_On.png");
    redOnIcon = new QIcon(redOn);
    QPixmap redOff(":Images/Red_Off.png");
    redOffIcon = new QIcon(redOff);
}

void Widget::on_pushButtonYellow_pressed()
{
    ui->pushButtonYellow->setIcon(*yellowOnIcon);
}

void Widget::on_pushButtonYellow_released()
{
    ui->pushButtonYellow->setIcon(*yellowOffIcon);
}

void Widget::on_pushButtonGreen_pressed()
{
    ui->pushButtonGreen->setIcon(*greenOnIcon);
}

void Widget::on_pushButtonGreen_released()
{
    ui->pushButtonGreen->setIcon(*greenOffIcon);
}

void Widget::on_pushButtonRed_pressed()
{
    ui->pushButtonRed->setIcon(*redOnIcon);
}

void Widget::on_pushButtonRed_released()
{
    ui->pushButtonRed->setIcon(*redOffIcon);
}

void Widget::on_pushButtonBlue_pressed()
{
    ui->pushButtonBlue->setIcon(*blueOnIcon);
}

void Widget::on_pushButtonBlue_released()
{
    ui->pushButtonBlue->setIcon(*blueOffIcon);
}
