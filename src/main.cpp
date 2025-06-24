#include "MainWidget.h"

#include <QApplication>

int main(int iArgc, char** pArgv)
{
    QApplication App(iArgc, pArgv);

    MainWidget Wdg;
    Wdg.show();

    return App.exec();
}
