#ifndef LOG_TOOLS_H
#define LOG_TOOLS_H
#include "net/net_common.h"
#include <QObject>

class LogTools : public QObject {
    Q_OBJECT
   public:
    explicit LogTools(QObject *parent = nullptr);
    static void  myMessageOutput(QtMsgType type, const QMessageLogContext &context,
                                 const QString &msg);
    void operator<<(const sniff_tcp *tcp);
    void operator<<(const sniff_ip *tcp);
   signals:

   public slots:
};

#endif  // LOG_TOOLS_H
