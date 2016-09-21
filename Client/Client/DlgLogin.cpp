// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "DlgLogin.h"
#include "afxdialogex.h"
extern int flag_login; //��������һ���ⲿȫ�ֱ���

// CDlgLogin �Ի���

IMPLEMENT_DYNAMIC(CDlgLogin, CDialogEx)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID, m_ID);
	DDX_Control(pDX, IDC_EDIT_PWD, m_PWD);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CDlgLogin::OnBnClickedButtonLogin)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgLogin ��Ϣ�������


void CDlgLogin::OnBnClickedButtonLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString m_csID;
	CString m_csPWD;             //����ӵ�½�����ȡ�˺�������Ϣ

	m_ID.GetWindowText(m_csID);
	m_PWD.GetWindowText(m_csPWD);

		LOGIN LoginDate;

		memset((void *)&LoginDate, '\0', sizeof(LoginDate));
		
		//LoginDate����

		LoginDate.nType = 0;
		for (int i = 0;i < m_csID.GetLength();i++)
		{
			*(LoginDate.cID + i) = m_csID.GetAt(i);
		}
		for (int i = 0;i < m_csPWD.GetLength();i++)
		{
			*(LoginDate.cPWD + i) = m_csPWD.GetAt(i);
		}

		m_pChatSock->Send((void *)&LoginDate, sizeof(LoginDate));
}


void CDlgLogin::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	exit(0);
	CDialogEx::OnClose();
}
