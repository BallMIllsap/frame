///************************************************************
/// @Copyright (C), 2015-2030, jsbn  Information Technologies Co., Ltd.
/// @URL
/// @file           BssTcpClient.h
/// @brief          业务服务器客户端
/// @attention
/// @Author         chenjianjun
/// @Version        0.1
/// @Date           2015年10月13日
/// @Description
/// @History
///************************************************************
#ifndef __BSS_TCP_CLIENT_H_
#define __BSS_TCP_CLIENT_H_

#include "module_const_def.h"
#include "../communicate.h"

class BssTcpClient:public jsbn::PassiveTCPClient
{
public:

    BssTcpClient(unsigned short seq, struct sockaddr_in* sa, short heart_time = 10);

    ~BssTcpClient();

    bool Isvalid();

    void SetIp(std::string bss_client_ip) { _bss_client_ip = bss_client_ip; }
    void SetBssClinentInfo(TBssClientInfo info);

    TBssClientInfo& GetBssClinentInfo();

private:
    // 地域ID
    TBssClientInfo _bss_client_info;
    // 服务器IP
    std::string _bss_client_ip;
};

#endif
