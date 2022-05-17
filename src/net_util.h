#ifndef NET_UTIL_H
#define NET_UTIL_H

#include <QObject>

class NetUtil : public QObject
{
    Q_OBJECT
public:
    explicit NetUtil(QObject *parent = nullptr);

signals:

public slots:
};

#endif // NET_UTIL_H