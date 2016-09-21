
// ServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "ChatSock.h"
#include "ListenSock.h"
#include "afxwin.h"


// CServerDlg �Ի���
class CServerDlg : public CDialogEx
{
// ����
public:
	CServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	CListenSock *m_pListenSock; //���ڼ���
	CList<CChatSock *, CChatSock *>m_pChatSock; //���ڽ���
	int AcceptClient();
	int RevMsg(CChatSock* pSock);
	int SendMsgToOne(char * cRevID, char * pMsg);
//	CString test;
	_SYSTEMTIME Time;
	bool compare(CString Cuser_name, CString Cuser_pass);
};
