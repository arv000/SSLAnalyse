#ifndef ANALYZE_HTTP_UTIL_H
#define ANALYZE_HTTP_UTIL_H

#include <QObject>

class AnalyzeHttpUtil : public QObject {
    Q_OBJECT
   public:
    explicit AnalyzeHttpUtil(QObject *parent = nullptr);
    int parseHttpHead(const u_char *payload,const unsigned int payload_len);
   signals:

   public slots:
};

#endif  // ANALYZE_HTTP_UTIL_H
