#include "select_net_dev_dialog.h"
#include <QFileDialog>
#include "../net/net_util.h"
#include <QtDebug>
SelectNetDevDialog::SelectNetDevDialog(QWidget *parent)
    : QDialog(parent)
    , m_ptrLabSelectDevName(new QLabel(tr("please select device:")))
    , m_ptrBtnRejected(new QPushButton(tr("cansl"), this))
    , m_ptrBtnAccepted(new QPushButton(tr("ok"), this))
    , m_ptrLayoutMain(new QGridLayout)
    , m_ptrCmbSelectDevName(new QComboBox(this))
{
    initUI();
    initConnect();
}

void SelectNetDevDialog::initUI()
{
    setWindowTitle(tr("select device dialog"));
    setMinimumWidth(500);
    m_ptrLayoutMain->addWidget(m_ptrLabSelectDevName, 0, 0);
    m_ptrLayoutMain->addWidget(m_ptrCmbSelectDevName, 0, 1);
    m_ptrLayoutMain->addWidget(m_ptrBtnRejected, 1, 0);
    m_ptrLayoutMain->addWidget(m_ptrBtnAccepted, 1, 1);
    NetUtil netUtil;
    QStringList list = netUtil.NetDevNameList();
    m_ptrCmbSelectDevName->addItems(list);
    m_strDevName = m_ptrCmbSelectDevName->currentText();
    setLayout(m_ptrLayoutMain);
}

void SelectNetDevDialog::initConnect()
{
    QObject::connect(m_ptrBtnAccepted, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(m_ptrBtnRejected, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(m_ptrCmbSelectDevName,
                     SIGNAL(currentIndexChanged(QString)), this,
                     SLOT(currentIndexChanged(QString)));
}

QString SelectNetDevDialog::getSelectDevName()
{
    SelectNetDevDialog dlg;
    if (dlg.exec() == QDialog::Accepted) {
        return dlg.getDevName();
    }
    return "";
}

QString SelectNetDevDialog::getDevName() { return m_strDevName; }

void SelectNetDevDialog::accept()
{
    QDialog::accept();
    return;
}

void SelectNetDevDialog::reject()
{
    QDialog::reject();
    return;
}

void SelectNetDevDialog::currentIndexChanged(QString strDevName)
{
    m_strDevName = strDevName;
    qInfo() << "m_strDevName:" << m_strDevName;
}
