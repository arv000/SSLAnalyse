#include "net_util_thread.h"
#include "analyze_util.h"
 AnalyzeUtil a;
static void on_handle_pkt(uint8_t *args, const struct pcap_pkthdr *ph,
                          const uint8_t *packet)
{
    a.AanlyzeTcp(args, ph, packet);
}
NetUtilThread::NetUtilThread() {}

void NetUtilThread::setPcap(pcap_t *_pcap) { m_pcap = _pcap; }

void NetUtilThread::run()
{
    if (nullptr != m_pcap) {
        pcap_loop(m_pcap, 0, on_handle_pkt, nullptr);
    }
}
