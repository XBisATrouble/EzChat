// ChatInterface.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ChatInterface.h"
#include "afxdialogex.h"


// CChatInterface 对话框

IMPLEMENT_DYNAMIC(CChatInterface, CDialogEx)

CChatInterface::CChatInterface(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHAT_DIALOG, pParent)
{

}

CChatInterface::~CChatInterface()
{
}

void CChatInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_Input);
	DDX_Control(pDX, IDC_EDIT_SHOW, m_Show);
}


BEGIN_MESSAGE_MAP(CChatInterface, CDialogEx)
END_MESSAGE_MAP()


// CChatInterface 消息处理程序