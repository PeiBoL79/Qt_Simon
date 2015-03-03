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
    InitStateMachine();
    connect(&timer, timer.timeout, this, timeout);
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
    emit state_machine_signal(INPUT, YELLOW);
}

void Widget::on_pushButtonGreen_pressed()
{
    ui->pushButtonGreen->setIcon(*greenOnIcon);
}

void Widget::on_pushButtonGreen_released()
{
    ui->pushButtonGreen->setIcon(*greenOffIcon);
    emit state_machine_signal(INPUT, GREEN);
}

void Widget::on_pushButtonRed_pressed()
{
    ui->pushButtonRed->setIcon(*redOnIcon);
}

void Widget::on_pushButtonRed_released()
{
    ui->pushButtonRed->setIcon(*redOffIcon);
    emit state_machine_signal(INPUT, RED);
}

void Widget::on_pushButtonBlue_pressed()
{
    ui->pushButtonBlue->setIcon(*blueOnIcon);
}

void Widget::on_pushButtonBlue_released()
{
    ui->pushButtonBlue->setIcon(*blueOffIcon);
    emit state_machine_signal(INPUT, BLUE);
}

void Widget::on_pushButtonStart_clicked()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    for(int i = 0; i < 100; i++)
    {
        generatedSequence[i] = (buttonIndex_e)randInt(0,3);
    }

    emit state_machine_signal(START);
}

int Widget::randInt(int low, int high)
{
// Random number between low and high
return qrand() % ((high + 1) - low) + low;
}

void Widget::state_machine_process(enum state_machine_events_e event, enum buttonIndex_e button)
{
    switch(stateMachine.state)
    {
        case WAIT_START:
            if(event == START)
            {
                stateMachine.state = PLAY_SEQUENCE;
                timer.setSingleShot(true);
                timer.start(100);
            }
        break;
        case PLAY_SEQUENCE:
            if(event == TIMER)
            {
                setAllButtonsOff();
                if(stateMachine.playSequenceIndex != stateMachine.level)
                {
                    playSequenceIndex();
                    stateMachine.playSequenceIndex++;
                    stateMachine.state = PLAY_SEQUENCE_2;
                }
                else
                {
                    stateMachine.playSequenceIndex = 0;
                    stateMachine.state = WAIT_INPUT;
                }
                timer.start(500);
            }
        break;
        case PLAY_SEQUENCE_2:
            setAllButtonsOff();
            stateMachine.state = PLAY_SEQUENCE;
            timer.start(100);
        break;
        case WAIT_INPUT:
            if(event == INPUT)
            {
                if(button != generatedSequence[stateMachine.waitInputIndex])
                {
                    qDebug() << "FIN\n";
                    stateMachine.state = WAIT_START;
                    stateMachine.level = 1;
                    stateMachine.waitInputIndex = 0;
                }
                else
                {
                    inputSequence[stateMachine.waitInputIndex] = button;
                    stateMachine.waitInputIndex++;
                    if(stateMachine.waitInputIndex == stateMachine.level)
                    {
                        stateMachine.state = PLAY_SEQUENCE;
                        stateMachine.waitInputIndex = 0;
                        stateMachine.level++;
                        timer.start(500);
                    }
                }
            }
        break;
    }
}

void Widget::setAllButtonsOff()
{
    ui->pushButtonYellow->setIcon(*yellowOffIcon);
    ui->pushButtonBlue->setIcon(*blueOffIcon);
    ui->pushButtonGreen->setIcon(*greenOffIcon);
    ui->pushButtonRed->setIcon(*redOffIcon);
}

void Widget::playSequenceIndex()
{
    switch(generatedSequence[stateMachine.playSequenceIndex])
    {
        case YELLOW:
            ui->pushButtonYellow->setIcon(*yellowOnIcon);
        break;
        case BLUE:
            ui->pushButtonBlue->setIcon(*blueOnIcon);
        break;
        case GREEN:
            ui->pushButtonGreen->setIcon(*greenOnIcon);
        break;
        case RED:
            ui->pushButtonRed->setIcon(*redOnIcon);
        break;
    }
}

void Widget::InitStateMachine()
{
    stateMachine.level = 1;
    stateMachine.state = WAIT_START;
    stateMachine.checkSequenceIndex = 0;
    stateMachine.playSequenceIndex = 0;
    stateMachine.waitInputIndex = 0;
    connect(this, state_machine_signal, this, state_machine_process);
}

void Widget::timeout()
{
    emit state_machine_signal(TIMER);
}
