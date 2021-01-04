// BackgroundColor.cpp : implementation file
//

#include "stdafx.h"
#include "Offline editor.h"
#include "BackgroundColor.h"
#include "afxdialogex.h"
#include "Offline editorDlg.h"
#include  <atlconv.h>


// BackgroundColor dialog

IMPLEMENT_DYNAMIC(BackgroundColor, CDialogEx)

BackgroundColor::BackgroundColor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COLORBOXBACGROUND, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

BackgroundColor::~BackgroundColor()
{
}

void BackgroundColor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDERR, sliderR);
	DDX_Control(pDX, IDC_COLORG, boxValueG);
	DDX_Control(pDX, IDC_SLIDERG, sliderG);
	DDX_Control(pDX, IDC_SLIDERB, sliderB);
	DDX_Control(pDX, IDC_COLORR, boxValueR);
	DDX_Control(pDX, IDC_COLORB, boxValueB);
}


BEGIN_MESSAGE_MAP(BackgroundColor, CDialogEx)
	ON_EN_CHANGE(IDC_COLORR, &BackgroundColor::ScrollUpdateR)
	ON_EN_CHANGE(IDC_COLORG, &BackgroundColor::ScrollUpdateG)
	ON_EN_CHANGE(IDC_COLORB, &BackgroundColor::ScrollUpdateB)
	ON_EN_KILLFOCUS(IDC_COLORR, &BackgroundColor::UpdateBoxR)
	ON_EN_KILLFOCUS(IDC_COLORG, &BackgroundColor::UpdateBoxG)
	ON_EN_KILLFOCUS(IDC_COLORB, &BackgroundColor::UpdateBoxB)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERR, &BackgroundColor::UpdateBox)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERG, &BackgroundColor::UpdateBox)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERB, &BackgroundColor::UpdateBox)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDERR, &BackgroundColor::UpdateBox)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDERG, &BackgroundColor::UpdateBox)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDERB, &BackgroundColor::UpdateBox)
	ON_BN_CLICKED(ID_COLOROK, &BackgroundColor::OnBnClickedColorok)
END_MESSAGE_MAP()


// BackgroundColor message handlers
BOOL BackgroundColor::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	base = (COfflineeditorDlg*)this->GetAncestor(GA_ROOTOWNER);
	sliderR.SetRange(0, 255);
	sliderG.SetRange(0, 255);
	sliderB.SetRange(0, 255);
	sliderR.SetPos(base->spheres.at(0)->data->red);
	boxValueR.SetWindowTextW(CString(to_string(sliderR.GetPos()).c_str()));
	sliderG.SetPos(base->spheres.at(0)->data->green);
	boxValueG.SetWindowTextW(CString(to_string(sliderG.GetPos()).c_str()));
	sliderB.SetPos(base->spheres.at(0)->data->blue);
	boxValueB.SetWindowTextW(CString(to_string(sliderB.GetPos()).c_str()));
	return TRUE;
}

// BackgroundColor message handlers

void BackgroundColor::ScrollUpdateR()
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





void BackgroundColor::UpdateBox(NMHDR *pNMHDR, LRESULT *pResult)
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

void BackgroundColor::ScrollUpdateG()
{
	wchar_t * buffer = new wchar_t[256];
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
void BackgroundColor::ScrollUpdateB()
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
void BackgroundColor::UpdateBoxR()
{
	boxValueR.SetWindowTextW(CString(to_string(sliderR.GetPos()).c_str()));
}
void BackgroundColor::UpdateBoxG()
{
	boxValueG.SetWindowTextW(CString(to_string(sliderG.GetPos()).c_str()));
}
void BackgroundColor::UpdateBoxB()
{
	boxValueB.SetWindowTextW(CString(to_string(sliderB.GetPos()).c_str()));
}

void BackgroundColor::OnBnClickedColorok()
{
	base->spheres.at(0)->data->red = sliderR.GetPos();
	base->spheres.at(0)->data->green = sliderG.GetPos();
	base->spheres.at(0)->data->blue = sliderB.GetPos();
	base->SetBackgroundColor(RGB(sliderR.GetPos(), sliderG.GetPos(), sliderB.GetPos()));
	this->EndDialog(0);
}
