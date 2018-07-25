#include "my_mci.h"
#include "mainwindow.h"
#pragma comment(lib,"winmm.lib")

My_MCI::My_MCI()
{

}


//打开一个媒体文件
void My_MCI::mci_open()
{

     OpenParms.lpstrDeviceType = NULL; // "mpegvideo";
     this->file_name = MainWindow::file_name;
     const QChar *f_n = this->file_name.unicode();
     OpenParms.lpstrElementName = LPCWSTR(f_n);
     OpenParms.wDeviceID =NULL;
     mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&OpenParms);

}

//播放打开的媒体文件
void My_MCI::mci_start()
{
    int Cdlen;
    PlayParms.dwFrom = 0;

    mciSendCommand(OpenParms.wDeviceID, MCI_RESUME, NULL, (DWORD)&PlayParms);
    //mciSendCommand (OpenParms.wDeviceID, MCI_STATUS_LENGTH, MCI_WAIT | MCI_STATUS_ITEM,(DWORD)(LPVOID) &StatusParms);
    Cdlen=getinfo(OpenParms.wDeviceID,MCI_STATUS_LENGTH);
}

void My_MCI::mci_stop()
{

    mciSendCommand(OpenParms.wDeviceID, MCI_PAUSE, NULL, (DWORD)&PlayParms);

}

//获取时长信息
DWORD My_MCI::getinfo(UINT wDeviceID,DWORD item)
{
     MCI_STATUS_PARMS mcistatusparms;
    // mcistatusparms.dwCallback=(DWORD)GetSafeHwnd();
     mcistatusparms.dwItem=item;
     mcistatusparms.dwReturn=0;
     mciSendCommand(wDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)&mcistatusparms);
     return mcistatusparms.dwReturn;
}


//时长转换为时间格式显示
QString My_MCI::cacau_len(int len)
{
    int time = len/1021;
    int time_s = time%60;
    int time_m = (time - time_s)/60;
    QString s = QString::number(time_s, 10);
    QString m = QString::number(time_m, 10);
    return m+":"+s;


}


DWORD My_MCI::SetVolume(DWORD Value)
{
    DWORD dwResult=0;
    MCI_DGV_SETAUDIO_PARMS mciSetAudioPara;
    mciSetAudioPara.dwItem = MCI_DGV_SETAUDIO_VOLUME;
    mciSetAudioPara.dwValue = Value;
    mciSendCommand(OpenParms.wDeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&mciSetAudioPara);
    return dwResult;
}



