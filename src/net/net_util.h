#ifndef NET_UTIL_H
#define NET_UTIL_H

#include <QObject>

class NetUtil : public QObject {
    Q_OBJECT
   public:
    explicit NetUtil(QObject *parent = nullptr);
    /**
     * @brief 开始抓取数据
     */
    int StartCaptureData();
    /**
     * @brief 停止抓取
     */
    int StopCaptureData();
    /**
     * @brief 开始抓取数据
     */
    int StartCaptureData(QString strDevName);
    /**
     * @brief 停止抓取
     */
    int StopCaptureData(QString strDevName);
    /**
     * @brief 获取网络设备列表
     * @return
     */
    QStringList NetDevNameList();

   private:
    bool m_bStatus;
   signals:

   public slots:
};

#endif  // NET_UTIL_H
