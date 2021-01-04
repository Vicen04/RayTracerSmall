// ReflectionBox.cpp : implementation file
//

#include "stdafx.h"
#include "Offline editor.h"
#include "afxdialogex.h"
#include "Offline editorDlg.h"


// ReflectionBox dialog

IMPLEMENT_DYNAMIC(ReflectionBox, CDialogEx)

ReflectionBox::ReflectionBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REFLECTION, pParent)
{
	EnableActiveAccessibility();
}

ReflectionBox::~ReflectionBox()
{
}

void ReflectionBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REFLECTION, boxValue);
	DDX_Control(pDX, IDC_LISTSPHERES, Spheres);
}


BEGIN_MESSAGE_MAP(ReflectionBox, CDialogEx)
	ON_BN_CLICKED(ID_REFLECTIONOK, &ReflectionBox::OnBnClickedok)
	ON_LBN_DBLCLK(IDC_LISTSPHERES, &ReflectionBox::UpdateBox2)
	ON_EN_KILLFOCUS(IDC_REFLECTION, &ReflectionBox::UpdateBox)
END_MESSAGE_MAP()

BOOL ReflectionBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	base = (COfflineeditorDlg*)this->GetAncestor(GA_ROOTOWNER);
	for (int i = 1; i < base->spheres.size(); i++)
	{
		Spheres.AddString(CString(to_string(i).c_str()));
	}
	return TRUE;
}

void ReflectionBox::UpdateBox2()
{
	selected = Spheres.GetCurSel() + 1;
	if (selected != NULL && selected != LB_ERR)
		boxValue.SetWindowTextW(CString(to_string((int)base->spheres.at(selected)->data->reflection).c_str()));
}
void ReflectionBox::UpdateBox()
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

void ReflectionBox::OnBnClickedok()
{
	if (selected != NULL && selected != LB_ERR)
		base->spheres.at(selected)->data->reflection = (float)value;
	this->EndDialog(0);
}
