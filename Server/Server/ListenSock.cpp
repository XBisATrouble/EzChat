// ListenSock.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "ListenSock.h"
#include "ServerDlg.h"

// CListenSock

CListenSock::CListenSock(CWnd *pWnd)
{
	m_pMainDlg = pWnd;
}

CListenSock::~CListenSock()
{
}


// CListenSock ��Ա����


void CListenSock::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	((CServerDlg *)m_pMainDlg)->AcceptClient();

	CSocket::OnAccept(nErrorCode);
}
