#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "head_file.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    My_MCI mic;



    static QString file_name;       //文件名字
    static int volume_btn_val;   //记录音量按钮的状态值
    static int volume_slit_val; //记录当前滑块的值
    bool pause_btn = true;     //开始按钮状态记录值
    static int sons_number_now;   //当前播放歌曲的下标
    static int sons_nums;       //列表中歌曲的总数目

    QLabel  *time_len;        //时长标签
    QGroupBox *box_player;    //播放控制界面box
    QGroupBox *box_main;     //主窗口box
    QGroupBox *box_list;    //列表box
    QListWidget *sons_list;  //歌曲清单
    QLineEdit *sons_table;      //列表表头
    QStringList *sons_lists;     //保存文件名的变量
    QListWidgetItem *item;
    QPushButton *start_btn;         //开始按钮
    QSlider *ctr_audio_value;       //音量滑块
    QPushButton *volume_ico;        //音量按钮
    QPushButton *next_song;         //下一首按钮
    QPushButton *previous_song;     //上一首按钮
    QLabel *playing_now;            //正在播放标签
    QLabel *str_q;
    QPushButton *menu_addfile;         //工具栏->添加文件按钮
    QPushButton *menu_info;             //工具栏->信息
    void reade_file();                  //读出文件函数
    void write_file();                  //写入文件函数

    void stan_song_volume_func();
    void keyPressEvent(QKeyEvent *e);
    static void setStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
public slots:
    int start_btn_func();
    void doubleclicked(QListWidgetItem* item);
    void setLineEditValue(int value);
    void trigerMenu();
    void btn_volume_ico_func();
    void btn_next_song_func();
    void btn_previous_song_func();
    int menu_info_btn_func();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
