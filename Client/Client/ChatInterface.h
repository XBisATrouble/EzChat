#pragma once
#include "afxwin.h"


// CChatInterface �Ի���

class CChatInterface : public CDialogEx
{
	DECLARE_DYNAMIC(CChatInterface)

public:
	CChatInterface(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChatInterface();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Input;
	CEdit m_Show;
};
