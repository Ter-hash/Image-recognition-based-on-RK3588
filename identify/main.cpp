#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font;

    font.setPointSize(16);

    font.setFamily(("wenquanyi"));

    font.setBold(false);

    a.setFont(font);

    Widget w;
    w.show();

    return a.exec();
}
