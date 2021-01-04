// DeleteAnimation.cpp : implementation file
//

#include "stdafx.h"
#include "Offline editor.h"
#include "Offline editorDlg.h"
#include "afxdialogex.h"


// DeleteAnimation dialog

IMPLEMENT_DYNAMIC(DeleteAnimation, CDialogEx)

DeleteAnimation::DeleteAnimation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DELETEANIMATION, pParent)
{

}

DeleteAnimation::~DeleteAnimation()
{
}

void DeleteAnimation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSPHERES, Spheres);
	DDX_Control(pDX, IDC_NOSELECTED, TextNoSelected);
}


BEGIN_MESSAGE_MAP(DeleteAnimation, CDialogEx)
	ON_BN_CLICKED(ID_DELETE, &DeleteAnimation::OnBnClickedDelete)
	ON_LBN_DBLCLK(IDC_LISTSPHERES, &DeleteAnimation::Select)
END_MESSAGE_MAP()


// DeleteAnimation message handlers

BOOL DeleteAnimation::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	base = (COfflineeditorDlg*)this->GetAncestor(GA_ROOTOWNER);
	for (int i = 1; i < base->spheres.size(); i++)
	{
		Spheres.AddString(CString(to_string(i).c_str()));
	}
	return TRUE;
}

void DeleteAnimation::Select()
{
	selected = Spheres.GetCurSel() + 1;
	TextNoSelected.ShowWindow(SW_HIDE);
}

void DeleteAnimation::OnBnClickedDelete()
{
	if (selected != NULL && selected != LB_ERR && base->spheres.at(selected)->animation != nullptr)
	{
		delete base->spheres.at(selected)->animation;
		base->spheres.at(selected)->animation = NULL;

		this->EndDialog(0);
	}
	else
		TextNoSelected.ShowWindow(SW_SHOWNA);
}
