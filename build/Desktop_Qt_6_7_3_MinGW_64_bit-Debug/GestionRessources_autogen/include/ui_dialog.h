/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLineEdit *id;
    QLineEdit *password;
    QPushButton *loginbutton;
    QLabel *label_13;
    QLabel *label_3;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(1321, 910);
        Dialog->setStyleSheet(QString::fromUtf8("background-color:#F8EDEB;\n"
""));
        id = new QLineEdit(Dialog);
        id->setObjectName("id");
        id->setGeometry(QRect(470, 330, 391, 51));
        id->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #4e1764;\n"
"    border-radius: 5px;\n"
"    background-color: white;\n"
"    padding: 4px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 3px solid #9f86c0;\n"
"    background-color: white;\n"
"}\n"
""));
        password = new QLineEdit(Dialog);
        password->setObjectName("password");
        password->setGeometry(QRect(470, 400, 391, 51));
        password->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #4e1764;\n"
"    border-radius: 5px;\n"
"    background-color: white;\n"
"    padding: 4px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 3px solid #9f86c0;\n"
"    background-color: white;\n"
"}\n"
""));
        password->setEchoMode(QLineEdit::Normal);
        password->setCursorMoveStyle(Qt::LogicalMoveStyle);
        loginbutton = new QPushButton(Dialog);
        loginbutton->setObjectName("loginbutton");
        loginbutton->setGeometry(QRect(450, 500, 421, 51));
        loginbutton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border: 2px solid #4e1764;\n"
"    border-radius: 5px;\n"
"    color: black;\n"
"    font-weight: bold;\n"
"    padding: 8px;\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #f1d9f1;\n"
"    border: 2px solid #9f86c0;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #e0c6f0;\n"
"    border: 2px solid #9f86c0;\n"
"}\n"
""));
        label_13 = new QLabel(Dialog);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(360, 50, 661, 181));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setBold(true);
        font.setItalic(true);
        label_13->setFont(font);
        label_13->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background: white;\n"
"    color: #333333;\n"
"    font-size: 25px;\n"
"    padding: 5px;\n"
"    border: 2px solid #4e1764;\n"
"    border-radius: 14px;\n"
"}\n"
""));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(380, 590, 591, 41));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        id->setPlaceholderText(QCoreApplication::translate("Dialog", "identifiant", nullptr));
        password->setPlaceholderText(QCoreApplication::translate("Dialog", "password", nullptr));
        loginbutton->setText(QCoreApplication::translate("Dialog", "Se Connecter", nullptr));
        label_13->setText(QCoreApplication::translate("Dialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:36pt;\">Bienvenue Chez</span></p><p align=\"center\"><span style=\" font-size:36pt;\">InnovArch</span></p><p align=\"center\"><span style=\" font-size:36pt;\"><br/></span></p></body></html>", nullptr));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
