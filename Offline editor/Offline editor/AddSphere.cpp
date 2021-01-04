// AddSphere.cpp : implementation file
//

#include "stdafx.h"
#include "Offline editor.h"
#include "Offline editorDlg.h"
#include  <atlconv.h>
#include "afxdialogex.h"


// AddSphere dialog

IMPLEMENT_DYNAMIC(AddSphere, CDialogEx)

AddSphere::AddSphere(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDSPHERE, pParent)
{
	EnableActiveAccessibility();
}

AddSphere::~AddSphere()
{
}

void AddSphere::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDERR, sliderR);
	DDX_Control(pDX, IDC_COLORG, boxValueG);
	DDX_Control(pDX, IDC_SLIDERG, sliderG);
	DDX_Control(pDX, IDC_SLIDERB, sliderB);
	DDX_Control(pDX, IDC_COLORR, boxValueR);
	DDX_Control(pDX, IDC_COLORB, boxValueB);
	DDX_Control(pDX, IDC_POSX, boxValueX);
	DDX_Control(pDX, IDC_POSY, boxValueY);
	DDX_Control(pDX, IDC_POSZ, boxValueZ);
	DDX_Control(pDX, IDC_TRANSPARENCY, boxValueTr);
	DDX_Control(pDX, IDC_REFLECTION, boxValueRef);
	DDX_Control(pDX, IDC_SIZE, boxValueRad);
	DDX_Control(pDX, IDC_WARNING, TextWarning);
}


BEGIN_MESSAGE_MAP(AddSphere, CDialogEx)
	ON_EN_CHANGE(IDC_COLORR, &AddSphere::ScrollUpdateR)
	ON_EN_CHANGE(IDC_COLORG, &AddSphere::ScrollUpdateG)
	ON_EN_CHANGE(IDC_COLORB, &AddSphere::ScrollUpdateB)
	ON_EN_KILLFOCUS(IDC_COLORR, &AddSphere::UpdateBoxR)
	ON_EN_KILLFOCUS(IDC_COLORG, &AddSphere::UpdateBoxG)
	ON_EN_KILLFOCUS(IDC_COLORB, &AddSphere::UpdateBoxB)
	ON_EN_KILLFOCUS(IDC_SIZE, &AddSphere::UpdateBoxRad)
	ON_EN_KILLFOCUS(IDC_TRANSPARENCY, &AddSphere::UpdateBoxTr)
	ON_EN_KILLFOCUS(IDC_REFLECTION, &AddSphere::UpdateBoxRef)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERR, &AddSphere::UpdateBox)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERG, &AddSphere::UpdateBox)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERB, &AddSphere::UpdateBox)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDERR, &AddSphere::UpdateBox)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDERG, &AddSphere::UpdateBox)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDERB, &AddSphere::UpdateBox)
	ON_EN_KILLFOCUS(IDC_POSX, &AddSphere::UpdateBoxX)
	ON_EN_KILLFOCUS(IDC_POSY, &AddSphere::UpdateBoxY)
	ON_EN_KILLFOCUS(IDC_POSZ, &AddSphere::UpdateBoxZ)
	ON_BN_CLICKED(ID_ADDOK, &AddSphere::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL AddSphere::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	base = (COfflineeditorDlg*)this->GetAncestor(GA_ROOTOWNER);
	sliderR.SetRange(0, 255);
	sliderG.SetRange(0, 255);
	sliderB.SetRange(0, 255);
	R = G = B = X = Y = Z = Rad = Ref = Tr = false;
	return TRUE;
}

// AddSphere message handlers

void AddSphere::ScrollUpdateR()
{
	wchar_t * buffer = new wchar_t[50];
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
		R = true;
	}
}


void AddSphere::UpdateBox(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	switch (pNMHDR->idFrom)
	{
	case IDC_SLIDERR:
		boxValueR.SetWindowTextW(CString(to_string(sliderR.GetPos()).c_str()));
		R = true;
		break;
	case IDC_SLIDERG:
		boxValueG.SetWindowTextW(CString(to_string(sliderG.GetPos()).c_str()));
		G = true;
		break;
	case IDC_SLIDERB:
		boxValueB.SetWindowTextW(CString(to_string(sliderB.GetPos()).c_str()));
		B = true;
		break;
	}

	*pResult = 0;
}

void AddSphere::ScrollUpdateG()
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
		G = true;
	}
}
void AddSphere::ScrollUpdateB()
{
	wchar_t * buffer = new wchar_t[50];
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
		B = true;
	}
}
void AddSphere::UpdateBoxR()
{
	boxValueR.SetWindowTextW(CString(to_string(sliderR.GetPos()).c_str()));
}
void AddSphere::UpdateBoxG()
{
	boxValueG.SetWindowTextW(CString(to_string(sliderG.GetPos()).c_str()));
}
void AddSphere::UpdateBoxB()
{
	boxValueB.SetWindowTextW(CString(to_string(sliderB.GetPos()).c_str()));
}

void AddSphere::UpdateBoxX()
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
		X = true;
	}
}
void AddSphere::UpdateBoxY()
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
		Y = true;
	}
}
void AddSphere::UpdateBoxZ()
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
		Z = true;
	}
}

void AddSphere::UpdateBoxRad()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueRad.GetWindowTextW(buffer, boxValueRad.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		valueRad = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			valueRad = strtol(to.c_str(), nullptr, 36);
		}
		if (valueRad > 10)
			valueRad = 10;
		else if (valueRad < 1)
			valueRad = 1;

		boxValueRad.SetWindowTextW(CString(to_string(valueRad).c_str()));
		Rad = true;
	}
}

void AddSphere::UpdateBoxRef()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueRef.GetWindowTextW(buffer, boxValueRef.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		valueRef = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			valueRef = strtol(to.c_str(), nullptr, 36);
		}
		if (valueRef > 100)
			valueRef = 100;
		else if (valueRef < 0)
			valueRef = 0;

		boxValueRef.SetWindowTextW(CString(to_string(valueRef).c_str()));
		Ref = true;
	}
}
void AddSphere::UpdateBoxTr()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueTr.GetWindowTextW(buffer, boxValueTr.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		valueTr = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			valueTr = strtol(to.c_str(), nullptr, 36);
		}
		if (valueTr > 100)
			valueTr = 100;
		else if (valueTr < 0)
			valueTr = 0;

		boxValueTr.SetWindowTextW(CString(to_string(valueTr).c_str()));
		Tr = true;
	}
}

void AddSphere::OnBnClickedOk()
{
	if (R == B && B == G && G == X && X == Y && Y == Z && Z == Rad && Rad == Ref && Ref == Tr && Tr != false)
	{
		base->spheres.push_back(new Sphere(new Data((float)valueX, (float)valueY, (float)valueZ, (float)sliderR.GetPos(), (float)sliderG.GetPos(), (float)sliderB.GetPos(), (float)valueRad, (float)valueRef, (float)valueTr), nullptr));
		this->EndDialog(0);
	}
	else
		TextWarning.ShowWindow(SW_SHOWNA);
}

