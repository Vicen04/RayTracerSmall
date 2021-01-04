// AboutBox.cpp : implementation file
//

#include "stdafx.h"
#include "Offline editor.h"
#include "AboutBox.h"
#include "afxdialogex.h"


// AboutBox dialog

IMPLEMENT_DYNAMIC(AboutBox, CDialogEx)

AboutBox::AboutBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ABOUTBOX, pParent)
{
	EnableActiveAccessibility();
}

AboutBox::~AboutBox()
{
}

void AboutBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutBox, CDialogEx)
END_MESSAGE_MAP()


// AboutBox message handlers
