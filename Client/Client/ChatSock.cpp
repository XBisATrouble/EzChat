// ChatSock.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "ChatSock.h"
#include "ClientDlg.h"


// CChatSock

CChatSock::CChatSock(CWnd *m_pWnd)
{
	m_pMainDlg = m_pWnd;
}

CChatSock::~CChatSock()
{
}


// CChatSock ��Ա����


void CChatSock::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	((CClientDlg *)m_pMainDlg)->RevMsg();
	CSocket::OnReceive(nErrorCode);
}
