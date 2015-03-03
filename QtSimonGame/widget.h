#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>

namespace Ui {
class Widget;
}

enum state_e
{
    WAIT_START = 0,
    PLAY_SEQUENCE,
    PLAY_SEQUENCE_2,
    WAIT_INPUT,
};

enum state_machine_events_e
{
    START = 0,
    TIMER,
    INPUT,
};

enum buttonIndex_e
{
    RED = 0,
    BLUE,
    GREEN,
    YELLOW,
};

typedef struct
{
    state_e state;
    int playSequenceIndex;
    int waitInputIndex;
    int checkSequenceIndex;
    int level;
} stateMachine_str;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void state_machine_signal(enum state_machine_events_e event, enum buttonIndex_e button = RED);

private slots:
    void on_pushButtonYellow_pressed();
    void on_pushButtonYellow_released();
    void on_pushButtonGreen_pressed();
    void on_pushButtonGreen_released();
    void on_pushButtonRed_pressed();
    void on_pushButtonRed_released();
    void on_pushButtonBlue_pressed();
    void on_pushButtonBlue_released();
    void on_pushButtonStart_clicked();
    void state_machine_process(enum state_machine_events_e event, enum buttonIndex_e button = RED);
    void timeout();

private:

    void InitIcons();
    void InitButtons();
    int randInt(int low, int high);
    void playSequenceIndex();
    void setAllButtonsOff();
    void InitStateMachine();

    Ui::Widget *ui;
    QIcon *yellowOnIcon;
    QIcon *yellowOffIcon;
    QIcon *greenOnIcon;
    QIcon *greenOffIcon;
    QIcon *blueOnIcon;
    QIcon *blueOffIcon;
    QIcon *redOnIcon;
    QIcon *redOffIcon;
    buttonIndex_e generatedSequence[100];
    buttonIndex_e inputSequence[100];
    stateMachine_str stateMachine;
    QTimer timer;


};

#endif // WIDGET_H
