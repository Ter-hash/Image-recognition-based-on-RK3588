/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *frame;
    QLabel *picture;
    QLabel *title;
    QTextBrowser *recve;
    QPushButton *identiyfBt;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1024, 600);
        frame = new QLabel(Widget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(130, 180, 231, 171));
        picture = new QLabel(Widget);
        picture->setObjectName(QStringLiteral("picture"));
        picture->setGeometry(QRect(660, 180, 231, 181));
        title = new QLabel(Widget);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(370, 80, 211, 41));
        QFont font;
        font.setPointSize(24);
        title->setFont(font);
        title->setAlignment(Qt::AlignCenter);
        recve = new QTextBrowser(Widget);
        recve->setObjectName(QStringLiteral("recve"));
        recve->setGeometry(QRect(60, 500, 491, 41));
        identiyfBt = new QPushButton(Widget);
        identiyfBt->setObjectName(QStringLiteral("identiyfBt"));
        identiyfBt->setGeometry(QRect(680, 500, 161, 41));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        frame->setText(QApplication::translate("Widget", "TextLabel", 0));
        picture->setText(QApplication::translate("Widget", "TextLabel", 0));
        title->setText(QApplication::translate("Widget", "\346\231\272\350\203\275\351\201\223\351\227\270\347\263\273\347\273\237", 0));
        identiyfBt->setText(QApplication::translate("Widget", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
