#ifndef NET_UTIL_THREAD_H
#define NET_UTIL_THREAD_H

#include <QThread>
#include "pcap.h"
class NetUtilThread : public QThread {
   public:
    NetUtilThread();
    pcap_t *m_pcap;
    void setPcap(pcap_t *_pcap);
    // QThread interface
   protected:
    void run();
};

#endif  // NET_UTIL_THREAD_H
