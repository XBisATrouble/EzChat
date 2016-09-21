// ListenSock.cpp : 实现文件
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


// CListenSock 成员函数


void CListenSock::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	((CServerDlg *)m_pMainDlg)->AcceptClient();

	CSocket::OnAccept(nErrorCode);
}
