// Server.cpp : 定义控制台应用程序的入口点。
//


#include "sh_common.h"
#include "sh_filelog.h"
#include "sh_dbsql.h"
#include "sh_include.h"
#include "sh_ptrlist.h"


struct SDbCfg
{
	sh::uint16	    wPort;
	std::string		strHost;
	std::string		strDBName;
	std::string		strUserName;
	std::string		strPassword;
};


int main()
{
    sh::IMySqlRealQuery* pRealMysql = sh::create_mysql_real_query();
    if (NULL == pRealMysql){
    assert(false);
    USER_LOG_FATAL("create real mysql fail");
    return 0;
    }

    SDbCfg cfg;
    cfg.wPort = 3306;
    cfg.strDBName = "z_all";
    cfg.strHost = "127.0.0.1";
    cfg.strUserName = "root";
    cfg.strPassword = "123456";
    if (!pRealMysql->init(cfg.strHost.c_str(), cfg.wPort, cfg.strUserName.c_str(), cfg.strPassword.c_str(), cfg.strDBName.c_str(), "utf8")){
    assert(false);
    USER_LOG_FATAL("init real mysql fail");
    return 0;
    }

    if (!pRealMysql->connect()){
    assert(false);
    USER_LOG_FATAL("connect real mysql fail");
    return 0;
    }

    char szSql[1024];
    const sh::int32 len = sh::safe_sprintf(szSql, "SELECT * FROM `tbl_idname` ");
    const bool r1 = pRealMysql->real_query(szSql, len);
    MYSQL_RES* select_result = pRealMysql->get_real_result();
    if (!r1 || NULL == select_result){
    assert(false);
    USER_LOG_INFO("import log select from `gs_dir` fail");
    return false;
    }

    for (MYSQL_ROW row = mysql_fetch_row(select_result); NULL != row; row = mysql_fetch_row(select_result)) {
    sh::int32 id = sh::a2i(row[0]);
    unsigned long *lengths = mysql_fetch_lengths(select_result);
    std::string s(row[1], lengths[1]);
    printf("real id=%d, s=%s \r\n", id, s.c_str());
    }
    free_mysql_real_query(pRealMysql);

    

   sh::CPool <SDbCfg>            m_DBEventPool; 
	printf("\r\ncommon test-----------------------------------------------------\r\n");

	system("pause");

	return 0;
}

