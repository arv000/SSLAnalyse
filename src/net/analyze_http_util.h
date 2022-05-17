#ifndef ANALYZE_HTTP_UTIL_H
#define ANALYZE_HTTP_UTIL_H

#include <QObject>

class AnalyzeHttpUtil : public QObject
{
    Q_OBJECT
public:
    explicit AnalyzeHttpUtil(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ANALYZE_HTTP_UTIL_H