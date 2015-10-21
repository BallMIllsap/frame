///************************************************************
/// @Copyright (C), 1993-2022, jsbn  Information Technologies Co., Ltd.
/// @URL
/// @file           module_data_center.h
/// @brief          数据存取中心
/// @attention
/// @Author         chenjianjun
/// @Version        0.1
/// @Date           2015年09月16日
/// @Description
/// @History
///************************************************************
#ifndef __MODULE_DATA_CENTER_H_
#define __MODULE_DATA_CENTER_H_

#include "module_const_def.h"
#include "./communicate/protoc/protocol_struct.h"

class ModuleDataCenter
{
public:

    /// @brief 获取类的唯一实例
    static ModuleDataCenter* Instance();

    /// @brief 析构函数
    virtual ~ModuleDataCenter();

    // 协议数据投放获取操作
    int PutProtocolData(sProtocolData_ptr&);
    sProtocolData_ptr GetProtocolData(unsigned long max_time_inMS = 1000);

protected:
    ModuleDataCenter();
    void operator=(const ModuleDataCenter&);
    ModuleDataCenter(const ModuleDataCenter&);

private:
    // 接收数据锁
    jsbn::CriticalSection _recv_critical_section;
    jsbn::ConditionVariable* _recv_cond_variable;
    CList<sProtocolData_ptr> _recv_data_lists;
};

#endif //__MODULE_DATA_CENTER_H_


