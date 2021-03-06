#include "mainwindow.h"
#include <QToolBar>
#include "net/net_util.h"
#include "ui/select_net_dev_dialog.h"
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ptrToolBar(new QToolBar(tr("toolBar")))
    , m_ptrNetUtil(new NetUtil(this))
{
    initUI();
    initConnect();
}

MainWindow::~MainWindow() {}

void MainWindow::initUI()
{
    initUIMenuBar();
    initUIToolBar();
}

void MainWindow::initUIMenuBar() {}

void MainWindow::initUIToolBar()
{
    m_ptrActionToolBarStart = m_ptrToolBar->addAction(tr("start"));
    m_ptrActionToolBarStop = m_ptrToolBar->addAction(tr("stop"));
    m_ptrActionToolBarStart->setEnabled(true);
    m_ptrActionToolBarStop->setEnabled(false);
    this->addToolBar(m_ptrToolBar);
}

void MainWindow::initConnect()
{
    if (nullptr != m_ptrActionToolBarStart) {
        connect(m_ptrActionToolBarStart, SIGNAL(triggered()), this,
                SLOT(slotStartCaptureData()));
    }
    if (nullptr != m_ptrActionToolBarStop) {
        connect(m_ptrActionToolBarStop, SIGNAL(triggered()), this,
                SLOT(slotStopCapture()));
    }
}

void MainWindow::slotStartCaptureData()
{
    // 获取用户选择的列表。
    QString s = SelectNetDevDialog::getSelectDevName();

    m_ptrActionToolBarStart->setEnabled(false);
    m_ptrActionToolBarStop->setEnabled(true);
    // 开始抓取数据。
    if (nullptr != m_ptrNetUtil) {
        m_ptrNetUtil->StartCaptureData(s);
    }
}

void MainWindow::slotStopCapture()
{
    m_ptrActionToolBarStart->setEnabled(true);
    m_ptrActionToolBarStop->setEnabled(false);
    if (nullptr != m_ptrNetUtil) {
        m_ptrNetUtil->StopCaptureData();
    }
}
