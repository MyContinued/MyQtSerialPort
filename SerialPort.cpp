/* 串口编程四步走：
* 1.设置串口参数
* 2.打开串口
* 3.读/写串口
* 4.关闭串口
* By WSG 2018/07/22
*/

#include "SerialPort.h"
#include "ui_SerialPort.h"

#include <QSettings>
#include <qt_windows.h>
#include <QMessageBox>
#include <QDebug>

SerialPort::SerialPort(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SerialPort)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("串口调试助手 Qt版 V1.0"));
    this->setFixedSize(this->width(), this->height());

    m_nRecvNum = 0;
    m_nSendNum = 0;
    m_bOpen = false;

    InitStatusBar();
    InitCommCmb();

    ui->OnOffBtn->setIcon(QIcon(":/pic/res/OFF.png"));
    ui->RecvDataEdt->setReadOnly(true);

    m_serial = new QSerialPort;
    connect(m_serial, SIGNAL(readyRead()), this, SLOT(slot_RecvPortData()));
    m_nReadBuffSize = 64;

}

SerialPort::~SerialPort()
{
    delete ui;
    delete m_SerStateLbl;
    delete m_RecvNumLbl;
    delete m_SendNumLbl;
    delete m_ResetNumBtn;
}

/***************************************************************************/
/*                              初始化状态栏                                 */
/***************************************************************************/

void SerialPort::InitStatusBar()
{
    m_SerStateLbl = new QLabel();
    m_RecvNumLbl = new QLabel();
    m_SendNumLbl = new QLabel();
    m_ResetNumBtn = new QPushButton();
    connect(m_ResetNumBtn, SIGNAL(clicked()), this, SLOT(slot_ResetNumBtn_clicked()));

    m_SerStateLbl->setMinimumSize(180, 20);
    m_RecvNumLbl->setMinimumSize(180, 20); // 标签最小尺寸
    m_SendNumLbl->setMinimumSize(180, 20);

    ui->statusBar->addWidget(m_SerStateLbl);
    ui->statusBar->addWidget(m_RecvNumLbl);
    ui->statusBar->addWidget(m_SendNumLbl);
    ui->statusBar->addWidget(m_ResetNumBtn);

    SetSerState();
    SetRecvNum();
    SetSendNum();
    m_ResetNumBtn->setText(tr("复位计数"));
}

void SerialPort::SetSerState()
{
    QString strState;
    if ( m_bOpen )
        strState = tr("打开");
    else
        strState = tr("关闭");

    m_SerStateLbl->setText(tr("串口状态：%1").arg(strState));
}

void SerialPort::SetRecvNum()
{
    QString strRecvNum = QString::number(m_nRecvNum);
    m_RecvNumLbl->setText(tr("接收字节数：%1").arg(strRecvNum));
}

void SerialPort::SetSendNum()
{
    QString strSendNum = QString::number(m_nSendNum);
    m_SendNumLbl->setText(tr("发送字节数：%1").arg(strSendNum));
}

/***************************************************************************/
/*                            初始化CombBox                                 */
/***************************************************************************/

void SerialPort::InitCommCmb()
{
    SetPortNumCmb();    // 串口号
    SetBaudCmb();       // 波特率
    SetDPaityCmb();     // 校验位
    SetDataBCmb();      // 数据位
    SetStopBCmb();      // 停止位
    SetStreamCmb();     // 流控制
}

// 设置串口号
void SerialPort::SetPortNumCmb()
{
    QStringList commPortList = GetEnableCommPortQt();
    if ( !commPortList.isEmpty() )
        ui->PortNumCmb->addItems(commPortList);
}

// 获取计算机可用串口 QSerialPort QSerialPortInfo类
QStringList SerialPort::GetEnableCommPortQt()
{
    QStringList CommPortList;

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            CommPortList.append(serial.portName());
            serial.close();
        }
    }

    return CommPortList;
}

// 获取计算机可用串口 Windows API
QStringList SerialPort::GetEnableCommPortWin()
{
    QStringList CommPortList;

    QString strCommPath = tr("HKEY_LOCAL_MACHINE\\HARDWARE\\DEVICEMAP\\SERIALCOMM");
    QSettings *settings = new QSettings(strCommPath, QSettings::NativeFormat);
    QStringList keyList = settings->allKeys();

    if ( !keyList.isEmpty() )
    {
        for (int i = 0; i < keyList.count(); i++)
            CommPortList.append(GetComm(i));
    }

    return CommPortList;
}

// nIndex为索引号 bValue选择返回值为key还是value，默认为value
QString SerialPort::GetComm(int nIndex, bool bValue)
{
    QString strCommRet = tr("");
    HKEY hKey;

    // RegOpenKeyEx windowsApi 成功返回0 需要加<qt_windows.h>头文件
    if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_READ, &hKey) != 0)
    {
        QMessageBox::warning(this, tr("注册表"), tr("无法打开注册表！"), QMessageBox::Ok);
        return tr(""); // 无法打开注册表
    }

    QString strKeyMsg;      // 键名
    QString strValueMsg;    // 键值
    wchar_t keyName[256];   // 键名数组
    char keyValue[256];     // 键值数组

    ulong nKeySize = sizeof(keyName);
    ulong nValueSize = sizeof(keyValue);
    ulong nType;

    if (::RegEnumValue(hKey, nIndex, keyName, &nKeySize, 0, &nType, (BYTE*)keyValue, &nValueSize) == 0) // 列举键名
    {
        // 读取键名
        for (uint i = 0; i < nKeySize; i++)
        {
            if (keyName[i] != 0x00)
                strKeyMsg.append(keyName[i]);
        }

        // 读取键值
        for (uint j = 0; j < nValueSize; j++)
        {
            if (keyValue[j] != 0x00)
                strValueMsg.append(keyValue[j]);
        }

        if ( bValue )
            strCommRet = strValueMsg;
        else
            strCommRet = strKeyMsg;
    }//if
    else
    {
        ::RegCloseKey(hKey); // 关闭注册表
        return tr("");  // 无可用串口
    }

    return strCommRet;
}

 // 设置波特率
void SerialPort::SetBaudCmb()
{
    QStringList baudRList;
    baudRList.append(tr("110"));
    baudRList.append(tr("300"));
    baudRList.append(tr("600"));
    baudRList.append(tr("1200"));
    baudRList.append(tr("2400"));
    baudRList.append(tr("4800"));
    baudRList.append(tr("9600"));
    baudRList.append(tr("14400"));
    baudRList.append(tr("19200"));
    baudRList.append(tr("38400"));
    baudRList.append(tr("56000"));
    baudRList.append(tr("57600"));
    baudRList.append(tr("115200"));
    baudRList.append(tr("128000"));
    baudRList.append(tr("256000"));
    baudRList.append(tr("自定义"));

    ui->baudRCmb->addItems(baudRList);
    ui->baudRCmb->setCurrentIndex(6);
}

// 设置校验位
void SerialPort::SetDPaityCmb()
{
    QStringList DPaityList;
    DPaityList.append(tr("NONE"));
    DPaityList.append(tr("ODD"));
    DPaityList.append(tr("EVEN"));
    DPaityList.append(tr("MARK"));
    DPaityList.append(tr("SPACE"));

    ui->DPaityCmb->addItems(DPaityList);
}

 // 设置数据位
void SerialPort::SetDataBCmb()
{
    for (int i = 5; i <= 8; i++)
    {
        QString strDataB = QString::number(i);
        ui->DataBCmb->addItem(strDataB);
    }
    ui->DataBCmb->setCurrentIndex(3);
}

// 设置停止位
void SerialPort::SetStopBCmb()
{
    ui->StopBCmb->addItem(tr("1"));
    ui->StopBCmb->addItem(tr("1.5"));
    ui->StopBCmb->addItem(tr("2"));
}

// 流控制
void SerialPort::SetStreamCmb()
{
    ui->FlowCtrlCmb->addItem(tr("NO"));
    ui->FlowCtrlCmb->addItem(tr("RTS/CTS"));
    ui->FlowCtrlCmb->addItem(tr("XON/XOFF"));
}

/***************************************************************************/
/*                                 槽函数                                   */
/***************************************************************************/
// 波特率自定义
void SerialPort::on_baudRCmb_currentIndexChanged(int index)
{
    uint nCount = ui->baudRCmb->count();
    if ((unsigned)index == nCount - 1)
    {
        ui->baudRCmb->setEditable(TRUE);
        ui->baudRCmb->setItemText(index, tr(""));
    }
    else
    {
        ui->baudRCmb->setEditable(FALSE);
        ui->baudRCmb->setItemText(nCount-1, tr("自定义"));
    }
}

// 刷新串口
void SerialPort::on_ReflushSerPortBtn_clicked()
{
    ui->PortNumCmb->clear();
    SetPortNumCmb();
}

// 复位计数
void SerialPort::slot_ResetNumBtn_clicked()
{
    m_nSendNum = 0;
    m_nRecvNum = 0;
    SetSendNum();
    SetRecvNum();
}

// 清空接受区
void SerialPort::on_ClearRecvBtn_clicked()
{
    ui->RecvDataEdt->setText(tr(""));
}

/***************************************************************************/
/*                             串口通信                                     */
/***************************************************************************/
// 打开/关闭串口
void SerialPort::on_OnOffBtn_clicked()
{
    if (m_serial->isOpen()) // 已经处于打开状态，则关闭串口
    {
        m_serial->close();
        ui->OnOffBtn->setText(tr("打开"));
        ui->OnOffBtn->setIcon(QIcon(":/pic/res/OFF.png"));
        m_bOpen = false;
        SetSerState();
    }
    else // 串口处于关闭状态，打开串口
    {
        if ( !SetSerialPortParam(m_serial) )
        {
            QMessageBox::critical(this, tr("Error"), tr("串口错误！"), QMessageBox::Ok);
            return;
        }

        // 打开串口
        if ( !m_serial->open(QIODevice::ReadWrite) ) // 打开失败
        {
            QMessageBox::critical(this, tr("Error"), tr("串口不存在或者被其它程序占用！"), QMessageBox::Ok);
            // QString strRecv = ui->RecvDataEdt->toPlainText();
            // strRecv += tr("\n【Error】Can't Open COM Port!");
            ui->RecvDataEdt->append(tr("\n【Error】Can't Open COM Port!"));
            return;
        }

        // 设置串口缓冲区大小
        m_serial->setReadBufferSize(m_nReadBuffSize);

        ui->OnOffBtn->setText(tr("断开"));
        ui->OnOffBtn->setIcon(QIcon(":/pic/res/ON.png"));
        m_bOpen = true;
        SetSerState();
    }
}

// 设置串口参数，失败返回false，成功返回true
bool SerialPort::SetSerialPortParam(QSerialPort *serial)
{
    // 设置串口号
    QString strPortNum = ui->PortNumCmb->currentText();
    if (strPortNum == tr(""))
        return false;
    serial->setPortName(strPortNum);

    // 设置波特率
    qint32 nBaudRate = ui->baudRCmb->currentText().toInt();
    serial->setBaudRate(nBaudRate);

    // 设置奇偶校验
    int nParityType = ui->DPaityCmb->currentIndex();
    switch (nParityType)
    {
    case 0:
        serial->setParity(QSerialPort::NoParity);
        break;
    case 1:
        serial->setParity(QSerialPort::OddParity);
        break;
    case 2:
        serial->setParity(QSerialPort::EvenParity);
        break;
    case 3:
        serial->setParity(QSerialPort::MarkParity);
        break;
    case 4:
        serial->setParity(QSerialPort::SpaceParity);
        break;
    default:
        serial->setParity(QSerialPort::UnknownParity);
        break;
    }

    // 设置数据位
    int nDataBits = ui->DataBCmb->currentIndex();
    switch (nDataBits)
    {
    case 0:
        serial->setDataBits(QSerialPort::Data5);
        break;
    case 1:
        serial->setDataBits(QSerialPort::Data6);
        break;
    case 2:
        serial->setDataBits(QSerialPort::Data7);
        break;
    case 3:
        serial->setDataBits(QSerialPort::Data8);
        break;
    default:
        serial->setDataBits(QSerialPort::UnknownDataBits);
        break;
    }

    // 设置停止位
    int nStopBits = ui->StopBCmb->currentIndex();
    switch (nStopBits)
    {
    case 0:
        serial->setStopBits(QSerialPort::OneStop);
        break;
    case 1:
        serial->setStopBits(QSerialPort::OneAndHalfStop);
        break;
    case 2:
        serial->setStopBits(QSerialPort::TwoStop);
        break;
    default:
        serial->setStopBits(QSerialPort::UnknownStopBits);
        break;
    }

    // 流控制
    int nFlowCtrl = ui->FlowCtrlCmb->currentIndex();
    switch (nFlowCtrl)
    {
    case 0:
        serial->setFlowControl(QSerialPort::NoFlowControl);
        break;
    case 1:
        serial->setFlowControl(QSerialPort::HardwareControl);
        break;
    case 2:
        serial->setFlowControl(QSerialPort::SoftwareControl);
        break;
    default:
        serial->setFlowControl(QSerialPort::UnknownFlowControl);
        break;
    }

    return true;
}

// 槽函数，接收串口数据
void SerialPort::slot_RecvPortData()
{
    QByteArray bytes = m_serial->readAll();
    if ( !bytes.isEmpty() )
    {
        QString strRecv = QString::fromLocal8Bit(bytes);
        ui->RecvDataEdt->append(strRecv);

        m_nRecvNum += bytes.count();
        SetRecvNum();
    }
    else
        ui->RecvDataEdt->setText(tr("接收数据出错！"));
}

// 发送数据，写串口
void SerialPort::on_SendBtn_clicked()
{
    // 串口未打开
    if ( !m_bOpen )
    {
        QMessageBox::warning(this, tr("Error"), tr("串口未打开，发送失败！"), QMessageBox::Ok);
        return;
    }

    QByteArray SendBytes = ui->SendDataEdt->toPlainText().toLocal8Bit();
    if ( !SendBytes.isEmpty() )
    {
        m_serial->write(SendBytes);
        m_nSendNum += SendBytes.count();
        SetSendNum();
    }
}

/***************************************************************************/
/*                                函数重写                                  */
/***************************************************************************/
// 串口关闭事件，如果窗口关闭前串口未关闭，则关闭串口
void SerialPort::closeEvent(QCloseEvent *event)
{
    if (m_serial->isOpen())
        m_serial->close();

    event->accept();
}




