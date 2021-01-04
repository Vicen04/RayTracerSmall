#pragma once


// Saved dialog

class Saved : public CDialogEx
{
	DECLARE_DYNAMIC(Saved)

public:
	Saved(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Saved();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAVED };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
