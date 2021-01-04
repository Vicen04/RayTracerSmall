// Instructions.cpp : implementation file
//

#include "stdafx.h"
#include "Offline editor.h"
#include "Instructions.h"
#include "afxdialogex.h"


// Instructions dialog

IMPLEMENT_DYNAMIC(Instructions, CDialogEx)

Instructions::Instructions(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSTRUCTIONS, pParent)
{

}

Instructions::~Instructions()
{
}

void Instructions::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Instructions, CDialogEx)
END_MESSAGE_MAP()


// Instructions message handlers
