#pragma once


// AboutBox dialog

class AboutBox : public CDialogEx
{
	DECLARE_DYNAMIC(AboutBox)

public:
	AboutBox(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AboutBox();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
