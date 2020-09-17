#include "thesislottery.h"
#include "ui_thesislottery.h"
#include <QTime>

ThesisLottery::ThesisLottery(QWidget *parent) : QWidget(parent), ui(new Ui::ThesisLottery)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->thesisNumber_spinBox->setValue(this->thesisNumber);
    ui->NumberOfIndividuals_spinBox->setValue(this->numberOfIndividuals);
    swapVisibility();
    init();
    qsrand(QTime::currentTime().msec());
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
}

ThesisLottery::~ThesisLottery()
{
    delete ui;
}

void ThesisLottery::swapVisibility()
{
    this->optionsVisibility = !this->optionsVisibility;
    ui->NumberOfIndividuals_label->setVisible(this->optionsVisibility);
    ui->NumberOfIndividuals_spinBox->setVisible(this->optionsVisibility);
    ui->thesisNumber_label->setVisible(this->optionsVisibility);
    ui->thesisNumber_spinBox->setVisible(this->optionsVisibility);
    ui->options_Button->setText(this->optionsVisibility ? "Submit" : "Options");
    ui->start_Button->setEnabled(!this->optionsVisibility);
}

void ThesisLottery::init()
{
    this->thesises.clear();
    this->forbiddens.clear();
    for(int i = 1; i <= thesisNumber; ++i)
    {
        thesises.push_back(i);
    }
}

void ThesisLottery::thesisManagement()
{
    this->forbiddens.enqueue(this->thesises[rnd]);
    this->thesises[rnd] = this->thesises[this->thesises.length() - 1];
    this->thesises.pop_back();
    if(forbiddens.length() > this->numberOfIndividuals)
    {
        this->thesises.push_back(this->forbiddens.dequeue());
    }
}

void ThesisLottery::on_timer_timeout()
{
    rnd = qrand() % this->thesises.length();
    ui->lineEdit->setText(QString::number(this->thesises[rnd]));
}

void ThesisLottery::on_options_Button_clicked()
{
    swapVisibility();
    if(!this->optionsVisibility)
    {
        this->thesisNumber = ui->thesisNumber_spinBox->value();
        this->numberOfIndividuals = ui->NumberOfIndividuals_spinBox->value();
        init();
        ui->lineEdit->setText("");
    }
}

void ThesisLottery::on_start_Button_clicked()
{
    if(!timer.isActive())
    {
        timer.start(1);
        ui->start_Button->setText("STOP");
        ui->options_Button->setEnabled(false);
    }
    else
    {
        timer.stop();
        ui->start_Button->setText("START");
        ui->options_Button->setEnabled(true);
        thesisManagement();
    }
}

void ThesisLottery::on_NumberOfIndividuals_spinBox_valueChanged(int arg1)
{
   ui->thesisNumber_spinBox->setMinimum(arg1 + 1);
}
