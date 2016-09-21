#pragma once
#include "afxwin.h"
#include "ChatSock.h"
#include "StructType.h"

// CDlgLogin �Ի���

class CDlgLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLogin();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

	CChatSock *m_pChatSock;      //���ڵ�½ͨ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ID;
	CEdit m_PWD;
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnClose();
};
