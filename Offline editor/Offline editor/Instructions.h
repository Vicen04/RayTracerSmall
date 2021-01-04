#pragma once


// Instructions dialog

class Instructions : public CDialogEx
{
	DECLARE_DYNAMIC(Instructions)

public:
	Instructions(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Instructions();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSTRUCTIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
