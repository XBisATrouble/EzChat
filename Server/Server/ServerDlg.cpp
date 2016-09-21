
// ServerDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CServerDlg �Ի���



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


// CServerDlg ��Ϣ�������

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_pListenSock = new CListenSock(this);

	if (!AfxSocketInit())
	{
		MessageBox(_T("�׽��ִ���ʧ��!"));
		return FALSE;
	}

	if (m_pListenSock->Create(1024) == NULL) //�󶨶˿�
	{
		delete m_pListenSock;
		m_pListenSock = NULL;
		MessageBox(_T("�󶨶˿�ʧ��!"));
		return FALSE;
	}


	m_pListenSock->Listen();//��������




	//���������߿ͻ����б�
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);//����ѡ��
	m_list.InsertColumn(0, TEXT("���"), LVCFMT_LEFT, 160);
	m_list.InsertColumn(1, TEXT("�û���"), LVCFMT_LEFT, 200);
	m_list.InsertColumn(2, TEXT("����ʱ��"), LVCFMT_LEFT, 204);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CServerDlg::AcceptClient()
{
	CChatSock *pSocket = new CChatSock(this);

	if (!m_pListenSock->Accept(*pSocket))
	{
		MessageBox(_T("���ӿͻ���ʧ��"));
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
	int iBuffSize = 1024; //����һ�ν��ܶ೤������
	int DateMsg[1024]; //������ʱ�����洢���ܵ�����

	int iRes = pSock->Receive((char *)DateMsg, iBuffSize);

	if (iRes != SOCKET_ERROR)
	{

		//���ܵ�½��Ϣ
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

			//LoginDate����
			ReLoginDate.nType = compare(cID, cPWD);
			pSock->Send((void *)&ReLoginDate, sizeof(ReLoginDate));

			//���������߿ͻ�����ʾ
			if (ReLoginDate.nType == 1) {
				::GetLocalTime(&Time);//����ʱ��
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
		//���ܡ�����
		else if (DateMsg[0] == 1)
		{
			DATECHAT *m_chat;
			m_chat = (DATECHAT *)DateMsg;

			if (!m_chat->RevID)
			{
				if (!(SendMsgToOne(m_chat->RevID, (char *)DateMsg)))
				{
					//������Ϣ�Ľ��
					//�����ļ������е��˺ţ�������˺��Ƿ����
					//������ڣ�����Ϣ�ݴ棬������½ʱ����
					//���򣬷���ʧ�ܸ��ͻ���
				}
			}
		}
	}

	return 0;
}


int CServerDlg::SendMsgToOne(char * cRevID, char * pMsg)
{
	POSITION pPos = m_pChatSock.GetHeadPosition();//��ȡͷָ��
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
		if (in) // �и��ļ�  
		{
			while (getline(in, line)) // line�в�����ÿ�еĻ��з�  
			{
				buf[len] = line;
				len++;
			}
		}
		else // û�и��ļ�  
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
