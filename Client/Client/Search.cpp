// Search.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "Search.h"
#include "afxdialogex.h"


// CSearch �Ի���

IMPLEMENT_DYNAMIC(CSearch, CDialogEx)

CSearch::CSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEARCH_DIALOG, pParent)
{

}

CSearch::~CSearch()
{
}

void CSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_Search);
	DDX_Control(pDX, IDC_LIST_RESULT, m_Result);
}


BEGIN_MESSAGE_MAP(CSearch, CDialogEx)
END_MESSAGE_MAP()


// CSearch ��Ϣ�������
