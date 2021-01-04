
// Offline editorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Offline editor.h"
#include "Offline editorDlg.h"
#include "afxdialogex.h"
#include <sstream>
#include <fstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COfflineeditorDlg dialog



COfflineeditorDlg::COfflineeditorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OFFLINEEDITOR, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COfflineeditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COfflineeditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(ID_HELP_ABOUT, ID_SPHERES_REFLECTION, &COfflineeditorDlg::OnMenuSelected)
END_MESSAGE_MAP()


// COfflineeditorDlg message handlers

BOOL COfflineeditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	spheres.push_back(new Sphere(new Data(0.0, -10004, -20, 51, 51, 51, 10000, 0, 0.0), NULL));
	menu.LoadMenuW(IDR_EDITORMENU);
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COfflineeditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		about.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COfflineeditorDlg::OnPaint()
{
	dc = new CPaintDC(this);
	if (IsIconic())
	{
		 // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc->GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc->DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COfflineeditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COfflineeditorDlg::OnMenuSelected(UINT nID)
{
	switch (nID)
	{
	case ID_FILE_FOPEN:

		break;
	case ID_FILE_FSAVE:
		SaveFile();
		break;
	case ID_FILE_EXIT:
		this->EndDialog(0);
		break;
	case ID_EDIT_ADDSPHERE:
		add.DoModal();
		//DrawSphere();
		break;
	case ID_EDIT_DELETESPHERE:
		if (spheres.size() > 1)
			delSphere.DoModal();
		break;
	case ID_EDIT_DELETEALLANIMATIONS:
		for (; count < spheres.size(); count++)
		{
			if (spheres.at(count)->animation != nullptr)
			{
				delete spheres.at(count)->animation;
				spheres.at(count)->animation = nullptr;
			}
		}
		count = 1;
		break;
	case ID_SPHERES_COLOR:
		color.DoModal();
		break;
	case ID_SPHERES_POSITION:
		position.DoModal();
		break;
	case ID_SPHERES_SIZE:
		size.DoModal();
		break;
	case ID_SPHERES_REFLECTION:
		reflection.DoModal();
		break;
	case ID_SPHERES_TRANSPARENCY:
		transparency.DoModal();
		break;
	case ID_SPHERES_ADDANIMATION:
		animation.DoModal();
		break;
	case ID_SPHERES_DELETEANIMATION:
		delAni.DoModal();
		break;
	case ID_BACKGROUND_COLOR:
		Bcolor.DoModal();
		break;
	case ID_HELP_ABOUT:
		about.DoModal();
		break;
	case ID_HELP_INSTRUCTIONS:
		instructions.DoModal();
		break;
	}
}

void COfflineeditorDlg::DrawSphere()
{
	RECT windowsize;
	this->GetWindowRect(&windowsize);
	PAINTSTRUCT Ps;
	this->BeginPaint(&Ps);

	this->EndPaint(&Ps);
}

void COfflineeditorDlg::SaveFile()
{
	bool animations = false;
	for (int i = 1; i < spheres.size(); i++)
	{
		if (spheres.at(i)->animation != nullptr)
			animations = true;
	}
	std::stringstream ss;
	ss << "./spheres_created" << ".json";
	std::string tempString = ss.str();
	char* filename = (char*)tempString.c_str();

	std::ofstream ofs(filename, std::ios::out);
	ofs << animations << endl;
	ofs << spheres.size() << endl;
	for (int i = 0; i < spheres.size(); i++)
	{
		ofs << spheres.at(i)->data->posX << endl;
		ofs << spheres.at(i)->data->posY << endl;
		ofs << spheres.at(i)->data->posZ << endl;
		ofs << spheres.at(i)->data->radius << endl;
		ofs << spheres.at(i)->data->red / 255.0f << endl;
		ofs << spheres.at(i)->data->green / 255.0f << endl;
		ofs << spheres.at(i)->data->blue / 255.0f << endl;
		ofs << spheres.at(i)->data->reflection /100.0f << endl;
		ofs << spheres.at(i)->data->transparency / 100.0f << endl;
		if (spheres.at(i)->animation != nullptr)
		{
			ofs << spheres.at(i)->animation->loops << endl;
			ofs << spheres.at(i)->animation->sumX << endl;
			ofs << spheres.at(i)->animation->sumY << endl;
			ofs << spheres.at(i)->animation->sumZ << endl;
		}
		else
		{
			ofs << 0 << endl;
			ofs << 0 << endl;
			ofs << 0 << endl;
			ofs << 0 << endl;
		}
	}
	ofs.close();
	saved.DoModal();
}