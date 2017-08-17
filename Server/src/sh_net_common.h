//////////////////////////////////////////////////////////
// initsock.h文件

#include <sh_include.h>
#include "sh_filelog.h"


class CInitSock		
{
public:
	CInitSock(BYTE minorVer = 2, BYTE majorVer = 2)
	{
		// 初始化WS2_32.dll
		WSADATA wsaData;
		WORD sockVersion = MAKEWORD(minorVer, majorVer);
		if(::WSAStartup(sockVersion, &wsaData) != 0){
			USER_LOG_FATAL("init sock version fail" << minorVer<<"majorver:"<<majorVer);
			assert(false);
			exit(0);
		}
	}
	~CInitSock()
	{	
		::WSACleanup();	
	}
};
