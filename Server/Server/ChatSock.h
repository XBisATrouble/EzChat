#pragma once

// CChatSock ����Ŀ��

class CChatSock : public CSocket
{
public:
	CChatSock(CWnd *pWnd);
	virtual ~CChatSock();

	CWnd *m_pMainDlg;
	virtual void OnReceive(int nErrorCode);

	char cID[10];
};


