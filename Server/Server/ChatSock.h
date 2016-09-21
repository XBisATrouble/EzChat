#pragma once

// CChatSock ÃüÁîÄ¿±ê

class CChatSock : public CSocket
{
public:
	CChatSock(CWnd *pWnd);
	virtual ~CChatSock();

	CWnd *m_pMainDlg;
	virtual void OnReceive(int nErrorCode);

	char cID[10];
};


