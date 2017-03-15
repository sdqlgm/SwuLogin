
// LOGINDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LOGIN.h"
#include "LOGINDlg.h"
#include "afxdialogex.h"
#include "HttpClient.h"
#include "Func.h"
#include "Code.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void getLoginInfo();

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLOGINDlg 对话框



CLOGINDlg::CLOGINDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLOGINDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_Button);
	DDX_Control(pDX, IDC_EDIT1, m_username);
	DDX_Control(pDX, IDC_EDIT2, m_password);
}

BEGIN_MESSAGE_MAP(CLOGINDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLOGINDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLOGINDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CLOGINDlg 消息处理程序

BOOL CLOGINDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	getLoginInfo();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLOGINDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLOGINDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLOGINDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HttpClient httpClient;

CString username = L"";
CString password = L"";

CString postData = L"";


//从注册表中读取用户名和密码到username和password
void getLoginInfo() {
	HKEY  hKey;
	CString KeyName;
	CStringArray ret;


	//打开注册表
	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\SwuLogin"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		return;
	}


	DWORD lpType = REG_SZ;
	BYTE *data = new BYTE[256];
	DWORD dwSize;
	CString value;

	//获取用户名
	dwSize = 256;
	KeyName = L"username";
	if (RegQueryValueEx(hKey, KeyName, NULL, &lpType, data, &dwSize) != ERROR_SUCCESS) {
		return;
	}
	value.Format(TEXT("%s"), data);
	AfxGetMainWnd()->GetDlgItem(IDC_EDIT1)->SetWindowText(value);
	UpdateWindow(AfxGetMainWnd()->GetDlgItem(IDC_EDIT1)->m_hWnd);

	
	//获取密码
	dwSize = 256;
	KeyName = L"password";
	if (RegQueryValueEx(hKey, KeyName, NULL, &lpType, data, &dwSize) != ERROR_SUCCESS) {
		return;
	}
	value.Format(TEXT("%s"), data);
	AfxGetMainWnd()->GetDlgItem(IDC_EDIT2)->SetWindowText(value);
	UpdateWindow(AfxGetMainWnd()->GetDlgItem(IDC_EDIT2)->m_hWnd);

	delete[]data;
	RegCloseKey(hKey);
}

//将登录信息保存到注册表
void setLoginInfo() {
	HKEY  hKey;
	CString KeyName;
	CStringArray ret;


	//打开注册表
	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\SWULOGIN"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		return;
	}

	DWORD lpType = REG_SZ;
	BYTE *data;
	DWORD dwSize;

	KeyName = L"username";
	RegSetValueEx(hKey, KeyName, NULL, REG_SZ, (BYTE*)username.GetBuffer(0), username.GetLength() * 2 + 2);
	username.ReleaseBuffer();

	KeyName = L"password";
	RegSetValueEx(hKey, KeyName, NULL, REG_SZ, (BYTE*)password.GetBuffer(0), password.GetLength() * 2 + 2);
	password.ReleaseBuffer();

	RegCloseKey(hKey);
}


//因为这一步很耗时间，所以单独提取出来共用
BOOL getPostData() {
	CString queryString = UrlEncode(UrlEncode(L"wlanuserip=7fe8068476a9ae5287fa52adf9118d6b&wlanacname=d3fd3003b8a92e5a0d9c924efc713c22&ssid=&nasip=f2267a27304a35841a4b2f3bbdcef5e6&snmpagentip=&mac=3eaf0c9c666b678946730b48dfc2c202&t=wireless-v2&url=bc769469379bc92a49dd39c8187326462c2c594662118267&apmac=&nasid=d3fd3003b8a92e5a0d9c924efc713c22&vid=622c44f245fcc3db&port=b7937cfdf5aa03ef&nasportid=136985ff42ef1c4528a45c84a073ddb8103c7c30674361d055125e5a7a865d356473378537f0ced6"));
	postData = L"userId=" + username + L"&password=" + password + L"&service=%25E9%25BB%2598%25E8%25AE%25A4&queryString=" + queryString + L"&operatorPwd=&operatorUserId=&validcode=";
	return TRUE;

	/*
	//获取登录地址
	CString ret = httpClient.Get(L"http://123.123.123.123");
	CString addr = SubString(ret, L"<script>top.self.location.href='", L"</script>");
	CString queryString = SubString(addr, L"http://222.198.127.170/eportal/index.jsp?", L"'");

	//该登录地址包含很多信息，需要将其URL编码两次作为登录时候的post信息
	queryString = UrlEncode(UrlEncode(queryString));

	if (queryString.CompareNoCase(L"") == 0) {
		AfxMessageBox(L"获取登录地址失败，请检查是否能访问校园网：login.swu.edu.cn", MB_ICONERROR);
		return FALSE;
	}

	//拼装登录信息
	postData = L"userId=" + username + L"&password=" + password + L"&service=%25E9%25BB%2598%25E8%25AE%25A4&queryString=" + queryString + L"&operatorPwd=&operatorUserId=&validcode=";
	OutputDebugString(postData);
	return TRUE;*/
}

//登录
void login() {
	getPostData();

	CString loginRet = httpClient.Post(L"http://222.198.127.170/eportal/InterFace.do?method=login", postData);


	if (SubString(loginRet, L"result\":\"", L"\"").CompareNoCase(L"success") != 0) {
		AfxMessageBox(L"登录失败，可能是用户名或密码错误！", MB_ICONERROR);
		return;
	}

	setLoginInfo();
	
}

//退出登录
void logout() {
	httpClient.Get(L"http://login.swu.edu.cn/");
	httpClient.Get(L"http://login.swu.edu.cn/eportal/gologout.jsp");
	CString url = httpClient.GetRecvHeader(L"Location");

	url = url + L"&";
	CString userIndex = SubString(url, L"userIndex=", L"&");
	if (url.Compare(L"") == 0) {
		return;
	}
	httpClient.Post(L"http://login.swu.edu.cn/eportal/InterFace.do?method=logout", L"userIndex=" + userIndex);
}

//自动线程
bool isContinue = false;
int now = 0;
DWORD WINAPI DoThread(LPVOID pParam) {
	while (true) {
		if (isContinue == false) {
			return 0;
		}
		now = now + 1;
		int minutes = now / 60;
		if (minutes > 10) {
			logout();
			login();
			now = 0;
		}

		Sleep(1000);
	}
}


void CLOGINDlg::OnBnClickedButton1()
{
	CString _username;
	CString _password;

	m_username.GetWindowText(_username);
	m_password.GetWindowText(_password);
	_username.Replace(L" ", L"");

	if (_username.CompareNoCase(L"") == 0 || _password.CompareNoCase(L"") == 0) {
		AfxMessageBox(L"用户名或密码不能为空！", MB_ICONERROR);
		return;
	}
	username = _username;
	password = _password;
	

	CString txt;
	m_Button.GetWindowText(txt);
	if (txt.Compare(L"已暂停") == 0) {
		//先获取一次登录信息
		if (getPostData() == FALSE) {
			return;
		}

		isContinue = true;
		AfxBeginThread((AFX_THREADPROC)DoThread, NULL);
		m_Button.SetWindowText(L"已开始");
	}
	else {
		isContinue = false;
		m_Button.SetWindowText(L"已暂停");
	}

}

void CLOGINDlg::OnBnClickedButton2()
{
	CString _username;
	CString _password;

	m_username.GetWindowText(_username);
	m_password.GetWindowText(_password);
	_username.Replace(L" ", L"");

	if (_username.CompareNoCase(L"") == 0 || _password.CompareNoCase(L"") == 0) {
		AfxMessageBox(L"用户名或密码不能为空！", MB_ICONERROR);
		return;
	}
	username = _username;
	password = _password;

	if (getPostData() == FALSE) {
		return;
	}

	logout();
	login();

}
