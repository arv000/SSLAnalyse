#include "analyze_http_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "net_common.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
AnalyzeHttpUtil::AnalyzeHttpUtil(QObject *parent)
    : QObject(parent)
{
}

int AnalyzeHttpUtil::parseHttpHead(const u_char *payload,
                                   const unsigned int payload_len)
{
    if (payload_len <= 0) {
        return -1;
    }

    for (unsigned int a = 0, b = 0; a < payload_len - 1; a++) {
        unsigned int line_len = 0;

        u_char tmp[4] = {0};

        if (a + 4 > payload_len - 1) {
            continue;
        }
        memcpy(tmp, payload + a, 4);
        if (int(tmp[0]) == 0x0d && tmp[1] == 0x0a && tmp[2] == 0x0d &&
            tmp[3] == 0x0a) {
            break;
        }

        //        // 0x0d0a 表示\r\n
        if (get_u_int16_t(payload, a) == ntohs(0x0d0a)) {
            line_len = a - b;
            char value[MAX_HOST_LEN] = {0};
            if (line_len > 0) {
                memcpy(value, payload + b, static_cast<u_long>(line_len));
                qInfo() << value;
            }

            b = a + 2;
        }
    }
    return 0;
}
