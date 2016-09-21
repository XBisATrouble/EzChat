
// ServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include "StructType.h"
#include <iostream>  
#include <iomanip>  
#include <fstream> 
#include <map>
#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerDlg 对话框



CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USER, m_list);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CServerDlg 消息处理程序

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_pListenSock = new CListenSock(this);

	if (!AfxSocketInit())
	{
		MessageBox(_T("套接字创建失败!"));
		return FALSE;
	}

	if (m_pListenSock->Create(1024) == NULL) //绑定端口
	{
		delete m_pListenSock;
		m_pListenSock = NULL;
		MessageBox(_T("绑定端口失败!"));
		return FALSE;
	}


	m_pListenSock->Listen();//启动监听




	//主界面在线客户端列表
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);//整行选择
	m_list.InsertColumn(0, TEXT("序号"), LVCFMT_LEFT, 160);
	m_list.InsertColumn(1, TEXT("用户名"), LVCFMT_LEFT, 200);
	m_list.InsertColumn(2, TEXT("上线时间"), LVCFMT_LEFT, 204);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CServerDlg::AcceptClient()
{
	CChatSock *pSocket = new CChatSock(this);

	if (!m_pListenSock->Accept(*pSocket))
	{
		MessageBox(_T("链接客户端失败"));
		delete pSocket;
		pSocket = NULL;
	}
	else
	{
		m_pChatSock.AddTail(pSocket);
	}
	return 0;
}


int CServerDlg::RevMsg(CChatSock* pSock)
{
	int iBuffSize = 1024; //定义一次接受多长的数据
	int DateMsg[1024]; //定义临时变量存储接受的数据

	int iRes = pSock->Receive((char *)DateMsg, iBuffSize);

	if (iRes != SOCKET_ERROR)
	{

		//接受登陆信息
		if (DateMsg[0] == 0)
		{
			LOGIN *m_login;
			m_login = (LOGIN *)DateMsg;
			strcpy(pSock->cID, m_login->cID);
			char *chcID = m_login->cID;
			char *chcPWD = m_login->cPWD;
			CString cID(chcID);
			CString cPWD(chcPWD);
			
			LOGIN ReLoginDate;

			memset((void *)&ReLoginDate, '\0', sizeof(ReLoginDate));

			//LoginDate数据
			ReLoginDate.nType = compare(cID, cPWD);
			pSock->Send((void *)&ReLoginDate, sizeof(ReLoginDate));

			//主界面在线客户端显示
			if (ReLoginDate.nType == 1) {
				::GetLocalTime(&Time);//本地时间
				CString TIME;
				TIME.Format(_T("[%d-%d-%d %d:%d:%d] "),
					Time.wYear, Time.wMonth, Time.wDay,
					Time.wHour, Time.wMinute, Time.wSecond);
				int n = 0;

				m_list.InsertItem(n, _T("1"));
				m_list.SetItemText(n, 1, cID);
				m_list.SetItemText(n, 2, TIME);
				n++;
			}
			//
		}
		//接受。。。
		else if (DateMsg[0] == 1)
		{
			DATECHAT *m_chat;
			m_chat = (DATECHAT *)DateMsg;

			if (!m_chat->RevID)
			{
				if (!(SendMsgToOne(m_chat->RevID, (char *)DateMsg)))
				{
					//离线信息的解决
					//遍历文件内所有的账号，看这个账号是否存在
					//如果存在，将消息暂存，当它登陆时发送
					//否则，返回失败给客户端
				}
			}
		}
	}

	return 0;
}


int CServerDlg::SendMsgToOne(char * cRevID, char * pMsg)
{
	POSITION pPos = m_pChatSock.GetHeadPosition();//获取头指针
	CChatSock *pSock;
	while (pPos)
	{
		pSock = m_pChatSock.GetAt(pPos);
		if (strcpy(pSock->cID, cRevID)) {
			pSock->Send(pMsg, sizeof(&pMsg) + 1);
		}
		m_pChatSock.GetNext(pPos);
	}

	return 0;
}


bool CServerDlg::compare(CString Cuser_name, CString Cuser_pass)
{
		string user_name = (CStringA)Cuser_name;
		string user_pass = (CStringA)Cuser_pass;
		ifstream in("User_Data.txt");
		string filename;
		string line;
		string buf[1000];
		int len = 0;
		if (in) // 有该文件  
		{
			while (getline(in, line)) // line中不包括每行的换行符  
			{
				buf[len] = line;
				len++;
			}
		}
		else // 没有该文件  
		{
			cout << "no such file" << endl;
		}

		map<string, string> mymap;

		for (int n = 0;n < len;n = n + 2)
		{
			mymap.insert(make_pair(buf[n], buf[n + 1]));
		}

		int flag = 0;
		map<string, string>::const_iterator it;
		for (it = mymap.begin(); it != mymap.end(); ++it) {
			if (it->first == user_name) {
				flag++;
				return (it->second == user_pass);
				break;
			}
		}
		if (flag == 0) {
			return false;
		}
	}
