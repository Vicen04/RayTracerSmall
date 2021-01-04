#pragma once


// TransparencyBox dialog

class TransparencyBox : public CDialogEx
{
	DECLARE_DYNAMIC(TransparencyBox)

public:
	TransparencyBox(CWnd* pParent = nullptr);   // standard constructor
	virtual ~TransparencyBox();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSPARENCYBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


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
	DECLARE_MESSAGE_MAP()
};
