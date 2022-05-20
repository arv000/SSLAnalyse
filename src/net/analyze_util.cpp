#include "analyze_util.h"
#include <QtDebug>
#include "net_common.h"
#include <arpa/inet.h>
#include "tool/log_tools.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "analyze_http_util.h"
AnalyzeUtil::AnalyzeUtil(QObject *parent)
    : QObject(parent)
{
}

int AnalyzeUtil::AanlyzeTcp(uint8_t *args, const pcap_pkthdr *ph,
                            const uint8_t *packet)
{
    const struct sniff_ethernet *ethernet; /* 以太网帧头部*/
    const struct sniff_ip *ip;             /* IP包头部 */
    const struct sniff_tcp *tcp;           /* TCP包头部 */


    int size_ethernet = sizeof(struct sniff_ethernet);
    int size_ip = sizeof(struct sniff_ip);
    int size_tcp = sizeof(struct sniff_tcp);
    //  int size_dhcp = sizeof(struct sniff_dhcp);

    ethernet = (struct sniff_ethernet *)packet;
    ip = (struct sniff_ip *)(packet + size_ethernet);
    tcp = (struct sniff_tcp *)(packet + size_ethernet + size_ip);
    qInfo()<<"index:"<<htons(ip->ip_id)<<",flags"<<tcp->th_flags<<",";
    if (!(htons(tcp->th_dport) == 8888 || htons(tcp->th_sport) == 8888)) {
        return -1;
    }
    // 关于syn ack分析
    NetInfo info;
    int len = m_index.length();
    if(tcp->th_flags == NET_FLAGS_SYN){
        info.start_index = htons(ip->ip_id);
        info.current_index = htons(ip->ip_id) +1;
        info.indexList.append(htons(ip->ip_id));
        m_index.append(info);
    }else if(tcp->th_flags == NET_FLAGS_SYN_FIN){
        for(int i = 0 ; i <len;i++){
            qInfo()<< "m_index[i].current_index :"<<m_index[i].current_index <<",htons(ip->ip_id):"<<htons(ip->ip_id);
            if(m_index[i].current_index == htons(ip->ip_id)){
                QList<int>l = m_index[i].indexList;
                foreach(auto item ,l){
                      qInfo()<<"NET_FLAGS_SYN_FIN:"<<item;
                }
                 qInfo()<<"------------------finish-----------";
               break;
            }
        }
    }
    else{
        for(int i = 0 ; i <len;i++){
            if(m_index[i].current_index == htons(ip->ip_id)){
                ++m_index[i].current_index;
                m_index[i].indexList.append(htons(ip->ip_id));
                break;
            }
        }
    }
//    if(htons(ip->ip_len) < 100){
//        switch (tcp->th_flags) {
//         case NET_FLAGS_SYN:
//             qInfo() << "Syn" << (tcp->th_len >> 2)<< ":"<< tcp->th_len<<",index:"<<htons(ip->ip_id) ;

//            break;
//        case NET_FLAGS_SYN_ACK:
//              qInfo() << "Syn Ack";

//           break;
//        case NET_FLAGS_ACK:
//             qInfo() << "Ack";

//           break;
//        case NET_FLAGS_PSH_ACK:
//            qInfo() << "Syn NET_FLAGS_PSH_ACK:"<<NET_FLAGS_PSH_ACK<<" , temp:"  << htons(ip->ip_id);

//           break;
//        case NET_FLAGS_SYN_FIN:
//              qInfo() << "Syn AFIN";

//           break;
//        }
//    }


    qInfo() << "-------------- start -------------------------";
    // LogTools()<< ip;
    // LogTools() << tcp;

    const u_char *tcp_payload;
    int payload_len = 0;  // tcp 数据包长度
    tcp_payload = (u_char *)(packet + size_ethernet + size_ip + (tcp->th_len >> 2));
    AnalyzeHttpUtil a;
    int offset = size_ethernet + size_ip + (tcp->th_len >> 2);

    payload_len = int(ph->len) - offset;

    int s = a.parseHttpHead(tcp_payload, payload_len);

    return 0;
}
