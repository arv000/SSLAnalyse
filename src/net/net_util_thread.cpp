#include "net_util_thread.h"
#include <QtDebug>
#include "net_common.h"
#include <arpa/inet.h>
#include "tool/log_tools.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "analyze_http_util.h"
static void on_handle_pkt(uint8_t *args, const struct pcap_pkthdr *ph,
                          const uint8_t *packet)
{
    const struct sniff_ethernet *ethernet; /* 以太网帧头部*/

    const struct sniff_ip *ip;             /* IP包头部 */
    const struct sniff_tcp *tcp;           /* UDP包头部 */
    int size_ethernet = sizeof(struct sniff_ethernet);
    int size_ip = sizeof(struct sniff_ip);
    int size_tcp = sizeof(struct sniff_tcp);
    //  int size_dhcp = sizeof(struct sniff_dhcp);

    ethernet = (struct sniff_ethernet *)packet;
    ip = (struct sniff_ip *)(packet + size_ethernet);
    tcp = (struct sniff_tcp *)(packet + size_ethernet + size_ip);

    dhcp_info dhinfo;
    sprintf(dhinfo.macaddr, "%02X:%02X:%02X:%02X:%02X:%02X",
            ethernet->ether_shost[0], ethernet->ether_shost[1],
            ethernet->ether_shost[2], ethernet->ether_shost[3],
            ethernet->ether_shost[4], ethernet->ether_shost[5]);

    if(!( htons( tcp->th_dport) == 8888 || htons( tcp->th_sport) == 8888)) return ;
    qInfo()<<"-------------- start -------------------------";
   // LogTools()<< ip;
   // LogTools() << tcp;

    const u_char *tcp_payload;
    int payload_len = 0; // tcp 数据包长度
    tcp_payload = (u_char *)(packet + size_ethernet + size_ip + size_tcp);
    AnalyzeHttpUtil a;
    int offset = size_ethernet + size_ip +size_tcp;

    payload_len  = int( ph->len) - offset;

    int s= a.parseHttpHead(tcp_payload, payload_len);

}
NetUtilThread::NetUtilThread() {}

void NetUtilThread::setPcap(pcap_t *_pcap) { m_pcap = _pcap; }

void NetUtilThread::run()
{
    if (nullptr != m_pcap) {
        pcap_loop(m_pcap, 0, on_handle_pkt, nullptr);
    }
}
