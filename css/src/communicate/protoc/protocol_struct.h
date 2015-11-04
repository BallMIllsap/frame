///************************************************************
/// @Copyright (C), 1993-2022, jsbn  Information Technologies Co., Ltd.
/// @URL
/// @file           protocol_struct.h
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

#include "module_const_def.h"
#include "../communicate.h"

// 通信协议基类
typedef struct stProtocolBase
{
    /// 消息ID
    jsbn::protoc::CommandID command_id;
    /// 连接序号
    unsigned int seq;
    /// 句柄
    unsigned short sock_handle;

}TProtocolBase;
typedef std::shared_ptr<TProtocolBase> sProtocolData_ptr;

// 注册请求
typedef struct stRegisterRequest : public TProtocolBase
{
    // 城市ID
    jsbn::protoc::CityID city_id;

}TRegisterRequest;

// 数据转发请求
typedef struct stDataRelayReq : public TProtocolBase
{
    // 源服务器
    jsbn::protoc::ServiceTpye src_srv_type;
    // 目的服务器
    jsbn::protoc::ServiceTpye dst_srv_type;
    // 目的城市ID
    jsbn::protoc::CityID dst_city_id;
    // 消息内容
    std::string msg;

    void clear()
    {
        msg.clear();
        dst_city_id = jsbn::protoc::CityID::CID_INIT;
    }

}TDataRelayReq;

#endif //__PROTOCOL_STRUCT_H_

