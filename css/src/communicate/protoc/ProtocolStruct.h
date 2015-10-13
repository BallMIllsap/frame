///************************************************************
/// @Copyright (C), 1993-2022, hzcw  Information Technologies Co., Ltd.
/// @URL
/// @file           ProtocolStruct.h
/// @brief          协议结构类
/// @attention
/// @Author         chenjianjun
/// @Version        0.1
/// @Date           2015年09月26日
/// @Description
/// @History
///************************************************************
#ifndef __PROTOCOL_STRUCT_H_
#define __PROTOCOL_STRUCT_H_

#include "ModuleConstDef.h"
#include "../Communicate.h"

typedef struct stProtocolBase
{
    /// 消息ID
    jsbn::protoc::MSG command_id;
    /// 连接序号
    unsigned short sock_handle;

}TProtocolBase;

typedef std::shared_ptr<TProtocolBase> sProtocolData_ptr;

#endif //__PROTOCOL_STRUCT_H_

