#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class NetUtil;
class QToolBar;
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private:
    QToolBar *m_ptrToolBar;
    QAction *m_ptrActionToolBarStart;
    QAction *m_ptrActionToolBarStop;
    NetUtil *m_ptrNetUtil;

   private:
    /**
     * @brief 初始化界面
     */
    void initUI();
    /**
     * @brief 初始化菜单栏
     */
    void initUIMenuBar();
    /**
     * @brief 初始化工具栏
     */
    void initUIToolBar();
    /**
     * @brief 初始化信号绑定信息。
     */
    void initConnect();

   public slots:
    /**
     * @brief 开始抓取数据
     */
    void slotStartCaptureData();
    /**
     * @brief 暂定抓取数据
     */
    void slotStopCapture();
};

#endif  // MAINWINDOW_H
