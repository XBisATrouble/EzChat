
// ServerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "ChatSock.h"
#include "ListenSock.h"
#include "afxwin.h"


// CServerDlg 对话框
class CServerDlg : public CDialogEx
{
// 构造
public:
	CServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
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
	CListCtrl m_list;
	CListenSock *m_pListenSock; //用于监听
	CList<CChatSock *, CChatSock *>m_pChatSock; //用于交流
	int AcceptClient();
	int RevMsg(CChatSock* pSock);
	int SendMsgToOne(char * cRevID, char * pMsg);
//	CString test;
	_SYSTEMTIME Time;
	bool compare(CString Cuser_name, CString Cuser_pass);
};
