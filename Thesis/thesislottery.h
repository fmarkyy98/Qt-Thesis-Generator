#ifndef THESISLOTTERY_H
#define THESISLOTTERY_H

#include <QWidget>
#include <QQueue>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class ThesisLottery; }
QT_END_NAMESPACE

class ThesisLottery : public QWidget
{
    Q_OBJECT

public:
    ThesisLottery(QWidget *parent = nullptr);
    ~ThesisLottery();

private slots:
    void on_options_Button_clicked();
    void on_start_Button_clicked();
    void on_timer_timeout();
    void on_NumberOfIndividuals_spinBox_valueChanged(int arg1);

private:
    Ui::ThesisLottery *ui;
    bool optionsVisibility = true;
    int thesisNumber = 21;
    int numberOfIndividuals = 5;
    QVector<int> thesises;
    QQueue<int> forbiddens;
    QTimer timer;
    int rnd;

    void swapVisibility();
    void init();
    void thesisManagement();
};
#endif // THESISLOTTERY_H
