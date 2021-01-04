// Saved.cpp : implementation file
//

#include "stdafx.h"
#include "Offline editor.h"
#include "Saved.h"
#include "afxdialogex.h"


// Saved dialog

IMPLEMENT_DYNAMIC(Saved, CDialogEx)

Saved::Saved(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SAVED, pParent)
{

}

Saved::~Saved()
{
}

void Saved::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Saved, CDialogEx)
END_MESSAGE_MAP()


// Saved message handlers
