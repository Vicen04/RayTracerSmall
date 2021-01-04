#pragma once


// ReflectionBox dialog

class ReflectionBox : public CDialogEx
{
	DECLARE_DYNAMIC(ReflectionBox)

public:
	ReflectionBox(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ReflectionBox();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REFLECTION };
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
