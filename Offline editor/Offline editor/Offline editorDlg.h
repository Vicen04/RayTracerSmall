
// Offline editorDlg.h : header file
//
#include <string>
#include <iostream>
#include <vector>
#include "ColorBox.h"
#include "AboutBox.h"
#include "BackgroundColor.h"
#include "PositionBox.h"
#include "SizeBox.h"
#include "TransparencyBox.h"
#include "ReflectionBox.h"
#include "AddSphere.h"
#include "DeleteAnimation.h"
#include "DeleteSphere.h"
#include "AddAnimation.h"
#include "Saved.h"
#include "Instructions.h"
using namespace std;
#pragma once

struct Data
{
	Data(float X, float Y, float Z, float r, float g, float b, float rad, float refl, float tr)
	{
		posX = X; posY = Y; posZ = Z; red = r; green = g; blue = b; radius = rad; reflection = refl; transparency = tr;
	}
	~Data()
	{
		posX =posY = posZ = red = green = blue = radius = reflection = transparency = NULL;
	}
	float posX;
	float posY;
	float posZ;
	float red;
	float green;
	float blue;
	float radius;
	float reflection;
	float transparency;
};

struct Animation
{
	Animation(float StartX, float StartY, float StartZ, float endX, float endY, float endZ, float frames)
	{
		sumX = (endX - StartX)/frames; sumY = (endY - StartY)/frames; sumZ = (endZ - StartZ)/frames; loops = frames;
	}
	~Animation()
	{
		sumX = sumY = sumZ = loops = NULL;
	}
	float sumX;
	float sumY;
	float sumZ;
	unsigned loops;
};

struct Sphere
{
	Sphere(Data* d,	Animation* a)
	{
		data = d; animation = a;
	}
	Data* data;
	Animation* animation;
};

// COfflineeditorDlg dialog
class COfflineeditorDlg : public CDialogEx
{
// Construction
public:
	COfflineeditorDlg(CWnd* pParent = nullptr);	// standard constructor
	void OnMenuSelected(UINT nID);
	void SaveFile();
	vector<Sphere*> spheres;
	Sphere* selectedSphere;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OFFLINEEDITOR };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	void DrawSphere();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CMFCMenuButton menuSelected;
    ColorBox color;
	AboutBox about;
	PositionBox position;
	BackgroundColor Bcolor;
	SizeBox size;
	ReflectionBox reflection;
	TransparencyBox transparency;
	AddSphere add;
	DeleteSphere delSphere;
	AddAnimation animation;
	DeleteAnimation delAni;
	Saved saved;
	Instructions instructions;
	CMenu menu;
	CPaintDC* dc;
	int count = 1;
};
