
// LOGINDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CLOGINDlg 对话框
class CLOGINDlg : public CDialogEx
{
// 构造
public:
	CLOGINDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton m_Button;
	afx_msg void OnBnClickedButton2();
	CEdit m_username;
	CEdit m_password;

};
