// DeleteSphere.cpp : implementation file
//

#include "stdafx.h"
#include "Offline editor.h"
#include "Offline editorDlg.h"
#include "afxdialogex.h"


// DeleteSphere dialog

IMPLEMENT_DYNAMIC(DeleteSphere, CDialogEx)

DeleteSphere::DeleteSphere(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DELETESPHERE, pParent)
{

}

DeleteSphere::~DeleteSphere()
{
}

void DeleteSphere::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSPHERES, Spheres);
	DDX_Control(pDX, IDC_NOSELECTED, TextNoSelected);
}


BEGIN_MESSAGE_MAP(DeleteSphere, CDialogEx)
	ON_BN_CLICKED(ID_DELETE, &DeleteSphere::OnBnClickedDelete)
	ON_LBN_DBLCLK(IDC_LISTSPHERES, &DeleteSphere::Select)
END_MESSAGE_MAP()


// DeleteSphere message handlers

BOOL DeleteSphere::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	base = (COfflineeditorDlg*)this->GetAncestor(GA_ROOTOWNER);
	for (int i = 1; i < base->spheres.size(); i++)
	{
		Spheres.AddString(CString(to_string(i).c_str()));
	}
	return TRUE;
}

void DeleteSphere::Select()
{
	selected = Spheres.GetCurSel() + 1;
	TextNoSelected.ShowWindow(SW_HIDE);
}

void DeleteSphere::OnBnClickedDelete()
{
	if (selected != NULL && selected != LB_ERR)
	{
		delete base->spheres.at(selected)->data;
		if (base->spheres.at(selected)->animation != nullptr)
			delete base->spheres.at(selected)->animation;
		delete base->spheres.at(selected);
		iter_swap(base->spheres.at(selected), base->spheres.at(base->spheres.size() - 1));
		base->spheres.pop_back();

		this->EndDialog(0);
	}
	else
		TextNoSelected.ShowWindow(SW_SHOWNA);
}
