#include "net_util.h"

#define CAP_LEN 2048

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
    if (_pcap) {
        (void)pcap_close(_pcap);
        _pcap = nullptr;
    }
    return 0;
}

int NetUtil::StartCaptureData(QString strDevName)
{
    if (strDevName.isNull() || strDevName.isEmpty()) {
        qWarning() << "为选中网卡";
        return -1;
    }
    if (m_bStatus) {
        m_bStatus = false;
    }

    int dev_flag = 1;
    int cap_len = CAP_LEN;
    char ebuf[PCAP_ERRBUF_SIZE];


    int ret = 0;
    // 打开设备准备开始监听程序,需要使用root权限
    _pcap = pcap_open_live(strDevName.toStdString().c_str(), cap_len, dev_flag,
                           1000, ebuf);

    if (!_pcap) {
        qWarning() << "pcap_open_live:" << strDevName << "," << ebuf;
        return -1;
    }

    ret = pcap_compile(_pcap, &filter, "tcp", 0, mask);
    if (-1 == ret) {
        qWarning() << "pcap_compile failed:" << strDevName << "," << ebuf;
        return -2;
    }
    ret = pcap_setfilter(_pcap, &filter);
    if (-1 == ret) {
        qWarning() << "pcap_setfilter failed:" << strDevName << "," << ebuf;
        return -3;
    }
    thread.setPcap(_pcap);
    thread.start();
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
