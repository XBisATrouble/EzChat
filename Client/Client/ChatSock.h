#pragma once

// CChatSock ����Ŀ��

class CChatSock : public CSocket
{
public:
	CChatSock(CWnd *m_pWnd);
	virtual ~CChatSock();

	virtual void OnReceive(int nErrorCode);

	CWnd *m_pMainDlg;
};


