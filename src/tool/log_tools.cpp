#include "log_tools.h"

LogTools::LogTools(QObject *parent)
    : QObject(parent)
{
}

void LogTools::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    fprintf(stderr, "Debug: [%30.30s:%u\t%40.40s ]:  %s\n",
         context.file, context.line, context.function, localMsg.constData());
    return ;
        switch (type) {
            case QtDebugMsg:
                  fprintf(stderr, "Debug: [%20.20s:%u\t%35.35s ]:  %s\n",
                        context.file, context.line, context.function, localMsg.constData());
                break;
            case QtInfoMsg:
                   fprintf(stderr, "Debug: [%20.20s:%u\t%35.35s ]:  %s\n",
                        context.file, context.line, context.function, localMsg.constData());
                break;
            case QtWarningMsg:
                   fprintf(stderr, "Debug: [%20.20s:%u\t%35.35s ]:  %s\n",
                        context.file, context.line, context.function, localMsg.constData());
                break;
            case QtCriticalMsg:
                    fprintf(stderr, "Debug: [%20.20s:%u\t%35.35s ]:  %s\n",
                        context.file, context.line, context.function, localMsg.constData());
                break;
            case QtFatalMsg:
                   fprintf(stderr, "Debug: [%20.20s:%u\t%35.35s ]:  %s\n",
                        context.file, context.line, context.function, localMsg.constData());
                break;
        }
}

void LogTools::operator<<(const sniff_tcp *tcp)
{
    QString strLog = "";
    strLog.append("th_sport:");
    strLog.append(QString::number(htons(tcp->th_sport)));
    strLog.append(",th_dport:");
    strLog.append(QString::number(htons(tcp->th_dport)));
    strLog.append(",th_seq:");
    strLog.append(QString ::number(htonl(tcp->th_seq)));
    strLog.append(",th_seq:");
    strLog.append(QString ::number(htonl(tcp->th_ack)));
    strLog.append(",th_win:");
    strLog.append(QString ::number(htons(tcp->th_win)));
    qInfo() << strLog;

}

void LogTools::operator<<(const sniff_ip *ip)
{
    QString strLog = "";
    strLog.append("ip_vhl:");
    strLog.append(QString::number(int(ip->ip_vhl)));
    strLog.append(",ip_tos:");
    strLog.append(QString::number(int(ip->ip_tos)));
    strLog.append(",ip_len:");
    strLog.append(QString ::number(htons(ip->ip_len)));
    strLog.append(",ip_id:");
    strLog.append(QString ::number(htons(ip->ip_id)));
    strLog.append(",ip_sum:");
    strLog.append(QString ::number(htons(ip->ip_sum)));
    strLog.append("源IP:");
   strLog.append(inet_ntoa(ip->ip_src));
   strLog.append(",目标IP:");
   strLog.append(inet_ntoa(ip->ip_dst));
    qInfo() << strLog;

}
