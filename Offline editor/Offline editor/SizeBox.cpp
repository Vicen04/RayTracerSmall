// SizeBox.cpp : implementation file
//

#include "stdafx.h"
#include "Offline editor.h"
#include "afxdialogex.h"
#include "Offline editorDlg.h"


// SizeBox dialog

IMPLEMENT_DYNAMIC(SizeBox, CDialogEx)

SizeBox::SizeBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIZEBOX, pParent)
{
	EnableActiveAccessibility();
}

SizeBox::~SizeBox()
{
}

void SizeBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SIZE, boxValue);
	DDX_Control(pDX, IDC_LISTSPHERES, Spheres);
}


BEGIN_MESSAGE_MAP(SizeBox, CDialogEx)
	ON_BN_CLICKED(ID_SIZEOK, &SizeBox::OnBnClickedok)
	ON_LBN_DBLCLK(IDC_LISTSPHERES, &SizeBox::UpdateBox2)
	ON_EN_KILLFOCUS(IDC_SIZE, &SizeBox::UpdateBox)
END_MESSAGE_MAP()

BOOL SizeBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	base = (COfflineeditorDlg*)this->GetAncestor(GA_ROOTOWNER);
	for (int i = 1; i < base->spheres.size(); i++)
	{
		Spheres.AddString(CString(to_string(i).c_str()));
	}
	return TRUE;
}

void SizeBox::UpdateBox2()
{
	selected = Spheres.GetCurSel() + 1;
	if (selected != NULL && selected != LB_ERR)
		boxValue.SetWindowTextW(CString(to_string((int)base->spheres.at(selected)->data->radius).c_str()));
}
void SizeBox::UpdateBox()
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
		if (value > 10)
			value = 10;
		else if (value < 1)
			value = 1;

		boxValue.SetWindowTextW(CString(to_string(value).c_str()));
	}
}

void SizeBox::OnBnClickedok()
{
	if (selected != NULL && selected != LB_ERR)
		base->spheres.at(selected)->data->radius = (float)value;
	this->EndDialog(0);
}

// SizeBox message handlers
