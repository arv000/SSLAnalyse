#include "net_util.h"
#include "pcap.h"
#include <QtDebug>
NetUtil::NetUtil(QObject *parent)
    : QObject(parent)
    , m_bStatus(true)
{
}

void NetUtil::StartCaptureData() {}

void NetUtil::StopCaptureData() {}

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
