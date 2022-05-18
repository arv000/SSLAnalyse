#ifndef NET_COMMON_H
#define NET_COMMON_H
#include "pcap.h"
#define ETHER_ADDR_LEN 6
struct sniff_ethernet {
    u_char ether_dhost[ETHER_ADDR_LEN]; /* ⽬的主机的地址         | 6 */
    u_char ether_shost[ETHER_ADDR_LEN]; /* 源主机的地址           | 6 */
    u_short ether_type;                 /* IP? ARP? RARP? etc   | 2 */
};
struct sniff_ip {
    u_char ip_vhl;  /* 前4位版本,后四位首部长度   | 1 */
    u_char ip_tos;  /* 服务类型(TOS)            | 1 */
    u_short ip_len; /* 总长度(字节数)            | 2 */
    u_short ip_id;  /* 标识                     | 2 */
    u_short ip_off; /* 前3位标志,后13位偏移       | 2 */
#define IP_RF 0x8000
#define IP_DF 0x4000
#define IP_MF 0x2000
#define IP_OFFMASK 0x1fff
    u_char ip_ttl;         /* 生成时间(TTL)     | 1 */
    u_char ip_p;           /* 协议             | 1 */
    u_short ip_sum;        /* 16位首部校验      | 2 */
    struct in_addr ip_src; /* 32位源ip地址      | 4 */
    struct in_addr ip_dst; /* 32位目的IP地址    | 4  */
};

typedef u_int tcp_seq;
struct sniff_tcp {
    u_short th_sport;  //源端口号 16 bit
    u_short th_dport;  //目的端口号 16 bit
    tcp_seq th_seq;    //序列号 32 bit
    tcp_seq th_ack;    //确认号 32 bit

    //    u_char th_offx2;  //前4位：TCP 头长度；中6位：保留；后6位：标志位
    //    u_char th_flags;
    u_short
        m_sHeaderLenAndFlag;  //前4位：TCP 头长度；中6位：保留；后6位：标志位
    u_short th_win;  //窗口大小 16 bit
    u_short th_sum;  //校验和 16 bit
    u_short th_urp;  //紧急数据偏移量 16 bit
};

struct sniff_udp {
    u_short udp_sport;
    u_short udp_dport;
    u_short udp_len;
    u_short udp_sum;
};

struct sniff_dhcp {
    u_char op;
    u_char htype;
    u_char hlen;
    u_char hops;
    u_int xid;
    u_short secs;
    u_short flags;
    u_int ciaddr;
    u_int yiaddr;
    u_int siaddr;
    u_int giaddr;
    u_char cmacddr[6];
    u_char chwaddrpad[10];
    u_char sname[64];
    u_char filename[128];
    u_int cookie;
};

struct dhcp_info {
    char macaddr[32];
    char ip[32];
    char hostname[128];
    char vendor[64];
};
#endif  // NET_COMMON_H
