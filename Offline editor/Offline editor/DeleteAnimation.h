#pragma once


// DeleteAnimation dialog

class DeleteAnimation : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteAnimation)

public:
	DeleteAnimation(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DeleteAnimation();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETEANIMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	class COfflineeditorDlg* base;
	int selected = NULL;
	CListBox Spheres;
	CStatic TextNoSelected;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDelete();
	afx_msg void Select();
};
