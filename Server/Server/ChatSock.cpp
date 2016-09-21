// ChatSock.cpp : 实现文件
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


// CChatSock 成员函数


void CChatSock::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	//异步接收服务端数据
	AsyncSelect(FD_READ);

	((CServerDlg *)m_pMainDlg)->RevMsg(this);

	CSocket::OnReceive(nErrorCode);
}
