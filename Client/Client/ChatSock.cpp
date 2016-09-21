// ChatSock.cpp : 实现文件
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


// CChatSock 成员函数


void CChatSock::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	((CClientDlg *)m_pMainDlg)->RevMsg();
	CSocket::OnReceive(nErrorCode);
}
