#include "net_util_thread.h"
#include <QtDebug>
#include "net_common.h"
#include <arpa/inet.h>

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
static void on_handle_pkt(uint8_t *args, const struct pcap_pkthdr *ph,
                          const uint8_t *packet)
{
    printf("Capture: %u, len: %u\n", ph->caplen, ph->len);
    const struct sniff_ethernet *ethernet; /* 以太网帧头部*/
    const struct sniff_ip *ip;             /* IP包头部 */
    const struct sniff_udp *udp;           /* UDP包头部 */
    const struct sniff_dhcp *dhcp;         /* DHCP除去常规字段*/
    int size_ethernet = sizeof(struct sniff_ethernet);
    int size_ip = sizeof(struct sniff_ip);
    int size_udp = sizeof(struct sniff_udp);
    int size_dhcp = sizeof(struct sniff_dhcp);

    ethernet = (sniff_ethernet *)packet;
    ip = (struct sniff_ip *)(packet + size_ethernet);

    dhcp_info dhinfo;
    sprintf(dhinfo.macaddr, "%02X:%02X:%02X:%02X:%02X:%02X",
            ethernet->ether_shost[0], ethernet->ether_shost[1],
            ethernet->ether_shost[2], ethernet->ether_shost[3],
            ethernet->ether_shost[4], ethernet->ether_shost[5]);
    ;
    printf("%s : %s\n", inet_ntoa(ip->ip_src), inet_ntoa(ip->ip_dst));
    qInfo() << dhinfo.macaddr;
}
NetUtilThread::NetUtilThread() {}

void NetUtilThread::setPcap(pcap_t *_pcap) { m_pcap = _pcap; }

void NetUtilThread::run()
{
    if (nullptr != m_pcap) {
        pcap_loop(m_pcap, 0, on_handle_pkt, nullptr);
    }
}
