#pragma once
#include "afxwin.h"
#include "ChatSock.h"
#include "StructType.h"

// CDlgLogin 对话框

class CDlgLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLogin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

	CChatSock *m_pChatSock;      //用于登陆通信
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ID;
	CEdit m_PWD;
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnClose();
};
