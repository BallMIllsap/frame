///************************************************************
/// @Copyright (C), 1993-2022, jsbn  Information Technologies Co., Ltd.
/// @URL
/// @file           protocol_proc_manager.cpp
/// @brief          协议处理管理类
/// @attention
/// @Author         chenjianjun
/// @Version        0.1
/// @Date           2015年09月16日
/// @Description
/// @History
///************************************************************
#include "protocol_proc_manager.h"
#include <assert.h>

void delete_recv_page(TProtocolBase* p)
{
    switch(p->command_id)
    {
        case jsbn::protoc::CommandID::Heart_Beat:
        {
            CObjectAllocator<TProtocolBase>::get_instance()->free((TProtocolBase*)p);
            break;
        }
        case jsbn::protoc::CommandID::Register_Req:
        {
            CObjectAllocator<TRegisterRequest>::get_instance()->free((TRegisterRequest*)p);
            break;
        }
        case jsbn::protoc::CommandID::Relay_Req:
        {
            CObjectAllocator<TRelayRequest>::get_instance()->free((TRelayRequest*)p);
            break;
        }
        default:
        {
            LOG(ERROR)<<"无法释放此类型的指针,ID:"<<p->command_id;
            break;
        }
    }
}

sProtocolData_ptr ProtocolProcManager::ParseProtocol(const unsigned char* buf, PacketLength len)
{
    // 解析协议，生成一个协议的智能指针区域
    static sNetProtocolDataPage_ptr protocol = std::make_shared<jsbn::protoc::NetProtocol>();

    protocol->Clear();
    if (!protocol->ParseFromArray(buf, len))
    {
        LOG(ERROR)<<"协议解析失败";
        return nullptr;
    }

    sProtocolData_ptr ptr = nullptr;
    switch(protocol->commandid())
    {
        case jsbn::protoc::CommandID::Heart_Beat:
        {
            ptr = sProtocolData_ptr(CObjectAllocator<TProtocolBase>::get_instance()->malloc(), delete_recv_page);
            ptr->command_id = jsbn::protoc::CommandID::Heart_Beat;

            break;
        }
        case jsbn::protoc::CommandID::Register_Req:
        {
            ptr = sProtocolData_ptr(CObjectAllocator<TRegisterRequest>::get_instance()->malloc(), delete_recv_page);
            ptr->command_id = jsbn::protoc::CommandID::Register_Req;

            ((TRegisterRequest*)ptr.get())->city_id = protocol->registerreq().cityid();

            LOG(INFO)<<"收到业务服务器注册请求,城市ID:"<< ((TRegisterRequest*)ptr.get())->city_id<<":"<<protocol->registerreq().cityid();

            break;
        }
        case jsbn::protoc::CommandID::Relay_Req:
        {
            ptr = sProtocolData_ptr(CObjectAllocator<TRelayRequest>::get_instance()->malloc(), delete_recv_page);
            ptr->command_id = jsbn::protoc::CommandID::Relay_Req;

            TRelayRequest*& pData = (TRelayRequest*)ptr.get();
            pData->clear();

            pData->dst_srv_type = protocol->relayreq().dstsrvtype();
            if(protocol->relayreq().has_cityid())
            {
                pData->city_id = protocol->relayreq().cityid();
            }
            else
            {
                pData->city_id = jsbn::protoc::CityID::CID_INIT;
            }
            assert(protocol->relayreq().relaymsg().length() > sizeof(pData->msg));
            ::memcpy(pData->msg, protocol->relayreq().relaymsg().c_str(), protocol->relayreq().relaymsg().length());

            break;
        }
        default:
        {
            LOG(ERROR)<<"通信协议不支持";
            break;
        }
    }

    return ptr;
}
