// ColorBox.cpp : implementation file
//

#include "stdafx.h"
#include "Offline editor.h"
#include "afxdialogex.h"
#include "Offline editorDlg.h"
#include  <atlconv.h>


// ColorBox dialog

IMPLEMENT_DYNAMIC(ColorBox, CDialogEx)

ColorBox::ColorBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COLORBOX, pParent)
{
	EnableActiveAccessibility();
}

ColorBox::~ColorBox()
{
}

void ColorBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDERR, sliderR);
	DDX_Control(pDX, IDC_COLORG, boxValueG);
	DDX_Control(pDX, IDC_SLIDERG, sliderG);
	DDX_Control(pDX, IDC_SLIDERB, sliderB);
	DDX_Control(pDX, IDC_COLORR, boxValueR);
	DDX_Control(pDX, IDC_COLORB, boxValueB);
	DDX_Control(pDX, IDC_LISTSPHERES, Spheres);
}


BEGIN_MESSAGE_MAP(ColorBox, CDialogEx)
	ON_EN_CHANGE(IDC_COLORR, &ColorBox::ScrollUpdateR)
	ON_EN_CHANGE(IDC_COLORG, &ColorBox::ScrollUpdateG)
	ON_EN_CHANGE(IDC_COLORB, &ColorBox::ScrollUpdateB)
	ON_EN_KILLFOCUS(IDC_COLORR, &ColorBox::UpdateBoxR)
	ON_EN_KILLFOCUS(IDC_COLORG, &ColorBox::UpdateBoxG)
	ON_EN_KILLFOCUS(IDC_COLORB, &ColorBox::UpdateBoxB)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERR, &ColorBox::UpdateBox)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERG, &ColorBox::UpdateBox)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERB, &ColorBox::UpdateBox)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDERR, &ColorBox::UpdateBox)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDERG, &ColorBox::UpdateBox)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDERB, &ColorBox::UpdateBox)
	ON_BN_CLICKED(ID_COLOROK, &ColorBox::OnBnClickedColorok)
	ON_LBN_DBLCLK(IDC_LISTSPHERES, &ColorBox::UpdateBox)
END_MESSAGE_MAP()

BOOL ColorBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	base = (COfflineeditorDlg*)this->GetAncestor(GA_ROOTOWNER);
	for (int i = 1; i < base->spheres.size(); i++)
	{
		Spheres.AddString(CString(to_string(i).c_str()));
	}
	sliderR.SetRange(0, 255);
	sliderG.SetRange(0, 255);
	sliderB.SetRange(0, 255);
	return TRUE;
}

// ColorBox message handlers

void ColorBox::ScrollUpdateR()
{
	wchar_t * buffer = new wchar_t[256];
	char* p;
	boxValueR.GetWindowTextW(buffer, boxValueR.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		int value = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			value = strtol(to.c_str(), nullptr, 36);
		}
		if (value > 255)
			value = 255;
		else if (value < 0)
			value = 0;

		sliderR.SetPos(value);
	}
}





void ColorBox::UpdateBox(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	switch (pNMHDR->idFrom)
	{
	case IDC_SLIDERR:
		boxValueR.SetWindowTextW(CString(to_string(sliderR.GetPos()).c_str()));
		break;
	case IDC_SLIDERG:
		boxValueG.SetWindowTextW(CString(to_string(sliderG.GetPos()).c_str()));
		break;
	case IDC_SLIDERB:
		boxValueB.SetWindowTextW(CString(to_string(sliderB.GetPos()).c_str()));
		break;
	}

	*pResult = 0;
}

void ColorBox::ScrollUpdateG()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueG.GetWindowTextW(buffer, boxValueG.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		int value = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			value = strtol(to.c_str(), nullptr, 36);
		}
		if (value > 255)
			value = 255;
		else if (value < 0)
			value = 0;

		sliderG.SetPos(value);
	}
}
void ColorBox::ScrollUpdateB()
{
	wchar_t * buffer = new wchar_t[256];
	char* p;
	boxValueB.GetWindowTextW(buffer, boxValueB.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		int value = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			value = strtol(to.c_str(), nullptr, 36);
		}
		if (value > 255)
			value = 255;
		else if (value < 0)
			value = 0;

		sliderB.SetPos(value);
	}
}
void ColorBox::UpdateBoxR()
{
	boxValueR.SetWindowTextW(CString(to_string(sliderR.GetPos()).c_str()));
}
void ColorBox::UpdateBoxG()
{
	boxValueG.SetWindowTextW(CString(to_string(sliderG.GetPos()).c_str()));
}
void ColorBox::UpdateBoxB()
{
	boxValueB.SetWindowTextW(CString(to_string(sliderB.GetPos()).c_str()));
}

void ColorBox::OnBnClickedColorok()
{
	if (selected != NULL && selected != LB_ERR)
	{
		base->spheres.at(selected)->data->red = (float)sliderR.GetPos();
		base->spheres.at(selected)->data->green = (float)sliderG.GetPos();
		base->spheres.at(selected)->data->blue = (float)sliderB.GetPos();
	}
	this->EndDialog(0);
}


void ColorBox::UpdateBox()
{
	selected = Spheres.GetCurSel() + 1;
	if (selected != NULL && selected != LB_ERR)
	{
		sliderR.SetPos(base->spheres.at(selected)->data->red);
		boxValueR.SetWindowTextW(CString(to_string(sliderR.GetPos()).c_str()));
		sliderG.SetPos(base->spheres.at(selected)->data->green);
		boxValueG.SetWindowTextW(CString(to_string(sliderG.GetPos()).c_str()));
		sliderB.SetPos(base->spheres.at(selected)->data->blue);
		boxValueB.SetWindowTextW(CString(to_string(sliderB.GetPos()).c_str()));
	}
}
