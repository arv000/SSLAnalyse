#ifndef SELECT_NET_DEV_H
#define SELECT_NET_DEV_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
class SelectNetDevDialog : public QDialog {
    Q_OBJECT
   public:
    explicit SelectNetDevDialog(QWidget *parent = nullptr);
    void initUI();
    void initConnect();

   private:
    QLabel *m_ptrLabSelectDevName;
    QPushButton *m_ptrBtnRejected;
    QPushButton *m_ptrBtnAccepted;
    QGridLayout *m_ptrLayoutMain;
    QComboBox *m_ptrCmbSelectDevName;
    QString m_strDevName;

   public:
    static QString getSelectDevName();
    QString getDevName();
   signals:

   public slots:
    void accept();
    void reject();
    void currentIndexChanged(QString strDevName);
};

#endif  // SELECT_NET_DEV_H
