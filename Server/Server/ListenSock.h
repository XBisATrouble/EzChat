#pragma once

// CListenSock ÃüÁîÄ¿±ê

class CListenSock : public CSocket
{
public:
	CListenSock(CWnd *pWnd);
	virtual ~CListenSock();
	virtual void OnAccept(int nErrorCode);

	CWnd *m_pMainDlg;
};


