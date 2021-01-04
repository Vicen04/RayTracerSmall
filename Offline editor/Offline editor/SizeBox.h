#pragma once


// SizeBox dialog

class SizeBox : public CDialogEx
{
	DECLARE_DYNAMIC(SizeBox)

public:
	SizeBox(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SizeBox();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIZEBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	class COfflineeditorDlg* base;
	int selected = NULL, value;
	CListBox Spheres;
	CEdit boxValue;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedok();
	afx_msg void UpdateBox();
	afx_msg void UpdateBox2();
};
