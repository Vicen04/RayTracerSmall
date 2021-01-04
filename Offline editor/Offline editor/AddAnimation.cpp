// AddAnimation.cpp : implementation file
//

#include "stdafx.h"
#include "Offline editor.h"
#include "Offline editorDlg.h"
#include "afxdialogex.h"


// AddAnimation dialog

IMPLEMENT_DYNAMIC(AddAnimation, CDialogEx)

AddAnimation::AddAnimation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDANIMATION, pParent)
{

}

AddAnimation::~AddAnimation()
{
}

void AddAnimation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_POSX, boxValueStartX);
	DDX_Control(pDX, IDC_POSY, boxValueStartY);
	DDX_Control(pDX, IDC_POSZ, boxValueStartZ);
	DDX_Control(pDX, IDC_POSXEND, boxValueEndX);
	DDX_Control(pDX, IDC_POSYEND, boxValueEndY);
	DDX_Control(pDX, IDC_POSZEND, boxValueEndZ);
	DDX_Control(pDX, IDC_FRAMES, boxValueFrames);
	DDX_Control(pDX, IDC_LISTSPHERES, Spheres);
}


BEGIN_MESSAGE_MAP(AddAnimation, CDialogEx)
	ON_EN_KILLFOCUS(IDC_POSX, &AddAnimation::UpdateBoxStartX)
	ON_EN_KILLFOCUS(IDC_POSY, &AddAnimation::UpdateBoxStartY)
	ON_EN_KILLFOCUS(IDC_POSZ, &AddAnimation::UpdateBoxStartZ)
	ON_EN_KILLFOCUS(IDC_POSXEND, &AddAnimation::UpdateBoxEndX)
	ON_EN_KILLFOCUS(IDC_POSYEND, &AddAnimation::UpdateBoxEndY)
	ON_EN_KILLFOCUS(IDC_POSZEND, &AddAnimation::UpdateBoxEndZ)
	ON_EN_KILLFOCUS(IDC_FRAMES, &AddAnimation::UpdateBoxFrames)
	ON_LBN_DBLCLK(IDC_LISTSPHERES, &AddAnimation::UpdateBox)
	ON_BN_CLICKED(ID_ANIMATIONOK, &AddAnimation::OnBnClickedPositionok)
END_MESSAGE_MAP()


BOOL AddAnimation::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	base = (COfflineeditorDlg*)this->GetAncestor(GA_ROOTOWNER);
	for (int i = 1; i < base->spheres.size(); i++)
	{
		Spheres.AddString(CString(to_string(i).c_str()));
	}
	return TRUE;
}

void AddAnimation::UpdateBox()
{
	selected = Spheres.GetCurSel() + 1;
	if (selected != NULL && selected != LB_ERR )
	{
			boxValueStartX.SetWindowTextW(CString(to_string((int)base->spheres.at(selected)->data->posX).c_str()));
			valueStartX = (int)base->spheres.at(selected)->data->posX;
			valueEndX = (int)base->spheres.at(selected)->data->posX;
			boxValueStartY.SetWindowTextW(CString(to_string((int)base->spheres.at(selected)->data->posY).c_str()));
			valueStartY = (int)base->spheres.at(selected)->data->posY;
			valueEndY = (int)base->spheres.at(selected)->data->posY;
			boxValueStartZ.SetWindowTextW(CString(to_string((int)base->spheres.at(selected)->data->posZ).c_str()));
			valueStartZ = (int)base->spheres.at(selected)->data->posZ;
			valueEndZ = (int)base->spheres.at(selected)->data->posZ;
			boxValueEndX.SetWindowTextW(CString(to_string((int)base->spheres.at(selected)->data->posX).c_str()));
			boxValueEndY.SetWindowTextW(CString(to_string((int)base->spheres.at(selected)->data->posY).c_str()));
			boxValueEndZ.SetWindowTextW(CString(to_string((int)base->spheres.at(selected)->data->posZ).c_str()));
			boxValueFrames.SetWindowTextW(CString(to_string(1).c_str()));
	}
}

void AddAnimation::UpdateBoxStartX()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueStartX.GetWindowTextW(buffer, boxValueStartX.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		valueStartX = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			valueStartX = strtol(to.c_str(), nullptr, 36);
		}
		if (valueStartX > 20)
			valueStartX = 20;
		else if (valueStartX < -20)
			valueStartX = -20;

		boxValueStartX.SetWindowTextW(CString(to_string(valueStartX).c_str()));
	}
}
void AddAnimation::UpdateBoxStartY()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueStartY.GetWindowTextW(buffer, boxValueStartY.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		valueStartY = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			valueStartY = strtol(to.c_str(), nullptr, 36);
		}
		if (valueStartY > 20)
			valueStartY = 20;
		else if (valueStartY < -20)
			valueStartY = -20;

		boxValueStartY.SetWindowTextW(CString(to_string(valueStartY).c_str()));
	}
}
void AddAnimation::UpdateBoxStartZ()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueStartZ.GetWindowTextW(buffer, boxValueStartZ.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		valueStartZ = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			valueStartZ = strtol(to.c_str(), nullptr, 36);
		}
		if (valueStartZ > -30)
			valueStartZ = -30;
		else if (valueStartZ < -300)
			valueStartZ = -300;

		boxValueStartZ.SetWindowTextW(CString(to_string(valueStartZ).c_str()));
	}
}

void AddAnimation::UpdateBoxEndX()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueEndX.GetWindowTextW(buffer, boxValueEndX.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		valueEndX = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			valueEndX = strtol(to.c_str(), nullptr, 36);
		}
		if (valueEndX > 30)
			valueEndX = 30;
		else if (valueEndX < -30)
			valueEndX = -30;

		boxValueEndX.SetWindowTextW(CString(to_string(valueEndX).c_str()));
	}
}
void AddAnimation::UpdateBoxEndY()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueEndY.GetWindowTextW(buffer, boxValueEndY.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		valueEndY = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			valueEndY = strtol(to.c_str(), nullptr, 36);
		}
		if (valueEndY > 30)
			valueEndY = 30;
		else if (valueEndY < -30)
			valueEndY = -30;

		boxValueEndY.SetWindowTextW(CString(to_string(valueEndY).c_str()));
	}
}
void AddAnimation::UpdateBoxEndZ()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueEndZ.GetWindowTextW(buffer, boxValueEndZ.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		valueEndZ = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			valueEndZ = strtol(to.c_str(), nullptr, 36);
		}
		if (valueEndZ > -20)
			valueEndZ = -20;
		else if (valueEndZ < -400)
			valueEndZ = -400;

		boxValueEndZ.SetWindowTextW(CString(to_string(valueEndZ).c_str()));
	}
}

void AddAnimation::UpdateBoxFrames()
{
	wchar_t * buffer = new wchar_t[50];
	char* p;
	boxValueFrames.GetWindowTextW(buffer, boxValueFrames.GetWindowTextLengthW() + 1);
	USES_CONVERSION;
	string to = T2A(buffer);
	if (to.size() > 0)
	{
		valueFrames = strtol(to.c_str(), &p, 10);
		if (*p)
		{
			valueFrames = strtol(to.c_str(), nullptr, 36);
		}
		if (valueFrames < 1)
			valueFrames = 1;
		else if (valueFrames > 120)
			valueFrames = 120;

		boxValueFrames.SetWindowTextW(CString(to_string(valueFrames).c_str()));
	}
}

void AddAnimation::OnBnClickedPositionok()
{
	if (selected != NULL && selected != LB_ERR)
	{
		base->spheres.at(selected)->data->posX = (float)valueStartX;
		base->spheres.at(selected)->data->posY = (float)valueStartY;
		base->spheres.at(selected)->data->posZ = (float)valueStartZ;
		if (base->spheres.at(selected)->animation != nullptr)
			delete base->spheres.at(selected)->animation;
		base->spheres.at(selected)->animation = new Animation((float)valueStartX, (float)valueStartY, (float)valueStartZ, (float)valueEndX, (float)valueEndY, (float)valueEndZ, valueFrames);
	}
	this->EndDialog(0);
}
