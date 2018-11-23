#include "launchermainwindows.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LauncherMainWindows w;
    w.show();

    return a.exec();
}
