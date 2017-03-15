#include "stdafx.h"
#include "Func.h"
#include "Code.h"
//远程服务器上新视野的IP地址有多少位
#define IP_LEN 2

CString GetRandWord(DWORD n)//获取n个随机字母
{
	//srand((unsigned)time(NULL));
	int i;
	CString str;
	char c;
	int t;
	for (i = 0; i < n; i++)
	{
		t = rand() % 3;
		if (t>1)
		{
			t = 'a';
		}
		else
		{
			t = 'A';
		}
		c = t + rand() % 26;
		str = str + c;
	}
	return str;
}
DWORD GetRand(DWORD m, DWORD n)//m <= rand() % (n - m + 1) + m <= n
{
	//srand((unsigned)time(NULL));
	return rand() % (n - m + 1) + m;
}
DOUBLE GetRandZeroToOne()
{
	//srand((unsigned)time(NULL));
	return  (rand() % 10) / (float)10;//生成0-1间的随机数。
}
CString GetRandStr(DWORD m, DWORD n)//m <= rand() % (n - m + 1) + m <= n
{
	CString str;
	str.Format(TEXT("%d"), GetRand(m, n));
	return str;
}

CString UnipusIp;
CString GetString(DWORD id)//从资源中提取字符串
{
	CString ss;
	/*
	int c;
	c = LoadString(NULL, id, ss.GetBuffer(1024000), 1024000);
	ss.ReleaseBuffer();
	ss.Left(c);
	*/
	ss.LoadString(id);
	ss.Replace(TEXT("UnipusIp"), UnipusIp);
	return ss;
}
void SetUnipusIp(CString ip) {
	UnipusIp = ip;
}
CString GetUnipusIp() {
	return UnipusIp;
}

CString LoadResource(DWORD ID,CString type) {
	CString result;
	HINSTANCE hInstance = AfxFindResourceHandle(MAKEINTRESOURCE(ID), RT_RCDATA);    //资源的ID号  
	HRSRC hRes = FindResource(hInstance, MAKEINTRESOURCE(ID), type);    //type是资源的类型，一定要写对  
	HGLOBAL hResData = LoadResource(hInstance, hRes);
	void * lpvData = LockResource(hResData);

	result = (char*)lpvData;
	//int cbSize = SizeofResource(hInstance, hRes);
	return result;
}

CString SubString(CString s, CString head, CString tail)
{
	int iPos = s.Find(head);
	if (iPos == -1)return TEXT("");
	iPos += head.GetLength();
	int iPos1 = s.Find(tail, iPos);
	if (iPos1 == -1)return TEXT("");
	return s.Mid(iPos, iPos1 - iPos);
}
CString SubString(CString s, CString head, CString tail,DWORD &t)
{
	int iPos = s.Find(head, t);
	if (iPos == -1)return TEXT("");
	iPos += head.GetLength();
	int iPos1 = s.Find(tail, iPos);
	if (iPos1 == -1)return TEXT("");
	t = iPos1;
	return s.Mid(iPos, iPos1 - iPos);
}
long long getCurrentTime()
{
	long long time_last;
	time_last = time(NULL);     //总秒数  
	struct timeb t1;
	ftime(&t1);
	//CString strTime;
	//strTime.Format(_T("%lldms"), t1.time * 1000 + t1.millitm);  //总毫秒数  
	//OutputDebugString(strTime);
	return t1.time * 1000 + t1.millitm;
}
BOOL TestUserName(CString User, int n) {
	/*简单的限制每台电脑最多运行n个账号，防止有人卖软件
	还能使用返回真，不能使用返回假*/
	HKEY  hKey;
	CString KeyName;
	CStringArray ret;


	//打开注册表
	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\SKSoftware"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		return TRUE;
	}

	//查询当前所有已经用过的用户
	CString Value;
	DWORD dwSize;
	BYTE *data;
	DWORD lpType = REG_SZ;
	for (int i = 0; i < n; i++) {
		KeyName.Format(TEXT("%d"), i);

		data = new BYTE[256];
		dwSize = 256;
		
		//获取键值内容
		if (RegQueryValueEx(hKey, KeyName, NULL, &lpType, data, &dwSize) != ERROR_SUCCESS) {
			continue;
		}
		
		//获取到一个使用过的用户名
		Value.Format(TEXT("%s"), data);
		ret.Add(Value);

		delete[]data;
	}

	//RegCloseKey(hKey);

	for (int i = 0; i < ret.GetSize(); i++) {
		//如果已经被注册过,直接返回成功
		if (User == ret[i]) {
			RegCloseKey(hKey);
			return TRUE;
		}
		//注册表中没有，这是一个新用户
		if (i == ret.GetSize() - 1) {

			if (i == n - 1) {
				//超过了能够使用的最大用户数
				RegCloseKey(hKey);
				return FALSE;
			}
			else {
				//还能接受一个新用户
				break;
			}

		}
	}

	//在注册表中写入新用户的信息
	KeyName.Format(TEXT("%d"), ret.GetSize());

	RegSetValueEx(hKey, KeyName, NULL, REG_SZ,(BYTE*)User.GetBuffer(0), User.GetLength()*2+2);
	User.ReleaseBuffer();

	RegCloseKey(hKey);
	return TRUE;
}

BOOL GetBoolByRate(int rate) {
	/*rate：返回假的概率
	  rate: rate为整型，例如97%将有97%的概率返回假
	*/

	//srand((unsigned)time(NULL));
	if (rate > 100 || rate < 0)return FALSE;
	int n = rand() % 100;
	if (n > rate) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

CString simpleEncrypt(CString str) {
	 CString code = L"3yg945v6wnop70qcderxfbshijlztuma812k";
	 CString decode = L"n4d0qhtmcu5vi38k1x7fabjw2rsozeyg69pl";
	 int pos = 0;
	 CString ret;
	 for (int i = 0; i < str.GetLength(); i++) {
		 pos = code.Find(str.GetAt(i));
		 if (pos == -1)
			 continue;
		 ret = ret + decode.GetAt(pos);
	 }
	 return ret;

}
CString simpleDecrypt(CString str) {
	CString code = L"3yg945v6wnop70qcderxfbshijlztuma812k";
	CString decode = L"n4d0qhtmcu5vi38k1x7fabjw2rsozeyg69pl";
	int pos = 0;
	CString ret;
	for (int i = 0; i < str.GetLength(); i++) {
		pos = decode.Find(str.GetAt(i));
		if (pos == -1)
			continue;
		ret = ret + code.GetAt(pos);
	}
	return ret;

}

BOOL localAuthorize(CString activeCode,CString userName,CString &retIp)
{
	if (activeCode.GetLength() < 5) {
		return FALSE;
	}
	//IP验证
	//左边第一位为IP的加密次数
	CString ip;
	int num = _ttoi(activeCode.Left(1));
	ip = simpleDecrypt(activeCode.Mid(1, IP_LEN));
	for (int i = 0; i < num-1; i++) {
		ip=simpleDecrypt(ip);
	}
	if (_ttoi(ip) > 50 || _ttoi(ip) < 30) {
		//2016届为37,2017届为38，以此类推
		return FALSE;
	}
	//解码之后然后将授权码中保存的IP地址提取出来
	retIp = ip;

	//接下来是账号验证
	//取出账号的加密次数
	CString name;
	num = _ttoi(activeCode.Mid(3,1));
	name = simpleDecrypt(activeCode.Mid(4, activeCode.GetLength() - 4));
	for (int i = 0; i < num - 1; i++) {
		name = simpleDecrypt(name);
	}
	if (userName.Compare(name) == 0) {
		return TRUE;
	}

	return FALSE;
}
