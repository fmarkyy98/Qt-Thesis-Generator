#include "thesislottery.h"

#include <QApplication>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    ThesisLottery w;
    w.show();
    return a.exec();
}
