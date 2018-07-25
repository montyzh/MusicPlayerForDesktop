#ifndef MY_MCI_H
#define MY_MCI_H
#include "head_file.h"



class My_MCI
{
public:
    My_MCI();
    MCI_OPEN_PARMS OpenParms;
    MCI_PLAY_PARMS PlayParms;
    //MCI_STATUS_PARMS StatusParms;
    DWORD getinfo(UINT wDeviceID,DWORD item);
    void mci_open();
    void mci_start();
    void mci_stop();

    DWORD SetVolume(DWORD Value); //设置音量
    QString cacau_len(int len);  //计算时长

    QString file_name;

};

#endif // MY_MCI_H
