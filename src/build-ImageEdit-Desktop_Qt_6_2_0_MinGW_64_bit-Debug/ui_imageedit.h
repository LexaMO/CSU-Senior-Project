/********************************************************************************
** Form generated from reading UI file 'imageedit.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEEDIT_H
#define UI_IMAGEEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_imageedit
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *imageedit)
    {
        if (imageedit->objectName().isEmpty())
            imageedit->setObjectName(QString::fromUtf8("imageedit"));
        imageedit->resize(800, 600);
        centralwidget = new QWidget(imageedit);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        imageedit->setCentralWidget(centralwidget);
        menubar = new QMenuBar(imageedit);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        imageedit->setMenuBar(menubar);
        statusbar = new QStatusBar(imageedit);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        imageedit->setStatusBar(statusbar);

        retranslateUi(imageedit);

        QMetaObject::connectSlotsByName(imageedit);
    } // setupUi

    void retranslateUi(QMainWindow *imageedit)
    {
        imageedit->setWindowTitle(QCoreApplication::translate("imageedit", "imageedit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class imageedit: public Ui_imageedit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEEDIT_H
