///************************************************************
/// @Copyright (C), 1993-2022, hzcw  Information Technologies Co., Ltd.
/// @URL
/// @file           ProtocolProcManager.h
/// @brief          协议处理管理类
/// @attention
/// @Author         chenjianjun
/// @Version        0.1
/// @Date           2015年09月16日
/// @Description
/// @History
///************************************************************
#ifndef __PROTOCOL_PROC_MANAGER_H_
#define __PROTOCOL_PROC_MANAGER_H_

#include "ModuleConstDef.h"
#include "ProtocolStruct.h"
#include "../Communicate.h"

class ProtocolProcManager
{
public:
    // 解析通信协议
    static sProtocolData_ptr ParseProtocol(const unsigned char*, PacketLength);

private:
    static sProtocolData_ptr GetRecvData(sNetProtocolDataPage_ptr&);
};

#endif //__PROTOCOL_PROC_MANAGER_H_

