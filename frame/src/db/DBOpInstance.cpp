//
//  DBOpInstance.cpp
//  mysql++
//
//  Created by chenjianjun on 15/9/10.
//
//

#include "DBOpInstance.h"
#include "DBPool.h"

namespace NAME_SPACE {
    
    DBOpInstance* DBOpInstance::Instance() {
        static DBOpInstance instance;
        return &instance;
    }
    
    DBOpInstance::DBOpInstance():_p_db_pool(nullptr) {}
    
    DBOpInstance::~DBOpInstance() {}
    
    // 初期话连接信息
    bool DBOpInstance::EnvInit(std::string db_name,
                               std::string db_host,
                               std::string db_user,
                               std::string db_passwd,
                               unsigned short max_con_num,
                               unsigned short db_port) {
        
        if (_p_db_pool) {
            return true;
        }
        
        TDBParameter parameter;
        parameter.db_name = db_name;
        parameter.server_ip = db_host;
        parameter.server_port = db_port;
        parameter.password = db_passwd;
        parameter.user = db_user;
        parameter.max_con_num = max_con_num;
        
        _p_db_pool = new DBPool(parameter);
        if (nullptr == _p_db_pool) {
            return false;
        }
        
        return true;
    }
    
    void DBOpInstance::Exit() {
        
        if (!_p_db_pool) {
            return;
        }
        
        delete _p_db_pool;
        _p_db_pool = nullptr;
    }
    
    mysqlpp::ScopedConnection* DBOpInstance::GetConnect() {
        
        if (!_p_db_pool) {
            return nullptr;
        }

        return new mysqlpp::ScopedConnection(*_p_db_pool, true);
    }
    
}
