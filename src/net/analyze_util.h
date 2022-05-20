#ifndef ANALYZE_UTIL_H
#define ANALYZE_UTIL_H

#include <QObject>
#include <pcap.h>
#include <QList>
struct NetInfo{
    int start_index;
    int current_index;
    int end_time;
    QList<int> indexList;
};
class AnalyzeUtil : public QObject {
    Q_OBJECT
   public:
    explicit AnalyzeUtil(QObject *parent = nullptr);
    /**
     * @brief AanlyzeTcp 分析Tcp协议
     * @param args
     * @param ph
     * @param packet    数据包内容
     * @return
     */
    int AanlyzeTcp(uint8_t *args, const struct pcap_pkthdr *ph,
                   const uint8_t *packet);
    QList<NetInfo> m_index;
   signals:

   public slots:
};

#endif  // ANALYZE_UTIL_H
