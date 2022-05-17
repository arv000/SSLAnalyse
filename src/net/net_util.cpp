#include "net_util.h"
#include "pcap.h"
#include <QtDebug>
NetUtil::NetUtil(QObject *parent)
    : QObject(parent)
    , m_bStatus(true)
{
}

int NetUtil::StartCaptureData()
{
    QString strDevName;
    StartCaptureData(strDevName);
    return 0;
}

int NetUtil::StopCaptureData()
{
    QString strDevName;
    StopCaptureData(strDevName);
    return 0;
}

int NetUtil::StartCaptureData(QString strDevName)
{
    if(strDevName.isNull() || strDevName.isEmpty()){
        qWarning()<<"为选中网卡";
        return -1;
    }

    if (m_bStatus) {
        m_bStatus = false;
    }
    return 0;
}

int NetUtil::StopCaptureData(QString strDevName)
{
    if (m_bStatus) {
        m_bStatus = true;
    }
    return 0;
}

QStringList NetUtil::NetDevNameList()
{
    QStringList strListRes;
    pcap_if_t *alldevs;
    pcap_if_t *d;

    char errbuf[PCAP_ERRBUF_SIZE];

    /* 获取本地机器设备列表 */
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        qWarning() << "Error in pcap_findalldevs_ex: " << errbuf;
        return strListRes;
    }
    /* 打印列表 */
    for (d = alldevs; d != nullptr; d = d->next) {
        if (nullptr != d->addresses) {
            QString strDevName = QString(d->name);
            strListRes.append(strDevName);
        }
    } /* 不再需要设备列表了，释放它 */

    pcap_freealldevs(alldevs);
    qInfo() << "DevNamelist : " << strListRes;
    return strListRes;
}
