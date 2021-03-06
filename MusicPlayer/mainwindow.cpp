#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle(QStringLiteral("Q-One Player"));
    box_main = new QGroupBox(this);
    box_list = new QGroupBox(box_main); //列表box
    sons_list = new QListWidget(box_list);//歌曲清单
    sons_lists = new QStringList;
    this->reade_file();                       //创建窗口时读写出文件

    //ui->setupUi(this);                        //不使用界面文件
    this->resize(MainWind_Width ,MainWind_Height);//主窗口大小设置
    this->setFixedSize(this->width(), this->height());    //设置窗口大小不可变动

    //*********box 设置

    box_main->setGeometry(0,0,MainWind_Width ,MainWind_Height);//主窗口box

    //主窗口box样式设置
    //box_main->setStyleSheet("QGroupBox{border-width:2px; border-style:solid;  border-radius: 10px;border-color:gray;margin-top:0.5ex;background-color:gray;}");




    box_player = new QGroupBox(box_main); //控件box
   //设置控件box的相对位置及大小


    box_player->setGeometry(MainWind_X,MainWind_Y+29,Box_Player_Width,Box_Player_Height);

    /***************************************************************************/
    //设置控件box的样式

    box_player->setStyleSheet
            (
"QGroupBox{border-width:2px; border-style:solid;  border-radius: 10px;border-color:black;background:rgb(0,64,0);margin-top:0.5ex;}");



    box_list->setGeometry(MainWind_X,MainWind_Y+150,Box_List_Width,Box_List_Height);

     /***************************************************************************/
    //列表box设置样式
    box_list->setStyleSheet
            (
"QGroupBox{border-width:2px; border-style:solid; background:rgb(0,0,64); border-radius: 10px;border-color:black;margin-top:0.5ex;}");

    sons_table = new QLineEdit(box_list);//列表表头

    sons_table ->setGeometry(MainWind_X+25,MainWind_Y+5,LineEdi_Table_Width,LineEdi_Table_Height);

    //设置列表为只读模式
    sons_table->setReadOnly(true);

    //*****************************************************************/

    sons_table->setStyleSheet("QLineEdit{border-width:2px; border-style:solid;  border-radius: 10px;border-color:black;margin-top:0.5ex;font-size:18px;background:rgb(0,64,0);}");

    //设置表头字符串
    sons_table->setText("     Song");



    sons_list ->setGeometry(MainWind_X+25,MainWind_Y+42,Box_List_Width-50,Box_List_Height-50);
//**********************************************************************************/
    //设置歌单列表样式
    sons_list ->setStyleSheet("QListView{border-width:5px; border-style:solid;  border-radius: 10px;border-color:black;margin-top:0.5ex;background:rgb(0,64,0);}");

    //歌曲清单列表显示

   //列表显示模式
    sons_list ->setViewMode(QListView::ListMode);
    //绑定双击列表事件
    QObject::connect(sons_list,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(doubleclicked(QListWidgetItem*)));


    //开始暂停按钮
    start_btn = new QPushButton(box_player);

    //
    start_btn->setGeometry(MainWind_X+55,MainWind_Y+5,StartButton_Width,StartButton_Heigth);

    //设置按钮图片
    QIcon icon2(":/image/2.png");
    start_btn->setIcon(icon2);
    start_btn->setIconSize(QSize(20,20));
    start_btn->setFlat(true);

    connect(start_btn,SIGNAL(clicked()),this,SLOT(start_btn_func()));

    //显示music时长
    time_len = new QLabel(box_player);
    QLabel *LABEL_LENGTH = new QLabel(box_player);
    LABEL_LENGTH->setGeometry(430,8,80,20);
    LABEL_LENGTH->setText("Length:");
    LABEL_LENGTH->setStyleSheet("font-size:18px;");
    time_len->setText("00:00");
    time_len->setGeometry(500,8,80,20);
    time_len->setStyleSheet("font-size:18px;");

    //滑块控制音量
    ctr_audio_value = new QSlider(Qt::Horizontal,box_player);
    ctr_audio_value->setMinimum(0);
    ctr_audio_value->setMaximum(1000);
    ctr_audio_value->setValue(500);         //音量初始值
    ctr_audio_value->setGeometry(230,11,80,20);
    ctr_audio_value->setSingleStep(100);    //步进值



    connect(ctr_audio_value, SIGNAL(valueChanged(int)), this, SLOT(setLineEditValue(int)));



    //音量图标
    volume_ico = new QPushButton (box_player);
    QIcon icon3(":/image/3.png");
    volume_ico->setGeometry(200,7,30,30);
    volume_ico->setIcon(icon3);
    volume_ico->setIconSize(QSize(20,20));
    volume_ico->setFlat(true);

    connect(volume_ico,SIGNAL(clicked()),this,SLOT(btn_volume_ico_func()));

    //下一首
     next_song = new QPushButton(box_player);
     QIcon icon4(":/image/5.png");
     next_song->setGeometry(105,5,30,30);
     next_song->setIcon(icon4);
     next_song->setIconSize(QSize(18,18));
     next_song->setFlat(true);

     connect(next_song,SIGNAL(clicked()),this,SLOT(btn_next_song_func()));


     //上一首
     previous_song = new QPushButton(box_player);
     QIcon icon5(":/image/6.png");
     previous_song->setGeometry(5,5,30,30);
     previous_song->setIcon(icon5);
     previous_song->setIconSize(QSize(18,18));
     previous_song->setFlat(true);

     connect(previous_song,SIGNAL(clicked()),this,SLOT(btn_previous_song_func()));


     //显示播放

     str_q = new QLabel(box_player);
    // str_q->setText("Playing:");
     str_q->setGeometry(10,50,80,50);
     str_q->setStyleSheet("font-size:18px;");

     playing_now = new QLabel(box_player);
     playing_now->setGeometry(90,50,600,50);
     playing_now->setStyleSheet("font-size:15px;");






        //菜单栏按钮设置

     menu_addfile = new QPushButton(this);

     QIcon icon6(":/image/7.png");
     menu_addfile->setGeometry(5,2,30,30);
     menu_addfile->setIcon(icon6);
     menu_addfile->setIconSize(QSize(25,25));
     menu_addfile->setFlat(true);
     connect(menu_addfile,SIGNAL(clicked()),this,SLOT(trigerMenu()));

     //版本信息按钮

     menu_info = new QPushButton(this);
     QIcon icon7(":/image/8.png");
     menu_info->setGeometry(50,2,30,30);
     menu_info->setIcon(icon7);
     menu_info->setIconSize(QSize(25,25));
     menu_info->setFlat(true);
     connect(menu_info,SIGNAL(clicked()),this,SLOT(menu_info_btn_func()));




     //加载样式文件
     MainWindow ::setStyle("css.qss");
}

MainWindow::~MainWindow()
{
    this->write_file();
    delete ui;
}


int MainWindow::start_btn_func()
{
    if(pause_btn == true)
    {
        pause_btn = false;
        mic.mci_start();
        //改变按钮图标
            QIcon icon2(":/image/1.png");
            start_btn->setIcon(icon2);
            start_btn->setIconSize(QSize(20,20));
            start_btn->setFlat(true);
        return 1;

    }
    else if (pause_btn == false)
    {
        pause_btn = true;
        mic.mci_stop();
        //改变按钮图标
            QIcon icon1(":/image/2.png");
            start_btn->setIcon(icon1);
            start_btn->setIconSize(QSize(20,20));
            start_btn->setFlat(true);
        return 2;

    }


}


//菜单栏按钮实现函数
void MainWindow::trigerMenu( )
{

        //添加文件前先关闭之前媒体
        mciSendCommand(mic.OpenParms.wDeviceID, MCI_CLOSE, 0, NULL);
        //把开始按钮状态取反 ，以及改变按钮图片
            if(pause_btn == true){pause_btn=false;}
            QIcon icon1(":/image/2.png");
            start_btn->setIcon(icon1);
            start_btn->setIconSize(QSize(20,20));
            start_btn->setFlat(true);



        //获取桌面路径，打开添加文件后默认为桌面地址
        QString dir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        MainWindow::file_name =  QFileDialog::getOpenFileName(this ,NULL,dir,"Mp3 file(*.mp3)",0,0) ;


        //这里我们需要判定点击按钮后是否添加了文件

        if(file_name != ""){

            //打开媒体
            mic.mci_open();
            //在列表中添加歌曲
            sons_list->addItem ((mic.file_name));
            QString swap_file_name = mic.file_name;

            //在lists中把添加进来的文件保存在QStringList中
            *sons_lists<<QString(swap_file_name);

            //记录歌曲的数量
            this->sons_nums++;

            this->pause_btn = true;

            //显示时长
            time_len ->setText(mic.cacau_len(mic.getinfo(mic.OpenParms.wDeviceID,MCI_STATUS_LENGTH)));


        }

}

QString MainWindow::file_name = "";


//列表双击相应事件
void MainWindow::doubleclicked(QListWidgetItem* item)
{

    //双击后先关闭先前的媒体
    mciSendCommand(mic.OpenParms.wDeviceID, MCI_CLOSE, 0, NULL);
    //根据列表的歌曲名字打开对应的媒体
    MainWindow:: file_name = item->text();
    //打开媒体并开始播放，按钮状态随著改变
    mic.mci_open();
    mic.mci_start();

        if(pause_btn == true){pause_btn=false;}
        QIcon icon1(":/image/1.png");
        start_btn->setIcon(icon1);
        start_btn->setIconSize(QSize(20,20));
        start_btn->setFlat(true);

    time_len ->setText(mic.cacau_len(mic.getinfo(mic.OpenParms.wDeviceID,MCI_STATUS_LENGTH)));

    //保存当前播放歌曲所在下标
    int row = 0;
    //记录双击的列的下标值
       while(sons_list->item(row)->text() != file_name)
       {
           row ++ ;

       }
        //将下标值标为当前播放的下表值
       sons_number_now = row;
      // 解决静音模式下切歌漏声和图标bug
       stan_song_volume_func();
      // 显示正在播放的歌曲
       str_q->setText("Playing:");
       playing_now->setText(sons_list->item(sons_number_now)->text());
}

int MainWindow::sons_nums = 0;


//写文件函数
void MainWindow::write_file()
{

    QString fin = "dat.txt";
    QFile file(fin);
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream in(&file);
    //先写入当前打开歌曲的数目
    in<<this->sons_nums<<"\n";
    //根据保存在变量里的值遍历并写入文件
    for (int i = 0;i<this->sons_nums;++i){
       in<<sons_lists->at(i)<<"\n";

   }
     file.close();

}

//读文件函数
void MainWindow::reade_file()
{
    QString fin = "dat.txt";
    QString list_vitual;
    QFile file(fin);
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream in(&file);
        //读取文件中的歌曲数目，此过程需要转换格式
        QString tr = in.readLine();
        bool ok;
        int num = tr.toInt(&ok,10);
        int j = num;
        //保存歌曲数目
        this->sons_nums = num;
    while(j--)
    {
        list_vitual = in.readLine();
       *sons_lists<<QString(list_vitual);
    }
    //读取出来的歌曲一并添加到列表中
    for ( j = 0;j<num;j++){


            sons_list->addItem( sons_lists->value(j));


    }
        file.close();

}


//按键重构
//函数无效
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->modifiers() == (Qt::ControlModifier) && e->key() == Qt::Key_N)
    {

        mciSendCommand(mic.OpenParms.wDeviceID, MCI_CLOSE, 0, NULL);
        MainWindow::file_name =  QFileDialog::getOpenFileName(this ,NULL,"C:\\","Mp3 file(*.mp3)",0,0) ;

        mic.mci_open();


        sons_list->addItem ((mic.file_name));
        QString swap_file_name = mic.file_name;

        *sons_lists<<QString(swap_file_name);
        this->sons_nums++;

        this->pause_btn = true;
        time_len ->setText(mic.cacau_len(mic.getinfo(mic.OpenParms.wDeviceID,MCI_STATUS_LENGTH)));

    }

}

//音量调节
void MainWindow::setLineEditValue(int value)
{

    //将滑块当前的值设置为音量值
    value = ctr_audio_value->value();
    mic.SetVolume(value);//实际操作函数
    //记录当前滑块的值
    MainWindow::volume_slit_val = value;


        QIcon icon2(":/image/3.png");
        volume_ico->setGeometry(200,7,30,30);
        volume_ico->setIcon(icon2);
        volume_ico->setIconSize(QSize(20,20));
        volume_ico->setFlat(true);

        volume_btn_val = 0;


    //手动拉滑块至静音图标
    if(ctr_audio_value->value() == 0){

        QIcon icon3(":/image/4.png");
        volume_ico->setGeometry(200,7,30,30);
        volume_ico->setIcon(icon3);
        volume_ico->setIconSize(QSize(17,17));
        volume_ico->setFlat(true);
        //如果手动拉至静音，则需同步音量图标的显示
        volume_btn_val = 1;



    }


}


int MainWindow::volume_btn_val = 0;
int MainWindow::volume_slit_val = 500;



//音量图标切换显示函数

void MainWindow::btn_volume_ico_func()
{

    if(volume_btn_val == 0){
        //手动点击按钮切换图标
            QIcon icon3(":/image/4.png");
            volume_ico->setGeometry(200,7,30,30);
            volume_ico->setIcon(icon3);
            volume_ico->setIconSize(QSize(17,17));
            volume_ico->setFlat(true);
        volume_btn_val = 1;

        //静音模式




        mic.SetVolume(0);

    }
    else if(volume_slit_val != 0){  //如果不是拖拉滑块至静音的情况下就执行以下
     if (volume_btn_val == 1){
        //手动点击按钮切换图标
              QIcon icon2(":/image/3.png");
              volume_ico->setGeometry(200,7,30,30);
              volume_ico->setIcon(icon2);
              volume_ico->setIconSize(QSize(20,20));
              volume_ico->setFlat(true);

          volume_btn_val = 0;

          //恢复之前的音量值
          ctr_audio_value->setValue(volume_slit_val);
          mic.SetVolume(volume_slit_val);

    }
   }


}



int MainWindow::sons_number_now = -1;


//下一首响应函数
void MainWindow::btn_next_song_func()
{

    //先关闭之前的媒体
    mciSendCommand(mic.OpenParms.wDeviceID, MCI_CLOSE, 0, NULL);

   // 下一首到最下面时在点击就直接跳到列表开始
    if(sons_number_now >= sons_nums-1){
        sons_number_now = -1;

    }
    //获取文件名
    MainWindow:: file_name = sons_list->item(sons_number_now+1)->text();
    sons_number_now ++;

    //打开并播放文件
    mic.mci_open();
    mic.mci_start();
        //刷新开始按钮
        if(pause_btn == true){pause_btn=false;}

        QIcon icon1(":/image/1.png");
        start_btn->setIcon(icon1);
        start_btn->setIconSize(QSize(20,20));
        start_btn->setFlat(true);
    time_len ->setText(mic.cacau_len(mic.getinfo(mic.OpenParms.wDeviceID,MCI_STATUS_LENGTH)));
    //解决静音模式下切歌漏声和图标bug
    stan_song_volume_func();
}


//解决静音模式下切歌漏声和图标bug

void MainWindow::stan_song_volume_func()
{


    if(volume_btn_val == 1){

        mic.SetVolume(0);

    }
    else if (volume_btn_val ==0){

        mic.SetVolume(volume_slit_val);

    }

    sons_list->item(sons_number_now)->setSelected(true);
    str_q->setText("Playing:");
    playing_now->setText(sons_list->item(sons_number_now)->text());

}


//上一首按钮响应事件
//类似下一首函数
void MainWindow::btn_previous_song_func()
{
    mciSendCommand(mic.OpenParms.wDeviceID, MCI_CLOSE, 0, NULL);

    if(sons_number_now <= 0){
        sons_number_now = sons_nums;

    }

    MainWindow:: file_name = sons_list->item(sons_number_now-1)->text();
    sons_number_now --;


    mic.mci_open();
    mic.mci_start();

        if(pause_btn == true){pause_btn=false;}

        QIcon icon1(":/image/1.png");
        start_btn->setIcon(icon1);
        start_btn->setIconSize(QSize(20,20));
        start_btn->setFlat(true);
    time_len ->setText(mic.cacau_len(mic.getinfo(mic.OpenParms.wDeviceID,MCI_STATUS_LENGTH)));

    stan_song_volume_func();



}


//信息按钮响应函数
int MainWindow::menu_info_btn_func()
{

 QMessageBox::information(NULL, QString("About"),
                          QString("<font size='6'>Q-One Player</font> <br><font color='red'>Version: 1.0 Beta</font> <br>E-mail:36440859@qq.com"),
                          0,
                          0);

 return 0;

}
