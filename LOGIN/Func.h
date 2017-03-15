/*
这里定义的是一些功能性函数
*/

#ifndef FUNC_H
#define FUNC_H

#include <afx.h>
#include<time.h>
#include<sys/timeb.h>

CString SubString(CString s, CString head, CString tail);		//截取字符串
CString SubString(CString s, CString head, CString tail,DWORD &t);	//从T开始找head，tail位置返回到t，用于持续寻找字符串

DOUBLE GetRandZeroToOne();		//0到1的随机数
DWORD GetRand(DWORD m, DWORD n);	//取随机数
CString GetRandStr(DWORD m, DWORD n);	//取随机数，只不过是返回值是字符串类型
CString GetRandWord(DWORD n);		//取长度为N的随机字母字符串

void SetUnipusIp(CString ip);		//与GetString配套使用，用于替换字符串里面的IP
CString GetUnipusIp();
CString GetString(DWORD id);		//从资源文件获取字符串
CString LoadResource(DWORD ID, CString type);	//从资源中加载指定类型的资源

long long getCurrentTime();		//获取现在到1970年1月1日的毫秒数
BOOL TestUserName(CString User, int n);	//设置一台电脑最多登录n的用户，如果超出，则返回假

BOOL GetBoolByRate(int rate);		//根据比率rate来随机的返回是否为真

CString simpleEncrypt(CString s);	//简单加密
CString simpleDecrypt(CString s);	//简单解密

BOOL localAuthorize(CString activeCode, CString userName, CString &retIp);//授权码的本地验证
#endif