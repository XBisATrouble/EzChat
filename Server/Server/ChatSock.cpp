// ChatSock.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "ChatSock.h"
#include "ServerDlg.h"


// CChatSock

CChatSock::CChatSock(CWnd *pWnd)
{
	m_pMainDlg = pWnd;
}

CChatSock::~CChatSock()
{
}


// CChatSock ��Ա����


void CChatSock::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	//�첽���շ��������
	AsyncSelect(FD_READ);

	((CServerDlg *)m_pMainDlg)->RevMsg(this);

	CSocket::OnReceive(nErrorCode);
}
