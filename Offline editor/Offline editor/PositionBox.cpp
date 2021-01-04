// PositionBox.cpp : implementation file
//

#include "stdafx.h"
#include "Offline editor.h"
#include "PositionBox.h"
#include "afxdialogex.h"
#include "Offline editorDlg.h"
#include  <atlconv.h>

// PositionBox dialog

IMPLEMENT_DYNAMIC(PositionBox, CDialogEx)

PositionBox::PositionBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POSITIONBOX, pParent)
{
	EnableActiveAccessibility();
}

PositionBox::~PositionBox()
{
}

void PositionBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_POSX, boxValueX);
	DDX_Control(pDX, IDC_POSY, boxValueY);
	DDX_Control(pDX, IDC_POSZ, boxValueZ);
	DDX_Control(pDX, IDC_LISTSPHERES, Spheres);
}


BEGIN_MESSAGE_MAP(PositionBox, CDialogEx)
	ON_EN_KILLFOCUS(IDC_POSX, &PositionBox::UpdateBoxX)
	ON_EN_KILLFOCUS(IDC_POSY, &PositionBox::UpdateBoxY)
	ON_EN_KILLFOCUS(IDC_POSZ, &PositionBox::UpdateBoxZ)
	ON_LBN_DBLCLK(IDC_LISTSPHERES, &PositionBox::UpdateBox)
	ON_BN_CLICKED(ID_POSITIONOK, &PositionBox::OnBnClickedPositionok)
END_MESSAGE_MAP()


BOOL PositionBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	base = (COfflineeditorDlg*)this->GetAncestor(GA_ROOTOWNER);
	for (int i = 1; i < base->spheres.size(); i++)
	{
		Spheres.AddString(CString(to_string(i).c_str()));
	}
	return TRUE;
}

void PositionBox::UpdateBox()
{
	selected = Spheres.GetCurSel() + 1;
	if (selected != NULL && selected != LB_ERR)
	{
		boxValueX.SetWindowTextW(CString(to_string((int)base->spheres.at(selected)->data->posX).c_str()));
		boxValueY.SetWindowTextW(CString(to_string((int)base->spheres.at(selected)->data->posY).c_str()));
		boxValueZ.SetWindowTextW(CString(to_string((int)base->spheres.at(selected)->data->posZ).c_str()));
	}
}

void PositionBox::UpdateBoxX()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueX.GetWindowTextW(buffer, boxValueX.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		valueX = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			valueX = strtol(to.c_str(), nullptr, 36);
		}
		if (valueX > 20)
			valueX = 20;
		else if (valueX < -20)
			valueX = -20;

		boxValueX.SetWindowTextW(CString(to_string(valueX).c_str()));
	}
}
void PositionBox::UpdateBoxY()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueY.GetWindowTextW(buffer, boxValueY.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		valueY = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			valueY = strtol(to.c_str(), nullptr, 36);
		}
		if (valueY > 20)
			valueY = 20;
		else if (valueY < -20)
			valueY = -20;

		boxValueY.SetWindowTextW(CString(to_string(valueY).c_str()));
	}
}
void PositionBox::UpdateBoxZ()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueZ.GetWindowTextW(buffer, boxValueZ.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		valueZ = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			valueZ = strtol(to.c_str(), nullptr, 36);
		}
		if (valueZ > -30)
			valueZ = -30;
		else if (valueZ < -300)
			valueZ = -300;

		boxValueZ.SetWindowTextW(CString(to_string(valueZ).c_str()));
	}
}

void PositionBox::OnBnClickedPositionok()
{
	if (selected != NULL && selected != LB_ERR)
	{
		base->spheres.at(selected)->data->posX = (float)valueX;
		base->spheres.at(selected)->data->posY= (float)valueY;
		base->spheres.at(selected)->data->posZ = (float)valueZ;
	}
	this->EndDialog(0);
}
