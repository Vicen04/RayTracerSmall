// TransparencyBox.cpp : implementation file
//
#include "stdafx.h"
#include "Offline editor.h"
#include "afxdialogex.h"
#include "Offline editorDlg.h"


// TransparencyBox dialog

IMPLEMENT_DYNAMIC(TransparencyBox, CDialogEx)

TransparencyBox::TransparencyBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRANSPARENCYBOX, pParent)
{
	EnableActiveAccessibility();
}

TransparencyBox::~TransparencyBox()
{
}

void TransparencyBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TRANSPARENCY, boxValue);
	DDX_Control(pDX, IDC_LISTSPHERES, Spheres);
}


BEGIN_MESSAGE_MAP(TransparencyBox, CDialogEx)
	ON_BN_CLICKED(ID_TRANSPARENCYOK, &TransparencyBox::OnBnClickedok)
	ON_LBN_DBLCLK(IDC_LISTSPHERES, &TransparencyBox::UpdateBox2)
	ON_EN_KILLFOCUS(IDC_TRANSPARENCY, &TransparencyBox::UpdateBox)
END_MESSAGE_MAP()

BOOL TransparencyBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	base = (COfflineeditorDlg*)this->GetAncestor(GA_ROOTOWNER);
	for (int i = 1; i < base->spheres.size(); i++)
	{
		Spheres.AddString(CString(to_string(i).c_str()));
	}
	return TRUE;
}

void TransparencyBox::UpdateBox2()
{
	selected = Spheres.GetCurSel() + 1;
	if (selected != NULL && selected != LB_ERR)
		boxValue.SetWindowTextW(CString(to_string((int)base->spheres.at(selected)->data->transparency).c_str()));
}
void TransparencyBox::UpdateBox()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValue.GetWindowTextW(buffer, boxValue.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		value = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			value = strtol(to.c_str(), nullptr, 36);
		}
		if (value > 100)
			value = 100;
		else if (value < 0)
			value = 0;

		boxValue.SetWindowTextW(CString(to_string(value).c_str()));
	}
}

void TransparencyBox::OnBnClickedok()
{
	if (selected != NULL && selected != LB_ERR)
		base->spheres.at(selected)->data->transparency = (float)value;
	this->EndDialog(0);
}
