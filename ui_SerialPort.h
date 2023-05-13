/********************************************************************************
** Form generated from reading UI file 'SerialPort.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALPORT_H
#define UI_SERIALPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialPort
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QGroupBox *groupBox_SerPortSetting;
    QPushButton *OnOffBtn;
    QComboBox *FlowCtrlCmb;
    QLabel *FlowCtrlLbl;
    QLabel *SerPortLbl;
    QComboBox *PortNumCmb;
    QLabel *BoaudLbl;
    QComboBox *baudRCmb;
    QLabel *CheckLbl;
    QComboBox *DPaityCmb;
    QLabel *DataLbl;
    QComboBox *DataBCmb;
    QLabel *StopLbl;
    QComboBox *StopBCmb;
    QGroupBox *groupBox_Recv;
    QGridLayout *gridLayout_2;
    QTextEdit *RecvDataEdt;
    QPushButton *SendBtn;
    QTextEdit *SendDataEdt;
    QPushButton *ReflushSerPortBtn;
    QPushButton *ClearRecvBtn;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SerialPort)
    {
        if (SerialPort->objectName().isEmpty())
            SerialPort->setObjectName(QStringLiteral("SerialPort"));
        SerialPort->resize(703, 480);
        actionOpen = new QAction(SerialPort);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralWidget = new QWidget(SerialPort);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox_SerPortSetting = new QGroupBox(centralWidget);
        groupBox_SerPortSetting->setObjectName(QStringLiteral("groupBox_SerPortSetting"));
        groupBox_SerPortSetting->setGeometry(QRect(11, 11, 181, 321));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        groupBox_SerPortSetting->setFont(font);
        OnOffBtn = new QPushButton(groupBox_SerPortSetting);
        OnOffBtn->setObjectName(QStringLiteral("OnOffBtn"));
        OnOffBtn->setGeometry(QRect(14, 270, 151, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font1.setPointSize(16);
        OnOffBtn->setFont(font1);
        FlowCtrlCmb = new QComboBox(groupBox_SerPortSetting);
        FlowCtrlCmb->setObjectName(QStringLiteral("FlowCtrlCmb"));
        FlowCtrlCmb->setGeometry(QRect(70, 230, 100, 30));
        QFont font2;
        font2.setFamily(QStringLiteral("Source Code Pro"));
        FlowCtrlCmb->setFont(font2);
        FlowCtrlLbl = new QLabel(groupBox_SerPortSetting);
        FlowCtrlLbl->setObjectName(QStringLiteral("FlowCtrlLbl"));
        FlowCtrlLbl->setGeometry(QRect(10, 230, 53, 30));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font3.setPointSize(9);
        FlowCtrlLbl->setFont(font3);
        SerPortLbl = new QLabel(groupBox_SerPortSetting);
        SerPortLbl->setObjectName(QStringLiteral("SerPortLbl"));
        SerPortLbl->setGeometry(QRect(10, 30, 53, 30));
        SerPortLbl->setFont(font3);
        PortNumCmb = new QComboBox(groupBox_SerPortSetting);
        PortNumCmb->setObjectName(QStringLiteral("PortNumCmb"));
        PortNumCmb->setGeometry(QRect(70, 30, 100, 30));
        PortNumCmb->setFont(font2);
        BoaudLbl = new QLabel(groupBox_SerPortSetting);
        BoaudLbl->setObjectName(QStringLiteral("BoaudLbl"));
        BoaudLbl->setGeometry(QRect(10, 70, 53, 30));
        BoaudLbl->setFont(font3);
        baudRCmb = new QComboBox(groupBox_SerPortSetting);
        baudRCmb->setObjectName(QStringLiteral("baudRCmb"));
        baudRCmb->setEnabled(true);
        baudRCmb->setGeometry(QRect(70, 70, 100, 30));
        baudRCmb->setFont(font2);
        CheckLbl = new QLabel(groupBox_SerPortSetting);
        CheckLbl->setObjectName(QStringLiteral("CheckLbl"));
        CheckLbl->setGeometry(QRect(10, 110, 53, 30));
        CheckLbl->setFont(font3);
        DPaityCmb = new QComboBox(groupBox_SerPortSetting);
        DPaityCmb->setObjectName(QStringLiteral("DPaityCmb"));
        DPaityCmb->setGeometry(QRect(70, 110, 100, 30));
        DPaityCmb->setFont(font2);
        DataLbl = new QLabel(groupBox_SerPortSetting);
        DataLbl->setObjectName(QStringLiteral("DataLbl"));
        DataLbl->setGeometry(QRect(10, 150, 53, 30));
        DataLbl->setFont(font3);
        DataBCmb = new QComboBox(groupBox_SerPortSetting);
        DataBCmb->setObjectName(QStringLiteral("DataBCmb"));
        DataBCmb->setGeometry(QRect(70, 150, 100, 30));
        DataBCmb->setFont(font2);
        StopLbl = new QLabel(groupBox_SerPortSetting);
        StopLbl->setObjectName(QStringLiteral("StopLbl"));
        StopLbl->setGeometry(QRect(10, 190, 53, 30));
        StopLbl->setFont(font3);
        StopBCmb = new QComboBox(groupBox_SerPortSetting);
        StopBCmb->setObjectName(QStringLiteral("StopBCmb"));
        StopBCmb->setGeometry(QRect(70, 190, 100, 30));
        StopBCmb->setFont(font2);
        groupBox_Recv = new QGroupBox(centralWidget);
        groupBox_Recv->setObjectName(QStringLiteral("groupBox_Recv"));
        groupBox_Recv->setGeometry(QRect(201, 11, 491, 321));
        groupBox_Recv->setFont(font);
        gridLayout_2 = new QGridLayout(groupBox_Recv);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(5);
        gridLayout_2->setContentsMargins(8, 5, 5, 5);
        RecvDataEdt = new QTextEdit(groupBox_Recv);
        RecvDataEdt->setObjectName(QStringLiteral("RecvDataEdt"));
        RecvDataEdt->setFont(font3);

        gridLayout_2->addWidget(RecvDataEdt, 0, 0, 1, 1);

        SendBtn = new QPushButton(centralWidget);
        SendBtn->setObjectName(QStringLiteral("SendBtn"));
        SendBtn->setGeometry(QRect(592, 340, 101, 101));
        SendBtn->setFont(font1);
        SendDataEdt = new QTextEdit(centralWidget);
        SendDataEdt->setObjectName(QStringLiteral("SendDataEdt"));
        SendDataEdt->setGeometry(QRect(210, 341, 381, 101));
        ReflushSerPortBtn = new QPushButton(centralWidget);
        ReflushSerPortBtn->setObjectName(QStringLiteral("ReflushSerPortBtn"));
        ReflushSerPortBtn->setGeometry(QRect(50, 350, 91, 41));
        ReflushSerPortBtn->setFont(font3);
        ClearRecvBtn = new QPushButton(centralWidget);
        ClearRecvBtn->setObjectName(QStringLiteral("ClearRecvBtn"));
        ClearRecvBtn->setGeometry(QRect(50, 400, 91, 41));
        ClearRecvBtn->setFont(font3);
        SerialPort->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SerialPort);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SerialPort->setStatusBar(statusBar);

        retranslateUi(SerialPort);

        QMetaObject::connectSlotsByName(SerialPort);
    } // setupUi

    void retranslateUi(QMainWindow *SerialPort)
    {
        SerialPort->setWindowTitle(QApplication::translate("SerialPort", "SerialPort", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("SerialPort", "Open", Q_NULLPTR));
        groupBox_SerPortSetting->setTitle(QApplication::translate("SerialPort", "\344\270\262\345\217\243\350\256\276\347\275\256", Q_NULLPTR));
        OnOffBtn->setText(QApplication::translate("SerialPort", "\346\211\223\345\274\200", Q_NULLPTR));
        FlowCtrlLbl->setText(QApplication::translate("SerialPort", "\346\265\201\346\216\247\345\210\266:", Q_NULLPTR));
        SerPortLbl->setText(QApplication::translate("SerialPort", "\344\270\262\345\217\243\345\217\267:", Q_NULLPTR));
        BoaudLbl->setText(QApplication::translate("SerialPort", "\346\263\242\347\211\271\347\216\207:", Q_NULLPTR));
        CheckLbl->setText(QApplication::translate("SerialPort", "\346\240\241\351\252\214\344\275\215:", Q_NULLPTR));
        DataLbl->setText(QApplication::translate("SerialPort", "\346\225\260\346\215\256\344\275\215:", Q_NULLPTR));
        StopLbl->setText(QApplication::translate("SerialPort", "\345\201\234\346\255\242\344\275\215:", Q_NULLPTR));
        groupBox_Recv->setTitle(QApplication::translate("SerialPort", "\344\270\262\345\217\243\346\225\260\346\215\256\346\216\245\346\224\266", Q_NULLPTR));
        SendBtn->setText(QApplication::translate("SerialPort", "\345\217\221\351\200\201", Q_NULLPTR));
        ReflushSerPortBtn->setText(QApplication::translate("SerialPort", "\345\210\267\346\226\260\344\270\262\345\217\243", Q_NULLPTR));
        ClearRecvBtn->setText(QApplication::translate("SerialPort", "\346\270\205\347\251\272\346\216\245\346\224\266\345\214\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SerialPort: public Ui_SerialPort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALPORT_H
