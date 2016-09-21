#pragma once
#include "afxwin.h"


// CChatInterface 对话框

class CChatInterface : public CDialogEx
{
	DECLARE_DYNAMIC(CChatInterface)

public:
	CChatInterface(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChatInterface();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Input;
	CEdit m_Show;
};
