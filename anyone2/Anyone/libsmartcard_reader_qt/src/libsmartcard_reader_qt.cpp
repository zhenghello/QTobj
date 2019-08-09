#include "libsmartcard_reader_qt.h"

#include <QDebug>
#include <QDateTime>
#include <QElapsedTimer>
//#include <QApplication>

libsmartcard_reader_qt::libsmartcard_reader_qt(int VID, int PID, char PORT):QObject(NULL)
{
    this->puserhid = new userHid(VID, PID, PORT);
    action_over = false;
}

libsmartcard_reader_qt::~libsmartcard_reader_qt()
{
    if(NULL != this->puserhid)
    {
        delete this->puserhid;
        this->puserhid = NULL;
    }
}

bool libsmartcard_reader_qt::cmd_open(UINT8 which_channel, int timeout /* = 500 */)
{
    bool b = false;
    int len = 0;
    UINT cmd_type = 0;
    UINT8 cmd_buff[9] = {0xAA, 0x00, 0x00, 0x03, 0x02, 0x00, 0x09, 0x00, 0x55};
    cmd_buff[5] = which_channel;
    cmd_buff[7] = 0x0E + which_channel;

    if(puserhid->hidSend(9, cmd_buff))
    {
        //??????
        while(1)
        {
            if(puserhid->hidParse(cmd_buff, len, cmd_type, timeout))
            {
                if(0x01 == cmd_buff[0]) //?????????υτ???
                {
                    b = true;
                    break;
                }
                else
                {
                    b = false;
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

    return b;
}

bool libsmartcard_reader_qt::cmd_close(UINT8 which_channel, int timeout /* = 500 */)
{
    bool b = false;
    int len = 0;
    UINT cmd_type = 0;
    UINT8 cmd_buff[9] = {0xAA, 0x00, 0x00, 0x03, 0x02, 0x00, 0x0A, 0x00, 0x55};
    cmd_buff[5] = which_channel;
    cmd_buff[7] = 0x0F + which_channel;

    if(puserhid->hidSend(9, cmd_buff))
    {
        //??????
        while(1)
        {
            if(puserhid->hidParse(cmd_buff, len, cmd_type, timeout))
            {
                if(0x01 == cmd_buff[0]) //?????????υτ???
                {
                    b = true;
                    break;
                }
                else
                {
                    b = false;
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

    return b;
}

bool libsmartcard_reader_qt::cmd_write(unsigned char df_p2, unsigned char ef_p2, unsigned short offset, unsigned short len, char* pbuff, int timeout, UINT8 which_channel /* = 0x00 */)
{
    bool b = false;
    int len_temp = 0;
    UINT cmd_type = 0;
    UINT8 *pcmd_buff = new UINT8[15 + len];

    pcmd_buff[0] = 0xAA;
    pcmd_buff[1] = 0x00;
    pcmd_buff[2] = ((9 + len) >> 8) & 0xFF;
    pcmd_buff[3] = (9 + len) & 0xFF;
    pcmd_buff[4] = 0x02;
    pcmd_buff[5] = which_channel;
    pcmd_buff[6] = 0x0B;
    pcmd_buff[7] = df_p2;
    pcmd_buff[8] = ef_p2;
    pcmd_buff[9] = (offset >> 8) & 0xFF;
    pcmd_buff[10] = offset & 0xFF;
    pcmd_buff[11] = (len >> 8) & 0xFF;
    pcmd_buff[12] = len & 0xFF;
    memcpy(&pcmd_buff[13], pbuff, len);
    pcmd_buff[13 + len] = 0x00;
    for(int i = 0;i < (len + 12);i++)
    {
        pcmd_buff[13 + len] += pcmd_buff[i + 1];
    }
    pcmd_buff[14 + len] = 0x55;

    if(puserhid->hidSend(15 + len, pcmd_buff))
    {
        //??????
        while(1)
        {
            if(puserhid->hidParse(pcmd_buff, len_temp, cmd_type, timeout))
            {
                if(0x01 == pcmd_buff[0])
                {
                    b = true;
                    break;
                }
                else
                {
                    b = false;
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

    delete []pcmd_buff;
    pcmd_buff = NULL;
    return b;
}

bool libsmartcard_reader_qt::cmd_get_cardid(UINT8 *pcar_id, UINT8 which_channel, int timeout)
{
    bool b = false;
    int len = 0;
    UINT cmd_type = 0;
    UINT8 cmd_buff[9] = {0xAA, 0x00, 0x00, 0x03, 0x02, 0x00, 0x0C, 0x00, 0x55};
    cmd_buff[5] = which_channel;
    cmd_buff[7] = 0x11 + which_channel;

    if(puserhid->hidSend(9, cmd_buff))
    {
        //??????
        while(1)
        {
            if(puserhid->hidParse(cmd_buff, len, cmd_type, timeout))
            {
                if((1 == len) && (0x00 == cmd_buff[0]))
                {
                    b = false;
                }
                else
                {
                    memcpy(pcar_id, cmd_buff, len);
                    b = true;
                }
                break;
            }
            else
            {
                break;
            }
        }
    }

    return b;
}

bool libsmartcard_reader_qt::cmd_oemset(UINT8 which_channel, UINT8 oem, int timeout /* = 500 */)
{
    bool b = false;
    int len = 0;
    UINT cmd_type = 0;
    UINT8 cmd_buff[10] = {0xAA, 0x00, 0x00, 0x04, 0x02, 0x00, 0x0D, 0x00, 0x00, 0x55};
    cmd_buff[5] = which_channel;
    cmd_buff[7] = oem;
    for(int i = 0;i < 7;i++)
    {
        cmd_buff[8] += cmd_buff[i + 1];
    }
    if(puserhid->hidSend(10, cmd_buff))
    {
        //??????
        while(1)
        {
            if(puserhid->hidParse(cmd_buff, len, cmd_type, timeout))
            {
                if((SMARTCARDOEMSET == (cmd_type & SMARTCARDOEMSET)) && (len == 2) && (cmd_buff[0] == 0x00) && (cmd_buff[1] == 0x00))
                {
                    b = true;
                }
                break;
            }
            else
            {
                break;
            }
        }
    }

    return b;
}

bool libsmartcard_reader_qt::cmd_create(unsigned char df_p2, unsigned char ef_p2, unsigned short len, unsigned char* pbuff, int timeout /* = 1000 */, UINT8 which_channel /* = 0x00 */)
{
    bool b = false;
    int len_temp = 0;
    UINT cmd_type = 0;
    UINT8 *pcmd_buff = new UINT8[13 + len];

    pcmd_buff[0] = 0xAA;
    pcmd_buff[1] = 0x00;
    pcmd_buff[2] = ((7 + len) >> 8) & 0xFF;
    pcmd_buff[3] = (7 + len) & 0xFF;
    pcmd_buff[4] = 0x02;
    pcmd_buff[5] = which_channel;
    pcmd_buff[6] = 0x0E;
    pcmd_buff[7] = df_p2;
    pcmd_buff[8] = ef_p2;
    pcmd_buff[9] = (len >> 8) & 0xFF;
    pcmd_buff[10] = len & 0xFF;
    memcpy(&pcmd_buff[11], pbuff, len);
    pcmd_buff[11 + len] = 0x00;
    for(int i = 0;i < (len + 10);i++)
    {
        pcmd_buff[11 + len] += pcmd_buff[i + 1];
    }
    pcmd_buff[12 + len] = 0x55;

    if(puserhid->hidSend(13 + len, pcmd_buff))
    {
        //??????
        while(1)
        {
            if(puserhid->hidParse(pcmd_buff, len_temp, cmd_type, timeout))
            {
                if(0x01 == pcmd_buff[0])
                {
                    b = true;
                    break;
                }
                else
                {
                    b = false;
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

    delete []pcmd_buff;
    pcmd_buff = NULL;
    return b;
}

bool libsmartcard_reader_qt::cmd_delete(int timeout /* = 20000 */, UINT8 which_channel /* = 0x00 */)
{
    bool b = false;
    int len = 0;
    UINT cmd_type = 0;
    UINT8 cmd_buff[9] = {0xAA, 0x00, 0x00, 0x03, 0x02, 0x00, 0x0F, 0x00, 0x55};
    cmd_buff[5] = which_channel;
    cmd_buff[7] = 0x14 + which_channel;

    if(puserhid->hidSend(9, cmd_buff))
    {
        //??????
        while(1)
        {
            if(puserhid->hidParse(cmd_buff, len, cmd_type, timeout))
            {
                if(0x01 == cmd_buff[0]) //???????????
                {
                    b = true;
                    break;
                }
                else
                {
                    b = false;
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

    return b;
}

bool libsmartcard_reader_qt::smartcard_read(MF &pmf, UINT8 &invalid_card_info, UINT16 &cpu_card_error_code, bool &timeout_flag, bool &usb_open_flag, UINT8* pcard_version_id, UINT8 which_channel /* = 0x00 */, int timeout /* = 20000 */, UINT8 oem /* = */ )
{
    UINT8 *pbuff = NULL;
    int len = 0;
    UINT cmd_type = 0;
    bool b = false;

    pbuff = new UINT8[8192];
    if(NULL == pbuff)
    {
        qDebug() << "\r\nE: Cannot get enough memory, smartcard_read!\r\n";
        return false;
    }
    memset(pbuff,0,8192);

    action_over = false;
    if(this->puserhid->hidOpen())//????usb??
    {
        if(this->cmd_oemset(which_channel, oem))
        {
            //?‘€?????????
            if(this->cmd_open(which_channel))
            {
                /*qint64 current_time = QDateTime::currentMSecsSinceEpoch() + 10000;*/
                /*QElapsedTimer t;
                t.start();*/

                timeout_flag = false;
                while(!action_over)
                {
                    //while(current_time > QDateTime::currentMSecsSinceEpoch()) //???10s???υτ?????????????????
                    //{
                    //	;
                    //}
                    //while(!t.hasExpired(10000))
                    //{
                    //	;//qApp->processEvents();

                    //}

                    if(puserhid->hidParse(pbuff, len, cmd_type, timeout))
                    {
                        switch(cmd_type & SMARTCARDMASK)
                        {
                        case SMARTCARDUPLOADBEGIN: //???????????
                            break;
                        case SMARTCARDUPLAODINFO: //?????????
                            {
                                if(MFDIR == ((pbuff[0] << 8) | pbuff[1]))
                                {
                                    EF *pcurrent_ef = new EF;
                                    pcurrent_ef->P2 = QString::number(pbuff[3]).rightJustified(2,'0');
                                    pcurrent_ef->dataLen = pbuff[4] << 8 | pbuff[5];
                                    pcurrent_ef->Data = new unsigned char[pcurrent_ef->dataLen];
                                    memcpy(pcurrent_ef->Data, &pbuff[6], pcurrent_ef->dataLen);

                                    pmf.EFList.append(pcurrent_ef);
                                }
                                else
                                {
                                    QString df_temp = QString::number(pbuff[1]).rightJustified(2,'0');
                                    int df_exist_index = -1;
                                    int df_length = pmf.DFList.length();
                                    for(int i = 0;i < df_length;i++)
                                    {
                                        if(df_temp == pmf.DFList.at(i)->P2) //DF??¦Λ??
                                        {
                                            df_exist_index = i;
                                            break;
                                        }
                                    }
                                    if(df_exist_index == -1) //DF???????,??????DF
                                    {
                                        DF *pcurrent_df = new DF;
                                        pcurrent_df->P2 = df_temp;

                                        pmf.DFList.append(pcurrent_df);
                                        df_exist_index = df_length;
                                    }
                                    //???DF??????EF
                                    EF *pcurrent_ef = new EF;
                                    pcurrent_ef->P2 = QString::number(pbuff[3]).rightJustified(2,'0');
                                    pcurrent_ef->dataLen = pbuff[4] << 8 | pbuff[5];
                                    pcurrent_ef->Data = new unsigned char[pcurrent_ef->dataLen];
                                    memcpy(pcurrent_ef->Data, &pbuff[6], pcurrent_ef->dataLen);

                                    pmf.DFList.at(df_exist_index)->EFList.append(pcurrent_ef);
                                }
                            }
                            break;
                        case SMARTCARDUPLOADEND: //????????????????????????????
                            {
                                action_over = true;
                                b = true;
                            }
                            break;
                        case SMARTCARDUPLOADINVALIDCARD: //??????????§Ή??
                            {
                                invalid_card_info = pbuff[0];
                                cpu_card_error_code = 0x0000;
                                action_over = true;
                                b = false;
                            }
                            break;
                        case SMARTCARDUPLOADCARDINFO: //??????·Ϊ???ID
                            {
                                memcpy(pcard_version_id, pbuff, len);
                            }
                            break;
                        case SMARTCARDUPLOADCARDERRORCODE: //???????????CPU?????????????
                            {
                                invalid_card_info = 0x00;
                                cpu_card_error_code = pbuff[0] << 8 | pbuff[1];
                                action_over = true;
                                b = false;
                            }
                            break;
                        }
                    }
                    else
                    {
                        timeout_flag = true;
                        break;
                    }
                }
            }
            else
            {
                timeout_flag = true;
            }
        }
        else
        {
            timeout_flag = true;
        }

        delete []pbuff;
        pbuff = NULL;
        this->cmd_close(which_channel);
        puserhid->hidClose();
        return b;
    }
    else
    {
        usb_open_flag = true;
        delete []pbuff;
        pbuff = NULL;
        this->cmd_close(which_channel);
        puserhid->hidClose();
        return false;
    }
}

bool libsmartcard_reader_qt::smartcard_write(unsigned char df_p2, unsigned char ef_p2, unsigned short offset, unsigned short len, char* pbuff, int timeout /* = 1000 */, UINT8 which_channel /* = 0x00 */, UINT8 oem /* = */ )
{
    bool b = false;

    //????usb??
    if(puserhid->hidOpen())
    {
        if(this->cmd_oemset(which_channel, oem))
        {
            b = this->cmd_write(df_p2, ef_p2, offset, len, pbuff, timeout, which_channel); //§Υ??
        }
        puserhid->hidClose();
        return b;
    }
    else
    {
        puserhid->hidClose();
        return false;
    }
}

bool libsmartcard_reader_qt::smartcard_get_cardid(UINT8 *pcar_id, int timeout /* = 1000 */, UINT8 which_channel /* = 0x00 */, UINT8 oem /* = */ )
{
    bool b = false;

    //????usb??
    if(puserhid->hidOpen())
    {
        if(this->cmd_oemset(which_channel, oem))
        {
            b = this->cmd_get_cardid(pcar_id, which_channel, timeout);
        }

        puserhid->hidClose();
        return b;
    }
    else
    {
        puserhid->hidClose();
        return false;
    }
}

bool libsmartcard_reader_qt::smartcard_create(MF &pmf, UINT8 which_channel /* = 0x00 */, UINT8 oem /* = */ )
{
    bool b = false;

    //????usb??
    if(puserhid->hidOpen())
    {
        b = this->cmd_oemset(which_channel, oem);
        if(!b)
        {
            puserhid->hidClose();
            return b;
        }

        int mf_ef_length = pmf.EFList.length();
        for(int i = 0;i < mf_ef_length;i++) //????MF?¦Μ?EF
        {
            QByteArray efByteArray = pmf.EFList.at(i)->P2.toLatin1();
            UINT8 ef_dir =  efByteArray.at(1) - '0';
            UINT16 ef_len = pmf.EFList.at(i)->dataLen;
            UINT8 *pef_data = pmf.EFList.at(i)->Data;

            b = this->cmd_create(0x00, ef_dir, ef_len, pef_data, 1000, which_channel);
            if(!b)
            {
                puserhid->hidClose();
                return b;
            }
        }

        int mf_df_length = pmf.DFList.length();
        for(int i = 0;i < mf_df_length;i++)
        {
            QByteArray dfByteArray = pmf.DFList.at(i)->P2.toLatin1();
            UINT8 df_dif = dfByteArray.at(1) - '0';
            int df_ef_length = pmf.DFList.at(i)->EFList.length();
            for(int j = 0;j < df_ef_length;j++)
            {
                QByteArray efByteArray = pmf.DFList.at(i)->EFList.at(j)->P2.toLatin1();
                UINT8 ef_dir = efByteArray.at(1) - '0';
                UINT16 ef_len = pmf.DFList.at(i)->EFList.at(j)->dataLen;
                UINT8 *pef_data = pmf.DFList.at(i)->EFList.at(j)->Data;

                b = this->cmd_create(df_dif, ef_dir, ef_len, pef_data, 1000, which_channel);
                if(!b)
                {
                    puserhid->hidClose();
                    return b;
                }
            }
        }

        puserhid->hidClose();
        return b;
    }
    else
    {
        puserhid->hidClose();
        return false;
    }
}

bool libsmartcard_reader_qt::smartcard_delete(int timeout /* =20000 */, UINT8 which_channel /* = 0x00 */, UINT8 oem /* = */ )
{
    bool b = false;

    //????usb??
    if(puserhid->hidOpen())
    {
        if(this->cmd_oemset(which_channel, oem))
        {
            b = this->cmd_delete(timeout, which_channel);
        }
        puserhid->hidClose();
        return b;
    }
    else
    {
        puserhid->hidClose();
        return false;
    }
}
